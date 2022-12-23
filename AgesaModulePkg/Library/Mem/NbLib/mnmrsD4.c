/* $NoKeywords:$ */
/**
 * @file
 *
 * mnmrsd4.c
 *
 * DDR4 Mode Register Handling Routines
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/NB)
 * @e \$Revision: 324927 $ @e \$Date: 2015-08-24 15:09:45 +0800 (Mon, 24 Aug 2015) $
 *
 **/
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
*
*/

/*
 *----------------------------------------------------------------------------
 *                                MODULES USED
 *
 *----------------------------------------------------------------------------
 */



#include "AGESA.h"
#include "Library/AmdBaseLib.h"
#include "Library/IdsLib.h"
#include "Ids.h"
#include "mm.h"
#include "mn.h"
#include "mt.h"
#include "mu.h"
#include "mnreg.h"
#include "merrhdl.h"
#include "cpuRegisters.h"
#include "Filecode.h"
CODE_GROUP (G1_PEICC)
RDATA_GROUP (G1_PEICC)

#define FILECODE LIBRARY_MEM_NBLIB_MNMRSD4_FILECODE

/*----------------------------------------------------------------------------
 *                          DEFINITIONS AND MACROS
 *
 *----------------------------------------------------------------------------
 */
/*----------------------------------------------------------------------------
 *                           TYPEDEFS AND STRUCTURES
 *
 *----------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------
 *                        PROTOTYPES OF LOCAL FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------
 *                            EXPORTED FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function calculates the value of MR0 for DDR4
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 *     @return          MR0 value
 *
 */

UINT32
MemNCalcD4MR0 (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  // CL Value Table          9 10 11 12 13 14 15 16  17 18  19 20  21  22  23  24  25  26  27  28  29  30  31  32
  CONST UINT8 CLValues[] = { 0, 1, 2, 3, 4, 5, 6, 7, 13, 8, 14, 9, 15, 10, 12, 11, 16, 17, 18, 19, 20, 21, 22, 23};
  // WR Value Table          10 12 14 16 18 20 22 24 26
  CONST UINT8 WRValues[] = { 0,  1, 2, 3, 4, 5, 7, 6, 8};
  UINT32 MrsAddress;
  UINT8  TclIndex;
  UINT32 TclEnc;
  UINT8  TwrIndex;
  UINT32 TwrEnc;
  //
  // A1:A0 Burst Length
  //   Based on F2x[1,0]84[BurstCtrl]
  //
  MrsAddress = MemNGetBitFieldNb (NBPtr, BFBurstCtrl);
  //
  // A3 Burst Type = 1 (interleaved)
  //
  MrsAddress |= (UINT16) 1 << 3;
  //
  // A12, A6:A4, A2 Read CAS latency
  //
  TclIndex = (UINT8) MemNGetBitFieldNb (NBPtr, BFTcl);
  TclIndex = (TclIndex < 9) ? 0 : TclIndex - 9;
  ASSERT (TclIndex < sizeof (CLValues));
  TclEnc = CLValues[TclIndex];
  ASSERT (TclEnc < 32);
  MrsAddress |= (TclEnc & 0x010) << 8;
  MrsAddress |= (TclEnc & 0x0E) << 3;
  MrsAddress |= (TclEnc & 1) << 2;
  //
  // A7 TM = 0
  //
  // A8 DllReset = 1
  //
  MrsAddress |= 0x00000100;
  //
  // A13, A11:A9 Write Recovery(tWR) and Read to Precharge(tRTP)
  //
  TwrIndex = (UINT8) MemNGetBitFieldNb (NBPtr, BFTwr);
  TwrIndex = (TwrIndex < 10) ? 0 : (TwrIndex - 10) / 2;
  ASSERT (TwrIndex < sizeof (WRValues));
  TwrEnc = WRValues[TwrIndex];
  MrsAddress |= (TwrEnc & 8) << 10;
  MrsAddress |= (TwrEnc & 7) << 9;
  //
  // A17,A13:A12 = 0
  //
  return MrsAddress;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function calculates the value of MR1 for DDR4
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]       ChipSel - Rank to be trained
 *
 *     @return          MR1 value
 *
 */

UINT32
MemNCalcD4MR1 (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 ChipSel
  )
{
  UINT32 MrsAddress;
  UINT32 RttNom;
  //
  // A0 DLL Enable = 1
  //
  MrsAddress = 1;
  //
  // A2:A1 Output Driver Impedance control (DIC):
  //   00 = RZQ/7
  //   01 = RZQ/5
  MrsAddress |= ((UINT16) 0 << 1);
  //
  // A4:A3 Additive Latency(AL) = 0
  //
  // A6:A5 Reserved = 0
  //
  // A7 Write Leveling Enable = 0
  //
  // A10:A8 Nominal termination resistance of ODT (RTT_NOM):
  //   0 = RTT_NOM Disable  4 = RZQ/1
  //   1 = RZQ/4            5 = RZQ/5
  //   2 = RZQ/2            6 = RZQ/3
  //   3 = RZQ/6            7 = RZQ/7
  //   Different CS may have different RTT.
  //
  RttNom = NBPtr->PsPtr->RttNom[ChipSel];
  IDS_OPTION_HOOK (IDS_MEM_RTTNOM, &RttNom, &NBPtr->MemPtr->StdHeader);
  MrsAddress |= ((RttNom & 0x7) << 8);
  //
  // A11 TDQS = (IF (mixed channel of x4 and x8 DIMMs && x8 DRAM) THEN 1 ELSE 0 ENDIF.)
  //
  if ((NBPtr->DCTPtr->Timings.Dimmx4Present != 0) && (NBPtr->DCTPtr->Timings.Dimmx8Present != 0)) {
    if ((NBPtr->DCTPtr->Timings.Dimmx8Present & ((UINT8) 1 << (ChipSel >> 1))) != 0) {
      MrsAddress |= ((UINT16) 1 << 11);
    }
  }
  //
  // A12 Output disable (QOFF) = 0
  //
  // A17,A13 Reserved
  //
  return MrsAddress;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function calculates the value of MR2 for DDR4
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]       ChipSel - Rank to be trained
 *
 *     @return          MR2 value
 *
 */

UINT32
MemNCalcD4MR2 (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 ChipSel
  )
{
  // CWL Value Table          9  10  11  12     13  14    15  16    17  18     19  20
  CONST UINT8 CWLValues[] = { 0,  1,  2,  3,  0xFF,  4, 0xFF,  5, 0xFF,  6,  0xFF,  7 };
  UINT32 MrsAddress;
  UINT32 RttWr;
  UINT8  TcwlIndex;
  UINT32 TcwlEnc;

  MrsAddress = 0;
  //
  // A1:A0 TRR Mode - BAn = 00b
  //
  // A5:A3 CAS Write Latency (tCWL)
  //    tCWL  A5:A3
  //     9      0
  //     10     1
  //     11     2
  //     12     3
  //     14     4
  //     16     5
  //     18     6
  //     20     7
  //
  TcwlIndex = (UINT8) MemNGetBitFieldNb (NBPtr, BFTcwl);
  TcwlIndex = (TcwlIndex < 9) ? 0 : TcwlIndex - 9;
  ASSERT (TcwlIndex < sizeof (CWLValues));
  TcwlEnc = CWLValues[TcwlIndex];
  ASSERT (TcwlEnc < 16);
  MrsAddress |= (TcwlEnc & 0x07) << 3;
  //
  // A7:A6 Low Power Array Self Refresh (LP ASR) = 11b (ASR Mode)
  //
  MrsAddress |= (3 << 6);
  //
  // A8:A2 TRR Mode - BGn = 0
  //
  // A11:A9 Dynamic termination during writes (RTT_WR)
  // 0 = Dynamic ODT Off         3 = Hi-Z
  // 1 = RZQ/2                   4 = RZQ/3
  // 2 = RZQ/1
  //
  RttWr = NBPtr->PsPtr->RttWr[ChipSel];
  IDS_OPTION_HOOK (IDS_MEM_RTTWR, &RttWr, &NBPtr->MemPtr->StdHeader);
  ASSERT (RttWr <= 4);
  MrsAddress |= (RttWr << 9);
  //
  // A12 Write CRC = 0
  //
  // A13 TRR = 0 (Disable)
  //
  // A17 Reserved = 0
  //
  return MrsAddress;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function calculates the value of MR3 for DDR4
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 *     @return          MR3 value
 *
 */

UINT32
MemNCalcD4MR3 (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  UINT32 MrsAddress;
  //
  // A1:A0 MPR Page Selection = 00b
  //
  MrsAddress = 0;
  //
  // A2 MPR Operation = 0 (Normal)
  //
  // A3 Geardown Mode = 0 (1/2 Rate)
  //
  // A4 Per DRAM Addressability = 0 (Disabled)
  //
  // A5 Temperature Sensor Readout = 0 (Disabed)
  //
  // A8:A6 Fine Granularity Refresh Mode = 000b (Normal - Fixed 1x)
  //  0 Normal (Fixed 1x)  5 Enable on the fly 2x
  //  1 Fixed 2x           6 Enable on the fly 4x
  //  2 Fixed 4x
  //
  // A10:A9 Write CMD Latency when CRC and DM are enabled = 0 (4nCK)
  //     Latency Speed Bin
  //  0   4nCK    1600
  //  1   5nCK    1866, 2133, 2400
  //  2   6nCK    TBD
  //  3   RFU     RFU
  //
  // A12:A11 MPR Read Format = 00b
  //
  // A17, A13 Reserved
  //
  return MrsAddress;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function calculates the value of MR4 for DDR4
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 *     @return          UINT32   - MR4 value
 *
 */

UINT32
MemNCalcD4MR4 (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  UINT32 MrsAddress;
  MEM_PARAMETER_STRUCT *RefPtr;
  RefPtr = NBPtr->RefPtr;
  //
  // A0 RFU = 0
  //
  MrsAddress = 0;
  //
  // A1 Maximum Power Down Mode = 0 (Disabled)
  //
  // A2 Temperature Controlled Refresh Range
  //    0 = Normal 1 = Extended
  //    Set per User Cfg Option
  if (RefPtr->DramTempControlledRefreshEn &&
       RefPtr->EnableExtendedTemperatureRange &&
       RefPtr->DramDoubleRefreshRateEn) {
    MrsAddress |= (1 << 2);
  }
  //
  // A3 Temperature Controlled Refresh Mode  = 1 (Enable)
  //
  if (RefPtr->DramTempControlledRefreshEn) {
    MrsAddress |= (1 << 3);
  }
  //
  // A4 Internal Vref Monitor = 0 (Disabled)
  //
  // A5 RFU = 0
  //
  // A8:A6 CS to CMD/ADDR Latency Mode (cycles) = 000b (Disabled)
  //
  //   000b = Disable  100b = 6
  //   001b = 3        101b = 8
  //   010b = 4        110b = Reserved
  //   011b = 5        111b = Reserved
  //
  // A9 Self Refresh Abort = 1 (Enabled)
  //   Note: Txs must be programmed to tXS_ABORT
  //
  if (NBPtr->SelfRefreshAbort) {
    MrsAddress |= (1 << 9);
  }
  //
  // A10 Read Preamble Training Mode = 0 (Disabled)
  //
  // A11 Read Preamble = 0 (1 tCK)
  //
  // A12 Write Preamble = 0 (1 tCK)
  //
  // A13 PPR = 0 (Disable)
  //
  // A17 RFU = 0
  //
  return MrsAddress;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function calculates the value of MR5 for DDR4
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]       ChipSel - Rank to be trained
 *
 *     @return          MR5 value
 *
 */

UINT32
MemNCalcD4MR5 (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 ChipSel
  )
{
  UINT32 MrsAddress;
  UINT32 RttPark;

  MrsAddress = 0;
  //
  // A2:A0 C/A Parity Latency Mode = 000b
  //
  // A3 CRC Error Clear = 0 (Clear)
  //
  // A4 C/A Parity Error Status = 0 (Clear)
  //
  // A5 ODT Input Buffer during Power Down mode
  //  IF (R/W ODT Pattern != 0)
  //    THEN [0 = ODT input buffer is activated]
  //    ELSE [1 = ODT input buffer is deactivated]
  //  ENDIF.
  //
  if ((NBPtr->ChannelPtr->PhyRODTCSLow |
       NBPtr->ChannelPtr->PhyRODTCSHigh |
       NBPtr->ChannelPtr->PhyWODTCSLow |
       NBPtr->ChannelPtr->PhyWODTCSHigh) == 0) {
    MrsAddress |= (1 << 5);
  }
  //
  // A8:A6 RTT_PARK Per BKDG [DRAM Data Bus Configuration]
  //
  RttPark = NBPtr->PsPtr->RttPark[ChipSel];
  IDS_OPTION_HOOK (IDS_MEM_RTTPARK, &RttPark, &NBPtr->MemPtr->StdHeader);
  ASSERT (RttPark <= 7);
  MrsAddress |= RttPark << 6;
  //
  // A9 CA parity Persistent Error = 0 (Disable)
  //
  // A10 Data Mask
  //   if (x4DIMM != 0 or DisDataMsk == 1) then 0 ELSE 1
  //
  if ((MemNGetBitFieldNb (NBPtr, BFDisDatMsk) == 0) && (MemNGetBitFieldNb (NBPtr, BFX4Dimm) == 0)) {
    MrsAddress |= 1 << 10;
  }
  //
  // A11 Write DBI = 0 (Disable)
  //
  // A12 Read DBI = 0 (Disable)
  //
  // A13 RFU = 0
  // A17 RFU = 0
  //
  return MrsAddress;
}
/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function calculates the value of MR6 for DDR4
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 *     @return          UINT32 MR6 value
 *
 */

UINT32
MemNCalcD4MR6 (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  UINT32 MrsAddress;
  UINT8 tCCD_L;
  MrsAddress = 0;
  //
  // A6 VrefDQ Training Range
  // A5:A0 VrefDQ Training Value (use JEDEC Spec)
  //    1 Dimm Installed:  0x18
  //    2 Dimms Installed: 0x23
  /// @todo: DDR4 - These values need to be abstracted as they will vary per platform.
  if (NBPtr->ChannelPtr->Dimms == 1) {
    MrsAddress |= 0x18;
  } else {
    MrsAddress |= 0x23;
  }
  //
  // A7 VrefDQ Training Enable = 0
  //  0 = Disable(Normal operation Mode)
  //  1 = Enable(Training Mode)
  //
  // A8 RFU = 0
  //
  // A9 RFU = 0
  //
  // A12:A10 tCCD_L
  //   Program per MEMCLK frequency (use JEDEC spec)
  //
  tCCD_L = NBPtr->DCTPtr->Timings.TccdL - 4;
  MrsAddress |= (tCCD_L << 10);
  //
  // A13 RFU = 0
  // A17 RFU = 0
  //
  IDS_OPTION_HOOK (IDS_MEM_MR6_VREF_DQ, &MrsAddress, &(NBPtr->MemPtr->StdHeader));
  return MrsAddress;
}
