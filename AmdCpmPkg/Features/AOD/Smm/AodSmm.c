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
 ******************************************************************************
 */

/*****************************************************************************
 *
 * This software package can be used to enable the Overclocking of certain
 * AMD processors and its use is subject to the terms and conditions of the
 * AMD Overclocking Waiver. Enabling overclocking through use of the low-level
 * routines included in this package and operating an AMD processor outside of
 * the applicable AMD product specifications will void any AMD warranty and can
 * result in damage to the processor or the system into which the processor has
 * been integrated. The user of this software assumes, and AMD disclaims, all
 * risk, liability, costs and damages relating to or arising from the overclocking
 * of AMD processors.
 *
 ******************************************************************************
 */

#include <Library/BaseMemoryLib.h>
#include <Protocol/SmmBase2.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/SmmServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/PciLib.h>
#include <Protocol/FchSmmSwDispatch2.h>
#include <Protocol/SmmVariable.h>

#include <Features/AOD/Include/AodRuntimeLib.h>
#include <Features/AOD/Include/AodCbsLib.h>
#include <ApcbCommon.h>
#include <Protocol/AmdApcbProtocol.h>


EFI_SMM_SYSTEM_TABLE2         *gSmst;
AodNvAreaStruct               *gAodNvAreaPtr;
AodCpuBiosStruct              *gAodCpuBiosStruct;

extern EFI_GUID gAodNvAreaUpdatedProtocolGuid;
extern  EFI_GUID gAmdApcbSmmServiceProtocolGuid;

AMD_APCB_SERVICE_PROTOCOL        *mApcbSmmServiceProtocol;
BOOLEAN                          gCommandBufferSaved = FALSE;
BOOLEAN                          gApcbChanged = FALSE;

EFI_STATUS
DumpApcbConfig (
  VOID
  )
{
  EFI_STATUS                           Status;
  UINT32                               Value;
  UINT16                               MemFreqClk;
  UINT8                                Die;
  UINT8                                DieBusNum;
  UINT32                               ChSmnChannelBase;
  UINT32                               CtlSmnChannelBase;
  UINT64                               PciAddress;

  Status = EFI_SUCCESS;
  DieBusNum = 0;
  ChSmnChannelBase = 0;
  CtlSmnChannelBase = 0;

  // First read from CH0
  AodSmnRead (DieBusNum, CH_SMN_BASE_CH0_MP0 + DRAM_CONFIGURATION, &Value);
  if (Value & 0x7F) {  // bit [6:0]
    ChSmnChannelBase = CH_SMN_BASE_CH0_MP0;
    CtlSmnChannelBase = CTL_SMN_BASE_CH0_MP0;
  } else {
    // If there's no DIMM on CH0, read from CH1
    AodSmnRead (DieBusNum, CH_SMN_BASE_CH1_MP0 + DRAM_CONFIGURATION, &Value);
    if (Value & 0x7F) {  // bit [6:0]
      ChSmnChannelBase = CH_SMN_BASE_CH1_MP0;
      CtlSmnChannelBase = CTL_SMN_BASE_CH1_MP0;
    }
  }

  if (ChSmnChannelBase == 0) {
    // For MCM, try to read from other DIEs
    for (Die = 1; Die < MAX_DIE_SUPPORT; Die++) {
      //DF devices on bus0
      PciAddress =  (0 << 20) + ((Die + 24) << 15) + (0 << 12) + 0;
      Value = PciRead32 (PciAddress);
      if ((Value & 0xFFFF) != AMD_VENDOR_ID) {
        continue;
      }
      PciAddress = (0 << 20) + ((Die + 24) << 15) + (0 << 12) + 0x84;
      Value = PciRead32 (PciAddress);
      DieBusNum = Value & 0xFF;

      // First read from CH0
      AodSmnRead (DieBusNum, CH_SMN_BASE_CH0_MP0 + DRAM_CONFIGURATION, &Value);
      if (Value & 0x7F) {  // bit [6:0]
        ChSmnChannelBase = CH_SMN_BASE_CH0_MP0;
        CtlSmnChannelBase = CTL_SMN_BASE_CH0_MP0;
        break;
      } else {
        // If there's no DIMM on CH0, read from CH1
        AodSmnRead (DieBusNum, CH_SMN_BASE_CH1_MP0 + DRAM_CONFIGURATION, &Value);
        if (Value & 0x7F) {  // bit [6:0]
          ChSmnChannelBase = CH_SMN_BASE_CH1_MP0;
          CtlSmnChannelBase = CTL_SMN_BASE_CH1_MP0;
          break;
        }
      }
    }
  }

  if (ChSmnChannelBase == 0) {
    // Should never be here
    return EFI_NOT_FOUND;
  }

  // MCLK
  AodSmnRead (DieBusNum, ChSmnChannelBase + DRAM_CONFIGURATION, &Value);
  Status = GetMemFreqClkByIndex ((UINT8) (Value & 0x7F), &MemFreqClk);
  if (Status == EFI_SUCCESS) {
    gAodNvAreaPtr->AodMemBuffer.MemClkFreq = MemFreqClk;
  } else {
    gAodNvAreaPtr->AodMemBuffer.MemClkFreq = Value & 0x7F; // Raw value
  }

  // Tcl, Tras, Trcdrd, Trcdwr
  AodSmnRead (DieBusNum, ChSmnChannelBase + DRAM_TIMING1, &Value);
  gAodNvAreaPtr->AodMemBuffer.Tcl = Value & 0x3F;  // bit [5:0]
  gAodNvAreaPtr->AodMemBuffer.Tras = (Value >> 8) & 0x7F;  // bit [14:8]
  gAodNvAreaPtr->AodMemBuffer.Trcdrd = (Value >> 16) & 0x3F;  // bit [21:16]
  gAodNvAreaPtr->AodMemBuffer.Trcdwr = (Value >> 24) & 0x3F;  // bit [29:24]

  // Trp
  AodSmnRead (DieBusNum, ChSmnChannelBase + DRAM_TIMING2, &Value);
  gAodNvAreaPtr->AodMemBuffer.Trp = (Value >> 16) & 0x3F; // bit [21:16]

  // procODT
  gAodNvAreaPtr->AodMemBuffer.procODT = gAodCpuBiosStruct->procODT;

  // Trcpage
  AodSmnRead (DieBusNum, ChSmnChannelBase + DRAM_TIMING7, &Value);
  gAodNvAreaPtr->AodMemBuffer.Trcpage = (Value >> 20) & 0xFFF;  // bit[31:20]

  // Trc
  AodSmnRead (DieBusNum, ChSmnChannelBase + DRAM_TIMING2, &Value);
  gAodNvAreaPtr->AodMemBuffer.Trc = Value & 0xFF;  // bit[7:0]

  // Tfrc, Tfrc2, Trfc4
  AodSmnRead (DieBusNum, ChSmnChannelBase + DRAM_TRFC_TIMING, &Value);
  gAodNvAreaPtr->AodMemBuffer.Trfc = Value & 0x7FF;  // bit[10:0]
  gAodNvAreaPtr->AodMemBuffer.Trfc2 = (Value >> 11) & 0x7FF;  // bit[21:11]
  gAodNvAreaPtr->AodMemBuffer.Trfc4 = (Value >> 22) & 0x7FF;  // bit[31:22]

  // Tfaw
  AodSmnRead (DieBusNum, ChSmnChannelBase + DRAM_TIMING4, &Value);
  gAodNvAreaPtr->AodMemBuffer.Tfaw = Value & 0x7F;  // bit[6:0]

  // TrrdS, TrrdL, Trtp
  AodSmnRead (DieBusNum, ChSmnChannelBase + DRAM_TIMING3, &Value);
  gAodNvAreaPtr->AodMemBuffer.TrrdS = Value & 0x1F;  // bit[4:0]
  gAodNvAreaPtr->AodMemBuffer.TrrdL = (Value >> 8) & 0x1F;  // bit[12:8]
  gAodNvAreaPtr->AodMemBuffer.Trtp = (Value >> 24) & 0x1F;  // bit[28:24]

  // Twr
  AodSmnRead (DieBusNum, ChSmnChannelBase + DRAM_TIMING6, &Value);
  gAodNvAreaPtr->AodMemBuffer.Twr = Value & 0x7F;  // bit[6:0]

  // TwtrS, TwtrL, Tcwl
  AodSmnRead (DieBusNum, ChSmnChannelBase + DRAM_TIMING5, &Value);
  gAodNvAreaPtr->AodMemBuffer.Tcwl = Value & 0x3F;  // bit[5:0]
  gAodNvAreaPtr->AodMemBuffer.TwtrS = (Value >> 8) & 0x1F;  // bit[12:8]
  gAodNvAreaPtr->AodMemBuffer.TwtrL = (Value >> 16) & 0x7F;  // bit[22:16]

  // tCKE
  AodSmnRead (DieBusNum, ChSmnChannelBase + DRAM_TIMING21, &Value);
  gAodNvAreaPtr->AodMemBuffer.TCke = (Value >> 24) & 0x1F;  // bit[28:24]

  // TrdrdSc, TrdrdScL, TrdrdSd, TrdrdDd
  AodSmnRead (DieBusNum, ChSmnChannelBase + DRAM_TIMING8, &Value);
  gAodNvAreaPtr->AodMemBuffer.TrdrdDd = Value & 0xF;  // bit[3:0]
  gAodNvAreaPtr->AodMemBuffer.TrdrdSd = (Value >> 8) & 0xF;  // bit[11:8]
  gAodNvAreaPtr->AodMemBuffer.TrdrdSc = (Value >> 16) & 0xF;  // bit[19:16]
  gAodNvAreaPtr->AodMemBuffer.TrdrdScL = (Value >> 24) & 0xF;  // bit[27:24]

  // TwrwrSc, TwrwrScL, TwrwrSd, TwrwrDd
  AodSmnRead (DieBusNum, ChSmnChannelBase + DRAM_TIMING9, &Value);
  gAodNvAreaPtr->AodMemBuffer.TwrwrDd = Value & 0xF;  // bit[3:0]
  gAodNvAreaPtr->AodMemBuffer.TwrwrSd = (Value >> 8) & 0xF;  // bit[11:8]
  gAodNvAreaPtr->AodMemBuffer.TwrwrSc = (Value >> 16) & 0xF;  // bit[19:16]
  gAodNvAreaPtr->AodMemBuffer.TwrwrScL = (Value >> 24) & 0xF;  // bit[27:24]

  // Trdwr, Twrrd
  AodSmnRead (DieBusNum, ChSmnChannelBase + DRAM_TIMING10, &Value);
  gAodNvAreaPtr->AodMemBuffer.Twrrd = Value & 0xF;  // bit[3:0]
  gAodNvAreaPtr->AodMemBuffer.Trdwr = (Value >> 8) & 0x1F;  // bit[12:8]

  // GearDownEn, Cmd2t
  AodSmnRead (DieBusNum, ChSmnChannelBase + DRAM_CONFIGURATION, &Value);
  gAodNvAreaPtr->AodMemBuffer.GearDownEn = (Value >> 11) & 0x1;  // bit 11
  gAodNvAreaPtr->AodMemBuffer.Cmd2t = (Value >> 10) & 0x1;  // bit 10

  // RttNom, RttWr, RttPark
  gAodNvAreaPtr->AodMemBuffer.RttNom = gAodCpuBiosStruct->RttNom;
  gAodNvAreaPtr->AodMemBuffer.RttWR = gAodCpuBiosStruct->RttWR;
  gAodNvAreaPtr->AodMemBuffer.RttPark = gAodCpuBiosStruct->RttPark;

  // PowerDownEn
  AodSmnRead (DieBusNum, ChSmnChannelBase + DRAM_SPAZ_CONTROL, &Value);
  gAodNvAreaPtr->AodMemBuffer.PowerDownEn = (Value >> 28) & 0x1;  // bit 28

  // OcDisable, OcVoltageMax, OcFrequencyMax
  gAodNvAreaPtr->AodMemBuffer.OcDisable = gAodCpuBiosStruct->OcDisable;
  gAodNvAreaPtr->AodMemBuffer.OcVoltageMax = gAodCpuBiosStruct->OcVoltageMax;
  gAodNvAreaPtr->AodMemBuffer.OcFrequencyMax = gAodCpuBiosStruct->OcFrequencyMax;

  // SMT enable/disable
  gAodNvAreaPtr->AodMemBuffer.SmtEnabled = gAodCpuBiosStruct->SmtEnabled;
  gAodNvAreaPtr->AodMemBuffer.DownCore.ActiveCoreNum = gAodCpuBiosStruct->ActiveCoreNum;

  // CDC Throttler Control
  gAodNvAreaPtr->AodMemBuffer.EdcThrottlerCtrl = gAodCpuBiosStruct->EdcThrottlerCtrl;
  gAodNvAreaPtr->AodMemBuffer.EdcThrottlerCtrlOpnValue = gAodCpuBiosStruct->EdcThrottlerCtrlOpnValue;

  //  AddrCmdSetup, CsOdtSetup, CkeSetup
  gAodNvAreaPtr->AodMemBuffer.AddrCmdSetup = gAodCpuBiosStruct->AddrCmdSetup;
  gAodNvAreaPtr->AodMemBuffer.CsOdtSetup = gAodCpuBiosStruct->CsOdtSetup;
  gAodNvAreaPtr->AodMemBuffer.CkeSetup = gAodCpuBiosStruct->CkeSetup;

  //  CadBusClkDrvStren, CadBusAddrDrvStren, CadBusCsOdtCmdDrvStren, CadBusCkeDrvStren
  gAodNvAreaPtr->AodMemBuffer.CadBusClkDrvStren = gAodCpuBiosStruct->CadBusClkDrvStren;
  gAodNvAreaPtr->AodMemBuffer.CadBusAddrDrvStren = gAodCpuBiosStruct->CadBusAddrDrvStren;
  gAodNvAreaPtr->AodMemBuffer.CadBusCsOdtCmdDrvStren = gAodCpuBiosStruct->CadBusCsOdtCmdDrvStren;
  gAodNvAreaPtr->AodMemBuffer.CadBusCkeDrvStren = gAodCpuBiosStruct->CadBusCkeDrvStren;

  //  CldoVddp
  gAodNvAreaPtr->AodMemBuffer.CldoVddp = gAodCpuBiosStruct->CldoVddp;

  // Interleaving Cap/Mode/Size
  gAodNvAreaPtr->AodMemBuffer.MemInterleavingCap = gAodCpuBiosStruct->MemInterleavingCap;
  gAodNvAreaPtr->AodMemBuffer.MemInterleavingMode = gAodCpuBiosStruct->MemInterleavingMode;
  gAodNvAreaPtr->AodMemBuffer.InterleavingSize = gAodCpuBiosStruct->InterleavingSize;

  // Temp offset
  gAodNvAreaPtr->AodMemBuffer.TempOffset = gAodCpuBiosStruct->TempOffset;

  // PPT/TDC/EDC Platform (PCD) Limits
  gAodNvAreaPtr->AodMemBuffer.PptPlatformPCD = gAodCpuBiosStruct->PptPlatformPCD;
  gAodNvAreaPtr->AodMemBuffer.TdcPlatformPCD = gAodCpuBiosStruct->TdcPlatformPCD;
  gAodNvAreaPtr->AodMemBuffer.EdcPlatformPCD = gAodCpuBiosStruct->EdcPlatformPCD;

  // FCLK OC Mode and Vddcr SOC VID are not be able to get, initialized to 0 at the moment
  gAodNvAreaPtr->AodMemBuffer.FclkOcMode = 0;
  gAodNvAreaPtr->AodMemBuffer.VddcrSocVid = 0;

  return Status;
}

EFI_STATUS
SetApcbConfig (
  UINT16          TokenId,
  UINT64          Value
  )
{
  UINT32        SizeInByte;
  EFI_STATUS    Status;

  DEBUG ((DEBUG_INFO, "\tSetApcbConfig Entry:  TokenId = 0x%x\n", TokenId));

  SizeInByte = 1;   // Note: Make sure this token length is aligned with APCB
  Status = mApcbSmmServiceProtocol->ApcbSetCbsParameter (
               mApcbSmmServiceProtocol,
               TokenId,
               &SizeInByte,
               &Value
               );
  DEBUG ((DEBUG_INFO, "\tSetApcbConfig Exit\n"));

  return Status;
}


EFI_STATUS
EFIAPI
AodMemClkTimingsUpdateSmmSwSmiCallBack (
  IN       EFI_HANDLE                        DispatchHandle,
  IN       CONST FCH_SMM_SW_REGISTER_CONTEXT *DispatchContext,
  IN OUT   FCH_SMM_SW_CONTEXT                *SwContext,
  IN OUT   UINTN                             *SizeOfSwContext
  )
{
  EFI_STATUS                           Status;

  Status = EFI_SUCCESS;

  DEBUG ((DEBUG_INFO, "\tAodMemClkTimingsUpdateSmmSwSmiCallBack Entry\n"));

  IoWrite8 (0x80, 0xD1);

  if (VerifyAcpiSmiTransferBuffer (gAodNvAreaPtr)) {
    IoWrite8 (0x80, 0xD2);
    if (gAodNvAreaPtr->AodMemBuffer.Command == GET_MEM_DATA_BUFFER) {
      IoWrite8 (0x80, 0xD3);
      Status = DumpApcbConfig ();
    } else if (gAodNvAreaPtr->AodMemBuffer.Command == COMMAND_BUFFER_START) {
      IoWrite8 (0x80, 0xF1);
      gCommandBufferSaved = TRUE;
    } else if (gAodNvAreaPtr->AodMemBuffer.Command == COMMAND_BUFFER_END) {
      IoWrite8 (0x80, 0xF2);
      gCommandBufferSaved = FALSE;
    } else {
      if (gAodNvAreaPtr->AodMemBuffer.Command == SET_MEMORY_CLOCK) {
        UINT8 MemFreqIndex = 0xFF;
        Status = GetMemFreqIndexByClk (gAodNvAreaPtr->AodMemBuffer.MemClkFreq, &MemFreqIndex);
        if (Status == EFI_SUCCESS) {
          Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_SPEED_DDR4, MemFreqIndex);
          if (Status == EFI_SUCCESS) {
            IoWrite8 (0x80, 0xD4);
            gApcbChanged = TRUE;
          }
        }
      } else if (gAodNvAreaPtr->AodMemBuffer.Command == SET_TCL) {
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_TIMING_TCL_DDR4, gAodNvAreaPtr->AodMemBuffer.Tcl);
        if (Status == EFI_SUCCESS) {
          gApcbChanged = TRUE;
        }
      } else if (gAodNvAreaPtr->AodMemBuffer.Command == SET_TRCDRD) {
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_TIMING_TRCDRD_DDR4, gAodNvAreaPtr->AodMemBuffer.Trcdrd);
        if (Status == EFI_SUCCESS) {
          gApcbChanged = TRUE;
        }
      } else if (gAodNvAreaPtr->AodMemBuffer.Command == SET_TRCDWR) {
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_TIMING_TRCDWR_DDR4, gAodNvAreaPtr->AodMemBuffer.Trcdwr);
        if (Status == EFI_SUCCESS) {
          gApcbChanged = TRUE;
        }
      } else if (gAodNvAreaPtr->AodMemBuffer.Command == SET_TRAS) {
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_TIMING_TRAS_DDR4, gAodNvAreaPtr->AodMemBuffer.Tras);
        if (Status == EFI_SUCCESS) {
          gApcbChanged = TRUE;
        }
      } else if (gAodNvAreaPtr->AodMemBuffer.Command == SET_TRP) {
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_TIMING_TRP_DDR4, gAodNvAreaPtr->AodMemBuffer.Trp);
        if (Status == EFI_SUCCESS) {
          gApcbChanged = TRUE;
        }
      } else if (gAodNvAreaPtr->AodMemBuffer.Command == SET_PROC_ODT) {
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_CTRLLER_PROC_ODT_DDR4, gAodNvAreaPtr->AodMemBuffer.procODT);
        if (Status == EFI_SUCCESS) {
          gApcbChanged = TRUE;
        }
      } else if (gAodNvAreaPtr->AodMemBuffer.Command == SET_TRCPAGE) {
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_TIMING_TRCPAGE_CTRL_DDR4, 1);  // Manual
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_TIMING_TRCPAGE_DDR4, gAodNvAreaPtr->AodMemBuffer.Trcpage);
        if (Status == EFI_SUCCESS) {
          gApcbChanged = TRUE;
        }
      } else if (gAodNvAreaPtr->AodMemBuffer.Command == SET_TRC) {
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_TIMING_TRC_CTRL_DDR4, 1);  // Manual
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_TIMING_TRC_DDR4, gAodNvAreaPtr->AodMemBuffer.Trc);
        if (Status == EFI_SUCCESS) {
          gApcbChanged = TRUE;
        }
      } else if (gAodNvAreaPtr->AodMemBuffer.Command == SET_TRFC) {
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_TIMING_TRFC_CTRL_DDR4, 1);  // Manual
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_TIMING_TRFC_DDR4, gAodNvAreaPtr->AodMemBuffer.Trfc);
        if (Status == EFI_SUCCESS) {
          gApcbChanged = TRUE;
        }
      } else if (gAodNvAreaPtr->AodMemBuffer.Command == SET_TRFC2) {
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_TIMING_TRFC2_CTRL_DDR4, 1);  // Manual
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_TIMING_TRFC2_DDR4, gAodNvAreaPtr->AodMemBuffer.Trfc2);
        if (Status == EFI_SUCCESS) {
          gApcbChanged = TRUE;
        }
      } else if (gAodNvAreaPtr->AodMemBuffer.Command == SET_TRFC4) {
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_TIMING_TRFC4_CTRL_DDR4, 1);  // Manual
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_TIMING_TRFC4_DDR4, gAodNvAreaPtr->AodMemBuffer.Trfc4);
        if (Status == EFI_SUCCESS) {
          gApcbChanged = TRUE;
        }
      } else if (gAodNvAreaPtr->AodMemBuffer.Command == SET_TFAW) {
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_TIMING_TFAW_CTRL_DDR4, 1);  // Manual
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_TIMING_TFAW_DDR4, gAodNvAreaPtr->AodMemBuffer.Tfaw);
        if (Status == EFI_SUCCESS) {
          gApcbChanged = TRUE;
        }
      } else if (gAodNvAreaPtr->AodMemBuffer.Command == SET_TRRDS) {
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_TIMING_TRRD_S_DDR4, gAodNvAreaPtr->AodMemBuffer.TrrdS);
        if (Status == EFI_SUCCESS) {
          gApcbChanged = TRUE;
        }
      } else if (gAodNvAreaPtr->AodMemBuffer.Command == SET_TRRDL) {
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_TIMING_TRRD_L_DDR4, gAodNvAreaPtr->AodMemBuffer.TrrdL);
        if (Status == EFI_SUCCESS) {
          gApcbChanged = TRUE;
        }
      } else if (gAodNvAreaPtr->AodMemBuffer.Command == SET_TWR) {
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_TIMING_TWR_CTRL_DDR4, 1);  // Manual
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_TIMING_TWR_DDR4, gAodNvAreaPtr->AodMemBuffer.Twr);
        if (Status == EFI_SUCCESS) {
          gApcbChanged = TRUE;
        }
      } else if (gAodNvAreaPtr->AodMemBuffer.Command == SET_TWTRS) {
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_TIMING_TWTR_S_DDR4, gAodNvAreaPtr->AodMemBuffer.TwtrS);
        if (Status == EFI_SUCCESS) {
          gApcbChanged = TRUE;
        }
      } else if (gAodNvAreaPtr->AodMemBuffer.Command == SET_TWTRL) {
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_TIMING_TWTR_L_DDR4, gAodNvAreaPtr->AodMemBuffer.TwtrL);
        if (Status == EFI_SUCCESS) {
          gApcbChanged = TRUE;
        }
      } else if (gAodNvAreaPtr->AodMemBuffer.Command == SET_TCKE) {
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_TIMING_TCKE_DDR4, gAodNvAreaPtr->AodMemBuffer.TCke);
        if (Status == EFI_SUCCESS) {
          gApcbChanged = TRUE;
        }
      } else if (gAodNvAreaPtr->AodMemBuffer.Command == SET_TCWL) {
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_TIMING_TCWL_DDR4, gAodNvAreaPtr->AodMemBuffer.Tcwl);
        if (Status == EFI_SUCCESS) {
          gApcbChanged = TRUE;
        }
      } else if (gAodNvAreaPtr->AodMemBuffer.Command == SET_TRTP) {
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_TIMING_TRTP_DDR4, gAodNvAreaPtr->AodMemBuffer.Trtp);
        if (Status == EFI_SUCCESS) {
          gApcbChanged = TRUE;
        }
      } else if (gAodNvAreaPtr->AodMemBuffer.Command == SET_TRDRDSC) {
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_TIMING_TRDRD_SC_DDR4, gAodNvAreaPtr->AodMemBuffer.TrdrdSc);
        if (Status == EFI_SUCCESS) {
          gApcbChanged = TRUE;
        }
      } else if (gAodNvAreaPtr->AodMemBuffer.Command == SET_TRDRDSCL) {
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_TIMING_TRDRD_SC_L_CTRL_DDR4, 1);  // Manual
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_TIMING_TRDRD_SC_L_DDR4, gAodNvAreaPtr->AodMemBuffer.TrdrdScL);
        if (Status == EFI_SUCCESS) {
          gApcbChanged = TRUE;
        }
      } else if (gAodNvAreaPtr->AodMemBuffer.Command == SET_TRDRDSD) {
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_TIMING_TRDRD_SD_DDR4, gAodNvAreaPtr->AodMemBuffer.TrdrdSd);
        if (Status == EFI_SUCCESS) {
          gApcbChanged = TRUE;
        }
      } else if (gAodNvAreaPtr->AodMemBuffer.Command == SET_TRDRDDD) {
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_TIMING_TRDRD_DD_DDR4, gAodNvAreaPtr->AodMemBuffer.TrdrdDd);
        if (Status == EFI_SUCCESS) {
          gApcbChanged = TRUE;
        }
      } else if (gAodNvAreaPtr->AodMemBuffer.Command == SET_TWRWRSC) {
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_TIMING_TWRWR_SC_DDR4, gAodNvAreaPtr->AodMemBuffer.TwrwrSc);
        if (Status == EFI_SUCCESS) {
          gApcbChanged = TRUE;
        }
      } else if (gAodNvAreaPtr->AodMemBuffer.Command == SET_TWRWRSCL) {
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_TIMING_TWRWR_SC_L_CTRL_DDR4, 1);  // Manual
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_TIMING_TWRWR_SC_L_DDR4, gAodNvAreaPtr->AodMemBuffer.TwrwrScL);
        if (Status == EFI_SUCCESS) {
          gApcbChanged = TRUE;
        }
      } else if (gAodNvAreaPtr->AodMemBuffer.Command == SET_TWRWRSD) {
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_TIMING_TWRWR_SD_DDR4, gAodNvAreaPtr->AodMemBuffer.TwrwrSd);
        if (Status == EFI_SUCCESS) {
          gApcbChanged = TRUE;
        }
      } else if (gAodNvAreaPtr->AodMemBuffer.Command == SET_TWRWRDD) {
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_TIMING_TWRWR_DD_DDR4, gAodNvAreaPtr->AodMemBuffer.TwrwrDd);
        if (Status == EFI_SUCCESS) {
          gApcbChanged = TRUE;
        }
      } else if (gAodNvAreaPtr->AodMemBuffer.Command == SET_TRDWR) {
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_TIMING_TRDWR_DDR4, gAodNvAreaPtr->AodMemBuffer.Trdwr);
        if (Status == EFI_SUCCESS) {
          gApcbChanged = TRUE;
        }
      } else if (gAodNvAreaPtr->AodMemBuffer.Command == SET_TWRRD) {
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_TIMING_TWRRD_DDR4, gAodNvAreaPtr->AodMemBuffer.Twrrd);
        if (Status == EFI_SUCCESS) {
          gApcbChanged = TRUE;
        }
      } else if (gAodNvAreaPtr->AodMemBuffer.Command == SET_GEAR_DOWN_EN) {
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_GEAR_DOWN_MODE_DDR4, gAodNvAreaPtr->AodMemBuffer.GearDownEn);
        if (Status == EFI_SUCCESS) {
          gApcbChanged = TRUE;
        }
      } else if (gAodNvAreaPtr->AodMemBuffer.Command == SET_CMD_2T) {
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_CTRLLER2_T_MODE_DDR4, gAodNvAreaPtr->AodMemBuffer.Cmd2t);
        if (Status == EFI_SUCCESS) {
          gApcbChanged = TRUE;
        }
      } else if (gAodNvAreaPtr->AodMemBuffer.Command == SET_RTT_NOM) {
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_DATA_BUS_CONFIG_CTL_DDR4, 1);  // Manual
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_CTRLLER_RTT_NOM_DDR4, gAodNvAreaPtr->AodMemBuffer.RttNom);
        if (Status == EFI_SUCCESS) {
          gApcbChanged = TRUE;
        }
      } else if (gAodNvAreaPtr->AodMemBuffer.Command == SET_RTT_WR) {
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_DATA_BUS_CONFIG_CTL_DDR4, 1);  // Manual
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_CTRLLER_RTT_WR_DDR4, gAodNvAreaPtr->AodMemBuffer.RttWR);
        if (Status == EFI_SUCCESS) {
          gApcbChanged = TRUE;
        }
      } else if (gAodNvAreaPtr->AodMemBuffer.Command == SET_RTT_PARK) {
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_DATA_BUS_CONFIG_CTL_DDR4, 1);  // Manual
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_CTRLLER_RTT_PARK_DDR4, gAodNvAreaPtr->AodMemBuffer.RttPark);
        if (Status == EFI_SUCCESS) {
          gApcbChanged = TRUE;
        }
      } else if (gAodNvAreaPtr->AodMemBuffer.Command == SET_POWER_DOWN_EN) {
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_CTRLLER_PWR_DN_EN_DDR4, gAodNvAreaPtr->AodMemBuffer.PowerDownEn);
        if (Status == EFI_SUCCESS) {
          gApcbChanged = TRUE;
        }
      } else if (gAodNvAreaPtr->AodMemBuffer.Command == SET_SMT_EN) {
        // SMT option doesn't change APCB, only set CBS option
      } else if (gAodNvAreaPtr->AodMemBuffer.Command == SW_DOWNCORE_CONFIG) {
        // SW Downcore option doesn't change APCB, only set CBS option
      } else if (gAodNvAreaPtr->AodMemBuffer.Command == SET_EDC_TROTTLER_CONTROL) {
        Status = SetApcbConfig (APCB_ID_CBS_CPU_RELAXED_EDC_THROTTLING, gAodNvAreaPtr->AodMemBuffer.EdcThrottlerCtrl);
        if (Status == EFI_SUCCESS) {
          gApcbChanged = TRUE;
        }
      } else if (gAodNvAreaPtr->AodMemBuffer.Command == SET_ADDR_CMD_SETUP) {
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_CAD_BUS_TIMING_CTL_DDR4, 1);  // Manual
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_ADDR_CMD_SETUP_DDR4, gAodNvAreaPtr->AodMemBuffer.AddrCmdSetup);
        if (Status == EFI_SUCCESS) {
          gApcbChanged = TRUE;
        }
      } else if (gAodNvAreaPtr->AodMemBuffer.Command == SET_CS_ODT_SETUP) {
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_CAD_BUS_TIMING_CTL_DDR4, 1);  // Manual
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_CS_ODT_SETUP_DDR4, gAodNvAreaPtr->AodMemBuffer.CsOdtSetup);
        if (Status == EFI_SUCCESS) {
          gApcbChanged = TRUE;
        }
      } else if (gAodNvAreaPtr->AodMemBuffer.Command == SET_CKE_SETUP) {
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_CAD_BUS_TIMING_CTL_DDR4, 1);  // Manual
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_CKE_SETUP_DDR4, gAodNvAreaPtr->AodMemBuffer.CkeSetup);
        if (Status == EFI_SUCCESS) {
          gApcbChanged = TRUE;
        }
      } else if (gAodNvAreaPtr->AodMemBuffer.Command == SET_CAD_BUS_CLK_DRV_STREN) {
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_CAD_BUS_DRV_STREN_CTL_DDR4, 1);  // Manual
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_CAD_BUS_CLK_DRV_STREN_DDR4, gAodNvAreaPtr->AodMemBuffer.CadBusClkDrvStren);
        if (Status == EFI_SUCCESS) {
          gApcbChanged = TRUE;
        }
      } else if (gAodNvAreaPtr->AodMemBuffer.Command == SET_CAD_BUS_ADDR_DRV_STREN) {
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_CAD_BUS_DRV_STREN_CTL_DDR4, 1);  // Manual
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_CAD_BUS_ADDR_CMD_DRV_STREN_DDR4, gAodNvAreaPtr->AodMemBuffer.CadBusAddrDrvStren);
        if (Status == EFI_SUCCESS) {
          gApcbChanged = TRUE;
        }
      } else if (gAodNvAreaPtr->AodMemBuffer.Command == SET_CAD_BUS_CS_ODT_CMD_DRV_STREN) {
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_CAD_BUS_DRV_STREN_CTL_DDR4, 1);  // Manual
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_CAD_BUS_CS_ODT_DRV_STREN_DDR4, gAodNvAreaPtr->AodMemBuffer.CadBusCsOdtCmdDrvStren);
        if (Status == EFI_SUCCESS) {
          gApcbChanged = TRUE;
        }
      } else if (gAodNvAreaPtr->AodMemBuffer.Command == SET_CAD_BUS_CKE_DRV_STREN) {
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_CAD_BUS_DRV_STREN_CTL_DDR4, 1);  // Manual
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_CAD_BUS_CKE_DRV_STREN_DDR4, gAodNvAreaPtr->AodMemBuffer.CadBusCkeDrvStren);
        if (Status == EFI_SUCCESS) {
          gApcbChanged = TRUE;
        }
      } else if (gAodNvAreaPtr->AodMemBuffer.Command == SET_CLDO_VDDP) {
        Status = SetApcbConfig (APCB_ID_CBS_CMN_CLDO_VDDP_CTL, 1);  // Manual
        Status = SetApcbConfig (APCB_ID_CBS_CMN_CLDOVDD_PVOLTAGE, gAodNvAreaPtr->AodMemBuffer.CldoVddp);
        if (Status == EFI_SUCCESS) {
          gApcbChanged = TRUE;
        }
      } else if (gAodNvAreaPtr->AodMemBuffer.Command == SET_INTERLEAVE_MODE) {
        Status = SetApcbConfig (APCB_ID_CBS_DF_CMN_MEM_INTLV, gAodNvAreaPtr->AodMemBuffer.MemInterleavingMode);
        if (Status == EFI_SUCCESS) {
          gApcbChanged = TRUE;
        }
      } else if (gAodNvAreaPtr->AodMemBuffer.Command == SET_INTERLEAVE_SIZE) {
        Status = SetApcbConfig (APCB_ID_CBS_DF_CMN_MEM_INTLV_SIZE, gAodNvAreaPtr->AodMemBuffer.InterleavingSize);
        if (Status == EFI_SUCCESS) {
          gApcbChanged = TRUE;
        }
      } else if (gAodNvAreaPtr->AodMemBuffer.Command == SET_FCLK_OC_MODE) {
        Status = SetApcbConfig (APCB_ID_CBS_CMN_GNB_FCLK_OC_FLAG, gAodNvAreaPtr->AodMemBuffer.FclkOcMode);
        if (Status == EFI_SUCCESS) {
          gApcbChanged = TRUE;
        }
      } else if (gAodNvAreaPtr->AodMemBuffer.Command == SET_SOC_VID) {
        Status = SetApcbConfig (APCB_ID_CBS_CMN_GNB_SOC_OVERCLOCK_VID, gAodNvAreaPtr->AodMemBuffer.VddcrSocVid);
        if (Status == EFI_SUCCESS) {
          gApcbChanged = TRUE;
        }
      }

      if ((gApcbChanged == TRUE) && (gCommandBufferSaved == FALSE)) {
        IoWrite8 (0x80, 0xD5);
        Status = SetApcbConfig (APCB_ID_CBS_CMN_MEM_OVERCLOCK_DDR4, 1);
        Status = mApcbSmmServiceProtocol->ApcbFlushData (mApcbSmmServiceProtocol);
        if (Status == EFI_SUCCESS) {
          IoWrite8 (0x80, 0xD6);
          gApcbChanged = FALSE;
        }
      }

      UpdateAmdCbsVariables (& (gAodNvAreaPtr->AodMemBuffer));

    }
  }

  FinalizeTransferBuffer (gAodNvAreaPtr, Status);
  DEBUG ((DEBUG_INFO, "\tAodMemClkTimingsUpdateSmmSwSmiCallBack Exit\n"));

  return Status;
}




/*********************************************************************************
 * Name: AodSmmEntryPoint
 *
 * Description
 *   Entry point of the AMD AOD SMM driver, register AOD Smm callbacks
 *
 * Input
 *   ImageHandle : EFI Image Handle for the DXE driver
 *   SystemTable : pointer to the EFI system table
 *
 * Output
 *   EFI_SUCCESS : Module initialized successfully
 *   EFI_ERROR   : Initialization failed (see error for more details)
 *
 *********************************************************************************/
EFI_STATUS
AodSmmEntryPoint (
  IN       EFI_HANDLE         ImageHandle,
  IN       EFI_SYSTEM_TABLE   *SystemTable
  )

{
  EFI_STATUS                       Status;
  FCH_SMM_SW_DISPATCH2_PROTOCOL    *AmdSwDispatch;
  FCH_SMM_SW_REGISTER_CONTEXT      SwRegisterContext;
  EFI_HANDLE                       SwHandle;
  AOD_NV_AREA_UPDATED_PROTOCOL     *AodNvAreaUpdatedProtocolPtr;

  DEBUG ((DEBUG_INFO, "\tAodSmmEntryPoint\n"));

  if (AodFamilyIdentify() == FALSE) {
    return EFI_SUCCESS;
  }

  Status = gSmst->SmmLocateProtocol (
                  &gFchSmmSwDispatch2ProtocolGuid,
                  NULL,
                  &AmdSwDispatch
                  );

  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = gBS->LocateProtocol (&gAodNvAreaUpdatedProtocolGuid, NULL, &AodNvAreaUpdatedProtocolPtr);

  if (!EFI_ERROR (Status)) {
    gAodNvAreaPtr = AodNvAreaUpdatedProtocolPtr->AodNvAreaPtr;
    DEBUG ((DEBUG_INFO, "\tLocate AOD NV Area Pointer = 0x%x\n", gAodNvAreaPtr));
    gAodCpuBiosStruct = AodNvAreaUpdatedProtocolPtr->AodCpuBiosStuctPtr;
    DEBUG ((DEBUG_INFO, "\tLocate AOD CPU BIOS Struct Pointer = 0x%x\n", gAodCpuBiosStruct));
  }

  Status = gSmst->SmmLocateProtocol (
              &gAmdApcbSmmServiceProtocolGuid,
              NULL,
              &mApcbSmmServiceProtocol
              );
  if (EFI_ERROR (Status)) {
    ASSERT (FALSE);
  }

  DEBUG ((DEBUG_INFO, "\tRegister SW SMI for AOD memory clock and timings update\n"));
  SwRegisterContext.AmdSwValue  = PcdGet8(SwSmiCmdAodUpdateMemClkTimings); 
  SwRegisterContext.Order       = 0x80;
  Status = AmdSwDispatch->Register (
                             AmdSwDispatch,
                             AodMemClkTimingsUpdateSmmSwSmiCallBack,
                             &SwRegisterContext,
                             &SwHandle
                             );
  
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  return Status;
}

