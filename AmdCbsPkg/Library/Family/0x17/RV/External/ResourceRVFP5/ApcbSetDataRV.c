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
 **/


//This file is auto generated, don't edit it manually


#include <Base.h>
#include <Library/DebugLib.h>
#include <AmdCbsVariable.h>
#include <Porting.h>
#include <Addendum/Apcb/Inc/RV/APCB.h>
#include <ApcbAutoGenRV.h>

VOID
PrepareCmnTypeAttrib (
  UINT32 *Size,
  APCB_PARAM_ATTRIBUTE *ApcbParaAttrib,
  VOID *CbsVariable
  )
{
  CBS_CONFIG *Setup_Config;
  UINT32     _Size;

  if (CbsVariable == NULL) {
    ASSERT (FALSE);
    return;
  }

  if (Size == NULL) {
    ASSERT (FALSE);
    return;
  }

  _Size = 0;
  Setup_Config = (CBS_CONFIG *) CbsVariable;


  //Relaxed EDC throttling
  if (Setup_Config->CbsCpuRelaxedEdcThrottling != 3) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CPU_RELAXED_EDC_THROTTLING;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //Memory interleaving
  if (Setup_Config->CbsDfCmnMemIntlv != 7) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_DF_CMN_MEM_INTLV;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //Memory interleaving size
  if (Setup_Config->CbsDfCmnMemIntlvSize != 7) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_DF_CMN_MEM_INTLV_SIZE;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //Channel interleaving hash
  if (Setup_Config->CbsDfCmnChnlIntlvHash != 3) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_DF_CMN_CHNL_INTLV_HASH;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //Overclock
  if (Setup_Config->CbsCmnMemOverclockDdr4 != 0xFF) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_OVERCLOCK_DDR4;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //Memory Clock Speed
  if (Setup_Config->CbsCmnMemSpeedDdr4 != 0xFF) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_SPEED_DDR4;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //Tcl
  if (Setup_Config->CbsCmnMemTimingTclDdr4 != 0xFF) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_TIMING_TCL_DDR4;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //Trcdrd
  if (Setup_Config->CbsCmnMemTimingTrcdrdDdr4 != 0xFF) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_TIMING_TRCDRD_DDR4;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //Trcdwr
  if (Setup_Config->CbsCmnMemTimingTrcdwrDdr4 != 0xFF) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_TIMING_TRCDWR_DDR4;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //Trp
  if (Setup_Config->CbsCmnMemTimingTrpDdr4 != 0xFF) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_TIMING_TRP_DDR4;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //Tras
  if (Setup_Config->CbsCmnMemTimingTrasDdr4 != 0xFF) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_TIMING_TRAS_DDR4;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //Trc Ctrl
  if (Setup_Config->CbsCmnMemTimingTrcCtrlDdr4 != 0) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_TIMING_TRC_CTRL_DDR4;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //Trc
  if (ApcbParaAttrib != NULL) {
    ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
    ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_TIMING_TRC_DDR4;
    ApcbParaAttrib->Size = (sizeof (UINT8) -1);
    ApcbParaAttrib++;
  }
  _Size += sizeof (APCB_PARAM_ATTRIBUTE);

  //TrrdS
  if (Setup_Config->CbsCmnMemTimingTrrdSDdr4 != 0xFF) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_TIMING_TRRD_S_DDR4;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //TrrdL
  if (Setup_Config->CbsCmnMemTimingTrrdLDdr4 != 0xFF) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_TIMING_TRRD_L_DDR4;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //Tfaw Ctrl
  if (Setup_Config->CbsCmnMemTimingTfawCtrlDdr4 != 0) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_TIMING_TFAW_CTRL_DDR4;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //Tfaw
  if (ApcbParaAttrib != NULL) {
    ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
    ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_TIMING_TFAW_DDR4;
    ApcbParaAttrib->Size = (sizeof (UINT8) -1);
    ApcbParaAttrib++;
  }
  _Size += sizeof (APCB_PARAM_ATTRIBUTE);

  //TwtrS
  if (Setup_Config->CbsCmnMemTimingTwtrSDdr4 != 0xFF) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_TIMING_TWTR_S_DDR4;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //TwtrL
  if (Setup_Config->CbsCmnMemTimingTwtrLDdr4 != 0xFF) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_TIMING_TWTR_L_DDR4;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //Twr Ctrl
  if (Setup_Config->CbsCmnMemTimingTwrCtrlDdr4 != 0) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_TIMING_TWR_CTRL_DDR4;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //Twr
  if (ApcbParaAttrib != NULL) {
    ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
    ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_TIMING_TWR_DDR4;
    ApcbParaAttrib->Size = (sizeof (UINT8) -1);
    ApcbParaAttrib++;
  }
  _Size += sizeof (APCB_PARAM_ATTRIBUTE);

  //Trcpage Ctrl
  if (Setup_Config->CbsCmnMemTimingTrcpageCtrlDdr4 != 0) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_TIMING_TRCPAGE_CTRL_DDR4;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //Trcpage
  if (ApcbParaAttrib != NULL) {
    ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
    ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_TIMING_TRCPAGE_DDR4;
    ApcbParaAttrib->Size = (sizeof (UINT16) -1);
    ApcbParaAttrib++;
  }
  _Size += sizeof (APCB_PARAM_ATTRIBUTE);

  //TrdrdScL Ctrl
  if (Setup_Config->CbsCmnMemTimingTrdrdScLCtrlDdr4 != 0) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_TIMING_TRDRD_SC_L_CTRL_DDR4;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //TrdrdScL
  if (ApcbParaAttrib != NULL) {
    ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
    ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_TIMING_TRDRD_SC_L_DDR4;
    ApcbParaAttrib->Size = (sizeof (UINT8) -1);
    ApcbParaAttrib++;
  }
  _Size += sizeof (APCB_PARAM_ATTRIBUTE);

  //TwrwrScL Ctrl
  if (Setup_Config->CbsCmnMemTimingTwrwrScLCtrlDdr4 != 0) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_TIMING_TWRWR_SC_L_CTRL_DDR4;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //TwrwrScL
  if (ApcbParaAttrib != NULL) {
    ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
    ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_TIMING_TWRWR_SC_L_DDR4;
    ApcbParaAttrib->Size = (sizeof (UINT8) -1);
    ApcbParaAttrib++;
  }
  _Size += sizeof (APCB_PARAM_ATTRIBUTE);

  //Trfc Ctrl
  if (Setup_Config->CbsCmnMemTimingTrfcCtrlDdr4 != 0) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_TIMING_TRFC_CTRL_DDR4;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //Trfc
  if (ApcbParaAttrib != NULL) {
    ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
    ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_TIMING_TRFC_DDR4;
    ApcbParaAttrib->Size = (sizeof (UINT16) -1);
    ApcbParaAttrib++;
  }
  _Size += sizeof (APCB_PARAM_ATTRIBUTE);

  //Trfc2 Ctrl
  if (Setup_Config->CbsCmnMemTimingTrfc2CtrlDdr4 != 0) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_TIMING_TRFC2_CTRL_DDR4;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //Trfc2
  if (ApcbParaAttrib != NULL) {
    ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
    ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_TIMING_TRFC2_DDR4;
    ApcbParaAttrib->Size = (sizeof (UINT16) -1);
    ApcbParaAttrib++;
  }
  _Size += sizeof (APCB_PARAM_ATTRIBUTE);

  //Trfc4 Ctrl
  if (Setup_Config->CbsCmnMemTimingTrfc4CtrlDdr4 != 0) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_TIMING_TRFC4_CTRL_DDR4;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //Trfc4
  if (ApcbParaAttrib != NULL) {
    ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
    ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_TIMING_TRFC4_DDR4;
    ApcbParaAttrib->Size = (sizeof (UINT16) -1);
    ApcbParaAttrib++;
  }
  _Size += sizeof (APCB_PARAM_ATTRIBUTE);

  //Fail_CNT
  if (ApcbParaAttrib != NULL) {
    ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
    ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_OVERCLOCK_FAIL_CNT;
    ApcbParaAttrib->Size = (sizeof (UINT8) -1);
    ApcbParaAttrib++;
  }
  _Size += sizeof (APCB_PARAM_ATTRIBUTE);

  //ProcODT
  if (Setup_Config->CbsCmnMemCtrllerProcOdtDdr4 != 0xFF) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_CTRLLER_PROC_ODT_DDR4;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //Tcwl
  if (Setup_Config->CbsCmnMemTimingTcwlDdr4 != 0xFF) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_TIMING_TCWL_DDR4;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //Trtp
  if (Setup_Config->CbsCmnMemTimingTrtpDdr4 != 0xFF) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_TIMING_TRTP_DDR4;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //Tcke
  if (Setup_Config->CbsCmnMemTimingTckeDdr4 != 0xFF) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_TIMING_TCKE_DDR4;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //TrdrdSc
  if (Setup_Config->CbsCmnMemTimingTrdrdScDdr4 != 0xFF) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_TIMING_TRDRD_SC_DDR4;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //TrdrdSd
  if (Setup_Config->CbsCmnMemTimingTrdrdSdDdr4 != 0xFF) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_TIMING_TRDRD_SD_DDR4;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //TrdrdDd
  if (Setup_Config->CbsCmnMemTimingTrdrdDdDdr4 != 0xFF) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_TIMING_TRDRD_DD_DDR4;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //TwrwrSc
  if (Setup_Config->CbsCmnMemTimingTwrwrScDdr4 != 0xFF) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_TIMING_TWRWR_SC_DDR4;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //TwrwrSd
  if (Setup_Config->CbsCmnMemTimingTwrwrSdDdr4 != 0xFF) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_TIMING_TWRWR_SD_DDR4;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //TwrwrDd
  if (Setup_Config->CbsCmnMemTimingTwrwrDdDdr4 != 0xFF) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_TIMING_TWRWR_DD_DDR4;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //Trdwr
  if (Setup_Config->CbsCmnMemTimingTrdwrDdr4 != 0xFF) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_TIMING_TRDWR_DDR4;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //Twrrd
  if (Setup_Config->CbsCmnMemTimingTwrrdDdr4 != 0xFF) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_TIMING_TWRRD_DDR4;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //Cmd2T
  if (Setup_Config->CbsCmnMemCtrller2TModeDdr4 != 0xFF) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_CTRLLER2_T_MODE_DDR4;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //Gear Down Mode
  if (Setup_Config->CbsCmnMemGearDownModeDdr4 != 0xFF) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_GEAR_DOWN_MODE_DDR4;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //Data Mask
  if (Setup_Config->CbsCmnMemDataMaskDdr4 != 0xFF) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_DATA_MASK_DDR4;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //Power Down Enable
  if (Setup_Config->CbsCmnMemCtrllerPwrDnEnDdr4 != 0xFF) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_CTRLLER_PWR_DN_EN_DDR4;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //CAD Bus Timing User Controls
  if (Setup_Config->CbsCmnMemCadBusTimingCtlDdr4 != 0xFF) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_CAD_BUS_TIMING_CTL_DDR4;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //AddrCmdSetup
  if (ApcbParaAttrib != NULL) {
    ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
    ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_ADDR_CMD_SETUP_DDR4;
    ApcbParaAttrib->Size = (sizeof (UINT8) -1);
    ApcbParaAttrib++;
  }
  _Size += sizeof (APCB_PARAM_ATTRIBUTE);

  //CsOdtSetup
  if (ApcbParaAttrib != NULL) {
    ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
    ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_CS_ODT_SETUP_DDR4;
    ApcbParaAttrib->Size = (sizeof (UINT8) -1);
    ApcbParaAttrib++;
  }
  _Size += sizeof (APCB_PARAM_ATTRIBUTE);

  //CkeSetup
  if (ApcbParaAttrib != NULL) {
    ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
    ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_CKE_SETUP_DDR4;
    ApcbParaAttrib->Size = (sizeof (UINT8) -1);
    ApcbParaAttrib++;
  }
  _Size += sizeof (APCB_PARAM_ATTRIBUTE);

  //CAD Bus Drive Strength User Controls
  if (Setup_Config->CbsCmnMemCadBusDrvStrenCtlDdr4 != 0xFF) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_CAD_BUS_DRV_STREN_CTL_DDR4;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //ClkDrvStren
  if (Setup_Config->CbsCmnMemCadBusClkDrvStrenDdr4 != 0xFF) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_CAD_BUS_CLK_DRV_STREN_DDR4;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //AddrCmdDrvStren
  if (Setup_Config->CbsCmnMemCadBusAddrCmdDrvStrenDdr4 != 0xFF) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_CAD_BUS_ADDR_CMD_DRV_STREN_DDR4;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //CsOdtDrvStren
  if (Setup_Config->CbsCmnMemCadBusCsOdtDrvStrenDdr4 != 0xFF) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_CAD_BUS_CS_ODT_DRV_STREN_DDR4;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //CkeDrvStren
  if (Setup_Config->CbsCmnMemCadBusCkeDrvStrenDdr4 != 0xFF) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_CAD_BUS_CKE_DRV_STREN_DDR4;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //Data Bus Configuration User Controls
  if (Setup_Config->CbsCmnMemDataBusConfigCtlDdr4 != 0xFF) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_DATA_BUS_CONFIG_CTL_DDR4;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //RttNom
  if (Setup_Config->CbsCmnMemCtrllerRttNomDdr4 != 0xFF) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_CTRLLER_RTT_NOM_DDR4;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //RttWr
  if (Setup_Config->CbsCmnMemCtrllerRttWrDdr4 != 0xFF) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_CTRLLER_RTT_WR_DDR4;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //RttPark
  if (Setup_Config->CbsCmnMemCtrllerRttParkDdr4 != 0xFF) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_CTRLLER_RTT_PARK_DDR4;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //Data Poisoning
  if (Setup_Config->CbsCmnMemDataPoisoningDdr4 != 0xFF) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_DATA_POISONING_DDR4;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //DRAM ECC Symbol Size
  if (Setup_Config->CbsCmnMemCtrllerDramEccSymbolSizeDdr4 != 0xFF) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_CTRLLER_DRAM_ECC_SYMBOL_SIZE_DDR4;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //DRAM ECC Enable
  if (Setup_Config->CbsCmnMemCtrllerDramEccEnDdr4 != 0xFF) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_CTRLLER_DRAM_ECC_EN_DDR4;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //TSME
  if (Setup_Config->CbsCmnMemTsmeDdr4 != 0xFF) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_TSME_DDR4;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //Chipselect Interleaving
  if (Setup_Config->CbsCmnMemMappingBankInterleaveDdr4 != 0xFF) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_MAPPING_BANK_INTERLEAVE_DDR4;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //BankGroupSwap
  if (Setup_Config->CbsCmnMemCtrllerBankGroupSwapDdr4 != 0xFF) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_CTRLLER_BANK_GROUP_SWAP_DDR4;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //BankGroupSwapAlt
  if (Setup_Config->CbsCmnMemCtrllerBankGroupSwapAltDdr4 != 0xFF) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_CTRLLER_BANK_GROUP_SWAP_ALT_DDR4;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //Address Hash Bank
  if (Setup_Config->CbsCmnMemAddressHashBankDdr4 != 0xFF) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_ADDRESS_HASH_BANK_DDR4;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //Address Hash CS
  if (Setup_Config->CbsCmnMemAddressHashCsDdr4 != 0xFF) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_ADDRESS_HASH_CS_DDR4;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //MBIST Enable
  if (Setup_Config->CbsCmnMemMbistEn != 0xFF) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_MBIST_EN;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //MBIST Test Mode
  if (Setup_Config->CbsCmnMemMbistSubTest != 0xFF) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_MBIST_SUB_TEST;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //MBIST Aggressors
  if (Setup_Config->CbsCmnMemMbistAggressors != 0xFF) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_MBIST_AGGRESSORS;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //MBIST Per Bit Slave Die Reporting
  if (Setup_Config->CbsCmnMemMbistPerBitSlaveDieReporting != 0xFF) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_MEM_MBIST_PER_BIT_SLAVE_DIE_REPORTING;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //UMA Mode
  if (Setup_Config->CbsCmnGnbGfxUmaMode != 0xf) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_GNB_GFX_UMA_MODE;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //UMA Version
  if (Setup_Config->CbsCmnGnbGfxUmaVersion != 0xf) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_GNB_GFX_UMA_VERSION;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //Display Resulotuon
  if (Setup_Config->CbsCmnGnbGfxDisplayResolution != 0xff) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_GNB_GFX_DISPLAY_RESOLUTION;
      ApcbParaAttrib->Size = (sizeof (UINT8) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //UMA Frame buffer Size
  if (Setup_Config->CbsCmnGnbGfxUmaFrameBufferSize != 0xffffffff) {
    if (ApcbParaAttrib != NULL) {
      ApcbParaAttrib->TimePoint = APCB_TIME_POINT_ANY;
      ApcbParaAttrib->Token = APCB_TOKEN_CBS_CMN_GNB_GFX_UMA_FRAME_BUFFER_SIZE;
      ApcbParaAttrib->Size = (sizeof (UINT32) -1);
      ApcbParaAttrib++;
    }
    _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  }

  //End
  if (ApcbParaAttrib != NULL) {
    ApcbParaAttrib->TimePoint = 0;
    ApcbParaAttrib->Token = APCB_TOKEN_CBS_DBG_LIMIT;
    ApcbParaAttrib->Size = 0;
    ApcbParaAttrib->Reserved = 0;
  }

  _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  *Size = _Size;
}

VOID
PrepareCmnTypeValue (
  UINT32 *Size,
  UINT8 *ApcbParaValue,
  VOID *CbsVariable
  )
{
  CBS_CONFIG *Setup_Config;
  UINT32     _Size;

  if (CbsVariable == NULL) {
    ASSERT (FALSE);
    return;
  }

  if (Size == NULL) {
    ASSERT (FALSE);
    return;
  }

  _Size = 0;
  Setup_Config = (CBS_CONFIG *) CbsVariable;

  //Relaxed EDC throttling
  if (Setup_Config->CbsCpuRelaxedEdcThrottling != 3) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCpuRelaxedEdcThrottling;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //Memory interleaving
  if (Setup_Config->CbsDfCmnMemIntlv != 7) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsDfCmnMemIntlv;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //Memory interleaving size
  if (Setup_Config->CbsDfCmnMemIntlvSize != 7) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsDfCmnMemIntlvSize;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //Channel interleaving hash
  if (Setup_Config->CbsDfCmnChnlIntlvHash != 3) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsDfCmnChnlIntlvHash;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //Overclock
  if (Setup_Config->CbsCmnMemOverclockDdr4 != 0xFF) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemOverclockDdr4;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //Memory Clock Speed
  if (Setup_Config->CbsCmnMemSpeedDdr4 != 0xFF) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemSpeedDdr4;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //Tcl
  if (Setup_Config->CbsCmnMemTimingTclDdr4 != 0xFF) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemTimingTclDdr4;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //Trcdrd
  if (Setup_Config->CbsCmnMemTimingTrcdrdDdr4 != 0xFF) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemTimingTrcdrdDdr4;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //Trcdwr
  if (Setup_Config->CbsCmnMemTimingTrcdwrDdr4 != 0xFF) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemTimingTrcdwrDdr4;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //Trp
  if (Setup_Config->CbsCmnMemTimingTrpDdr4 != 0xFF) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemTimingTrpDdr4;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //Tras
  if (Setup_Config->CbsCmnMemTimingTrasDdr4 != 0xFF) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemTimingTrasDdr4;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //Trc Ctrl
  if (Setup_Config->CbsCmnMemTimingTrcCtrlDdr4 != 0) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemTimingTrcCtrlDdr4;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //Trc
  if (ApcbParaValue != NULL) {
    * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemTimingTrcDdr4;
    ApcbParaValue += sizeof (UINT8);
  }
  _Size += sizeof (UINT8);

  //TrrdS
  if (Setup_Config->CbsCmnMemTimingTrrdSDdr4 != 0xFF) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemTimingTrrdSDdr4;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //TrrdL
  if (Setup_Config->CbsCmnMemTimingTrrdLDdr4 != 0xFF) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemTimingTrrdLDdr4;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //Tfaw Ctrl
  if (Setup_Config->CbsCmnMemTimingTfawCtrlDdr4 != 0) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemTimingTfawCtrlDdr4;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //Tfaw
  if (ApcbParaValue != NULL) {
    * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemTimingTfawDdr4;
    ApcbParaValue += sizeof (UINT8);
  }
  _Size += sizeof (UINT8);

  //TwtrS
  if (Setup_Config->CbsCmnMemTimingTwtrSDdr4 != 0xFF) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemTimingTwtrSDdr4;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //TwtrL
  if (Setup_Config->CbsCmnMemTimingTwtrLDdr4 != 0xFF) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemTimingTwtrLDdr4;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //Twr Ctrl
  if (Setup_Config->CbsCmnMemTimingTwrCtrlDdr4 != 0) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemTimingTwrCtrlDdr4;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //Twr
  if (ApcbParaValue != NULL) {
    * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemTimingTwrDdr4;
    ApcbParaValue += sizeof (UINT8);
  }
  _Size += sizeof (UINT8);

  //Trcpage Ctrl
  if (Setup_Config->CbsCmnMemTimingTrcpageCtrlDdr4 != 0) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemTimingTrcpageCtrlDdr4;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //Trcpage
  if (ApcbParaValue != NULL) {
    * ((UINT16 *) ApcbParaValue) = Setup_Config->CbsCmnMemTimingTrcpageDdr4;
    ApcbParaValue += sizeof (UINT16);
  }
  _Size += sizeof (UINT16);

  //TrdrdScL Ctrl
  if (Setup_Config->CbsCmnMemTimingTrdrdScLCtrlDdr4 != 0) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemTimingTrdrdScLCtrlDdr4;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //TrdrdScL
  if (ApcbParaValue != NULL) {
    * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemTimingTrdrdScLDdr4;
    ApcbParaValue += sizeof (UINT8);
  }
  _Size += sizeof (UINT8);

  //TwrwrScL Ctrl
  if (Setup_Config->CbsCmnMemTimingTwrwrScLCtrlDdr4 != 0) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemTimingTwrwrScLCtrlDdr4;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //TwrwrScL
  if (ApcbParaValue != NULL) {
    * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemTimingTwrwrScLDdr4;
    ApcbParaValue += sizeof (UINT8);
  }
  _Size += sizeof (UINT8);

  //Trfc Ctrl
  if (Setup_Config->CbsCmnMemTimingTrfcCtrlDdr4 != 0) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemTimingTrfcCtrlDdr4;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //Trfc
  if (ApcbParaValue != NULL) {
    * ((UINT16 *) ApcbParaValue) = Setup_Config->CbsCmnMemTimingTrfcDdr4;
    ApcbParaValue += sizeof (UINT16);
  }
  _Size += sizeof (UINT16);

  //Trfc2 Ctrl
  if (Setup_Config->CbsCmnMemTimingTrfc2CtrlDdr4 != 0) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemTimingTrfc2CtrlDdr4;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //Trfc2
  if (ApcbParaValue != NULL) {
    * ((UINT16 *) ApcbParaValue) = Setup_Config->CbsCmnMemTimingTrfc2Ddr4;
    ApcbParaValue += sizeof (UINT16);
  }
  _Size += sizeof (UINT16);

  //Trfc4 Ctrl
  if (Setup_Config->CbsCmnMemTimingTrfc4CtrlDdr4 != 0) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemTimingTrfc4CtrlDdr4;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //Trfc4
  if (ApcbParaValue != NULL) {
    * ((UINT16 *) ApcbParaValue) = Setup_Config->CbsCmnMemTimingTrfc4Ddr4;
    ApcbParaValue += sizeof (UINT16);
  }
  _Size += sizeof (UINT16);

  //Fail_CNT
  if (ApcbParaValue != NULL) {
    * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemOverclockFailCNT;
    ApcbParaValue += sizeof (UINT8);
  }
  _Size += sizeof (UINT8);

  //ProcODT
  if (Setup_Config->CbsCmnMemCtrllerProcOdtDdr4 != 0xFF) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemCtrllerProcOdtDdr4;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //Tcwl
  if (Setup_Config->CbsCmnMemTimingTcwlDdr4 != 0xFF) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemTimingTcwlDdr4;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //Trtp
  if (Setup_Config->CbsCmnMemTimingTrtpDdr4 != 0xFF) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemTimingTrtpDdr4;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //Tcke
  if (Setup_Config->CbsCmnMemTimingTckeDdr4 != 0xFF) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemTimingTckeDdr4;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //TrdrdSc
  if (Setup_Config->CbsCmnMemTimingTrdrdScDdr4 != 0xFF) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemTimingTrdrdScDdr4;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //TrdrdSd
  if (Setup_Config->CbsCmnMemTimingTrdrdSdDdr4 != 0xFF) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemTimingTrdrdSdDdr4;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //TrdrdDd
  if (Setup_Config->CbsCmnMemTimingTrdrdDdDdr4 != 0xFF) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemTimingTrdrdDdDdr4;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //TwrwrSc
  if (Setup_Config->CbsCmnMemTimingTwrwrScDdr4 != 0xFF) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemTimingTwrwrScDdr4;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //TwrwrSd
  if (Setup_Config->CbsCmnMemTimingTwrwrSdDdr4 != 0xFF) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemTimingTwrwrSdDdr4;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //TwrwrDd
  if (Setup_Config->CbsCmnMemTimingTwrwrDdDdr4 != 0xFF) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemTimingTwrwrDdDdr4;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //Trdwr
  if (Setup_Config->CbsCmnMemTimingTrdwrDdr4 != 0xFF) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemTimingTrdwrDdr4;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //Twrrd
  if (Setup_Config->CbsCmnMemTimingTwrrdDdr4 != 0xFF) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemTimingTwrrdDdr4;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //Cmd2T
  if (Setup_Config->CbsCmnMemCtrller2TModeDdr4 != 0xFF) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemCtrller2TModeDdr4;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //Gear Down Mode
  if (Setup_Config->CbsCmnMemGearDownModeDdr4 != 0xFF) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemGearDownModeDdr4;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //Data Mask
  if (Setup_Config->CbsCmnMemDataMaskDdr4 != 0xFF) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemDataMaskDdr4;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //Power Down Enable
  if (Setup_Config->CbsCmnMemCtrllerPwrDnEnDdr4 != 0xFF) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemCtrllerPwrDnEnDdr4;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //CAD Bus Timing User Controls
  if (Setup_Config->CbsCmnMemCadBusTimingCtlDdr4 != 0xFF) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemCadBusTimingCtlDdr4;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //AddrCmdSetup
  if (ApcbParaValue != NULL) {
    * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemAddrCmdSetupDdr4;
    ApcbParaValue += sizeof (UINT8);
  }
  _Size += sizeof (UINT8);

  //CsOdtSetup
  if (ApcbParaValue != NULL) {
    * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemCsOdtSetupDdr4;
    ApcbParaValue += sizeof (UINT8);
  }
  _Size += sizeof (UINT8);

  //CkeSetup
  if (ApcbParaValue != NULL) {
    * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemCkeSetupDdr4;
    ApcbParaValue += sizeof (UINT8);
  }
  _Size += sizeof (UINT8);

  //CAD Bus Drive Strength User Controls
  if (Setup_Config->CbsCmnMemCadBusDrvStrenCtlDdr4 != 0xFF) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemCadBusDrvStrenCtlDdr4;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //ClkDrvStren
  if (Setup_Config->CbsCmnMemCadBusClkDrvStrenDdr4 != 0xFF) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemCadBusClkDrvStrenDdr4;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //AddrCmdDrvStren
  if (Setup_Config->CbsCmnMemCadBusAddrCmdDrvStrenDdr4 != 0xFF) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemCadBusAddrCmdDrvStrenDdr4;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //CsOdtDrvStren
  if (Setup_Config->CbsCmnMemCadBusCsOdtDrvStrenDdr4 != 0xFF) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemCadBusCsOdtDrvStrenDdr4;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //CkeDrvStren
  if (Setup_Config->CbsCmnMemCadBusCkeDrvStrenDdr4 != 0xFF) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemCadBusCkeDrvStrenDdr4;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //Data Bus Configuration User Controls
  if (Setup_Config->CbsCmnMemDataBusConfigCtlDdr4 != 0xFF) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemDataBusConfigCtlDdr4;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //RttNom
  if (Setup_Config->CbsCmnMemCtrllerRttNomDdr4 != 0xFF) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemCtrllerRttNomDdr4;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //RttWr
  if (Setup_Config->CbsCmnMemCtrllerRttWrDdr4 != 0xFF) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemCtrllerRttWrDdr4;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //RttPark
  if (Setup_Config->CbsCmnMemCtrllerRttParkDdr4 != 0xFF) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemCtrllerRttParkDdr4;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //Data Poisoning
  if (Setup_Config->CbsCmnMemDataPoisoningDdr4 != 0xFF) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemDataPoisoningDdr4;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //DRAM ECC Symbol Size
  if (Setup_Config->CbsCmnMemCtrllerDramEccSymbolSizeDdr4 != 0xFF) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemCtrllerDramEccSymbolSizeDdr4;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //DRAM ECC Enable
  if (Setup_Config->CbsCmnMemCtrllerDramEccEnDdr4 != 0xFF) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemCtrllerDramEccEnDdr4;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //TSME
  if (Setup_Config->CbsCmnMemTsmeDdr4 != 0xFF) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemTsmeDdr4;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //Chipselect Interleaving
  if (Setup_Config->CbsCmnMemMappingBankInterleaveDdr4 != 0xFF) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemMappingBankInterleaveDdr4;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //BankGroupSwap
  if (Setup_Config->CbsCmnMemCtrllerBankGroupSwapDdr4 != 0xFF) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemCtrllerBankGroupSwapDdr4;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //BankGroupSwapAlt
  if (Setup_Config->CbsCmnMemCtrllerBankGroupSwapAltDdr4 != 0xFF) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemCtrllerBankGroupSwapAltDdr4;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //Address Hash Bank
  if (Setup_Config->CbsCmnMemAddressHashBankDdr4 != 0xFF) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemAddressHashBankDdr4;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //Address Hash CS
  if (Setup_Config->CbsCmnMemAddressHashCsDdr4 != 0xFF) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemAddressHashCsDdr4;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //MBIST Enable
  if (Setup_Config->CbsCmnMemMbistEn != 0xFF) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemMbistEn;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //MBIST Test Mode
  if (Setup_Config->CbsCmnMemMbistSubTest != 0xFF) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemMbistSubTest;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //MBIST Aggressors
  if (Setup_Config->CbsCmnMemMbistAggressors != 0xFF) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemMbistAggressors;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //MBIST Per Bit Slave Die Reporting
  if (Setup_Config->CbsCmnMemMbistPerBitSlaveDieReporting != 0xFF) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnMemMbistPerBitSlaveDieReporting;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //UMA Mode
  if (Setup_Config->CbsCmnGnbGfxUmaMode != 0xf) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnGnbGfxUmaMode;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //UMA Version
  if (Setup_Config->CbsCmnGnbGfxUmaVersion != 0xf) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnGnbGfxUmaVersion;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //Display Resulotuon
  if (Setup_Config->CbsCmnGnbGfxDisplayResolution != 0xff) {
    if (ApcbParaValue != NULL) {
      * ((UINT8 *) ApcbParaValue) = Setup_Config->CbsCmnGnbGfxDisplayResolution;
      ApcbParaValue += sizeof (UINT8);
    }
    _Size += sizeof (UINT8);
  }

  //UMA Frame buffer Size
  if (Setup_Config->CbsCmnGnbGfxUmaFrameBufferSize != 0xffffffff) {
    if (ApcbParaValue != NULL) {
      * ((UINT32 *) ApcbParaValue) = Setup_Config->CbsCmnGnbGfxUmaFrameBufferSize;
      ApcbParaValue += sizeof (UINT32);
    }
    _Size += sizeof (UINT32);
  }

  //End
  *Size = _Size;
}


VOID
PrepareDbgTypeAttrib (
  UINT32 *Size,
  APCB_PARAM_ATTRIBUTE *ApcbParaAttrib,
  VOID *CbsVariable
  )
{
  CBS_CONFIG *Setup_Config;
  UINT32     _Size;

  if (CbsVariable == NULL) {
    ASSERT (FALSE);
    return;
  }

  if (Size == NULL) {
    ASSERT (FALSE);
    return;
  }

  _Size = 0;
  Setup_Config = (CBS_CONFIG *) CbsVariable;


  //End
  if (ApcbParaAttrib != NULL) {
    ApcbParaAttrib->TimePoint = 0;
    ApcbParaAttrib->Token = APCB_TOKEN_CBS_DBG_LIMIT;
    ApcbParaAttrib->Size = 0;
    ApcbParaAttrib->Reserved = 0;
  }

  _Size += sizeof (APCB_PARAM_ATTRIBUTE);
  *Size = _Size;
}

VOID
PrepareDbgTypeValue (
  UINT32 *Size,
  UINT8 *ApcbParaValue,
  VOID *CbsVariable
  )
{
  CBS_CONFIG *Setup_Config;
  UINT32     _Size;

  if (CbsVariable == NULL) {
    ASSERT (FALSE);
    return;
  }

  if (Size == NULL) {
    ASSERT (FALSE);
    return;
  }

  _Size = 0;
  Setup_Config = (CBS_CONFIG *) CbsVariable;

  //End
  *Size = _Size;
}


