/* $NoKeywords:$ */
/**
 * @file
 *
 * mnphyD3cz.c
 *
 * Northbridge Phy support for CZ with DDR3
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/NB/CZ)
 * @e \$Revision: 322890 $ @e \$Date: 2015-07-20 14:11:57 +0800 (Mon, 20 Jul 2015) $
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
#include "cpuRegisters.h"
#include "mport.h"
#include "mm.h"
#include "mn.h"
#include "mt.h"
#include "mu.h"
#include "mnreg.h"
#include "OptionMemory.h"       // need def for MEM_FEAT_BLOCK_NB
#include "mncz.h"
#include "PlatformMemoryConfiguration.h"
#include "merrhdl.h"
#include "Filecode.h"
CODE_GROUP (G3_DXE)
RDATA_GROUP (G3_DXE)


#define FILECODE LIBRARY_MEM_NBCZLIB_MNPHYD3CZ_FILECODE
/* features */
#include "mftds.h"
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
typedef struct {
  UINT8 BankAddr :4;
  UINT8 Addr13 :1;
  UINT8 Addr14 :1;
  UINT8 Addr15 :1;
  UINT8 Reserved :1;
} BANK_ADDR_MAP;

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
 *     This function does Phy Predriver initialization for DDR3
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNPredriverInitD3CZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  CONST STATIC TXPREPN_ENTRY TxPrePNDqDqs[] = {
    {DDR1066_FREQUENCY, 0x31, {0x8F, 0x8F, 0x8F}},
    {DDR1066_FREQUENCY, 0x70, {0x8F, 0x8F, 0x8F}},
    {DDR1066_FREQUENCY, 0x75, {0x8D, 0x8D, 0x8F}},
    {DDR1066_FREQUENCY, 0x7F, {0x12, 0x12, 0x12}},
    {DDR1600_FREQUENCY, 0x31, {0x8F, 0x8F, 0x8F}},
    {DDR1600_FREQUENCY, 0x70, {0x8F, 0x8F, 0x8F}},
    {DDR1600_FREQUENCY, 0x75, {0x8D, 0x8D, 0x8F}},
    {DDR1600_FREQUENCY, 0x7F, {0x12, 0x12, 0x12}},
    {DDR2400_FREQUENCY, 0x31, {0x8F, 0x8F, 0x8F}},
    {DDR2400_FREQUENCY, 0x70, {0x8F, 0x8F, 0x8F}},
    {DDR2400_FREQUENCY, 0x75, {0x8D, 0x8D, 0x8F}},
    {DDR2400_FREQUENCY, 0x7F, {0x12, 0x12, 0x23}},
  };

  CONST STATIC TXPREPN_ENTRY TxPrePNCmdAddr[] = {
    {DDR1066_FREQUENCY, 0x07, {0x12, 0x23, 0x23}},
    {DDR1066_FREQUENCY, 0x0F, {0x12, 0x12, 0x23}},
    {DDR1066_FREQUENCY, 0x1F, {0x11, 0x12, 0x12}},
    {DDR1066_FREQUENCY, 0x3F, {0x11, 0x12, 0x12}},
    {DDR1600_FREQUENCY, 0x07, {0x12, 0x23, 0x23}},
    {DDR1600_FREQUENCY, 0x0F, {0x12, 0x12, 0x23}},
    {DDR1600_FREQUENCY, 0x1F, {0x11, 0x12, 0x23}},
    {DDR1600_FREQUENCY, 0x3F, {0x11, 0x12, 0x23}},
    {DDR2400_FREQUENCY, 0x07, {0x23, 0x23, 0x34}},
    {DDR2400_FREQUENCY, 0x0F, {0x22, 0x23, 0x34}},
    {DDR2400_FREQUENCY, 0x1F, {0x22, 0x22, 0x34}},
    {DDR2400_FREQUENCY, 0x3F, {0x22, 0x22, 0x34}},
  };

  CONST STATIC TXPREPN_ENTRY TxPrePNClk[] = {
    {DDR1066_FREQUENCY, 0x07, {0x22, 0x33, 0x33}},
    {DDR1066_FREQUENCY, 0x0F, {0x22, 0x22, 0x33}},
    {DDR1066_FREQUENCY, 0x1F, {0x22, 0x22, 0x22}},
    {DDR1066_FREQUENCY, 0x3F, {0x22, 0x22, 0x22}},
    {DDR1600_FREQUENCY, 0x07, {0x33, 0x33, 0x44}},
    {DDR1600_FREQUENCY, 0x0F, {0x33, 0x33, 0x44}},
    {DDR1600_FREQUENCY, 0x1F, {0x33, 0x33, 0x44}},
    {DDR1600_FREQUENCY, 0x3F, {0x33, 0x33, 0x44}},
    {DDR2400_FREQUENCY, 0x07, {0x44, 0x56, 0x67}},
    {DDR2400_FREQUENCY, 0x0F, {0x45, 0x56, 0x67}},
    {DDR2400_FREQUENCY, 0x1F, {0x55, 0x56, 0x67}},
    {DDR2400_FREQUENCY, 0x3F, {0x55, 0x56, 0x66}},
  };

  CONST STATIC PROG_TXPREPN_STRUCT ProgTxPrePN[] = {
    {PER_CAD_PAD (PAD_CKE, ALL_PADS, RegCadTxSlewRate),      (TXPREPN_ENTRY *)&TxPrePNCmdAddr, OFFSET_OF (MEM_PS_BLOCK, CkeStrength)},
    {PER_CAD_PAD (PAD_CS, ALL_PADS, RegCadTxSlewRate),       (TXPREPN_ENTRY *)&TxPrePNCmdAddr, OFFSET_OF (MEM_PS_BLOCK, CsOdtStrength)},
    {PER_CAD_PAD (PAD_ODT, ALL_PADS, RegCadTxSlewRate),      (TXPREPN_ENTRY *)&TxPrePNCmdAddr, OFFSET_OF (MEM_PS_BLOCK, CsOdtStrength)},
    {PER_CAD_PAD (PAD_ADDR_CMD, ALL_PADS, RegCadTxSlewRate), (TXPREPN_ENTRY *)&TxPrePNCmdAddr, OFFSET_OF (MEM_PS_BLOCK, AddrCmdStrength)},
    {PER_CAD_PAD (PAD_CLK, ALL_PADS, RegCadTxSlewRate),      (TXPREPN_ENTRY *)&TxPrePNClk,     OFFSET_OF (MEM_PS_BLOCK, ClkStrength)},
    {PER_DATA_BYTE (PAD_DQ, ALL_BYTES, RegDataTxSlewRate),   (TXPREPN_ENTRY *)&TxPrePNDqDqs,   OFFSET_OF (MEM_PS_BLOCK, DqStrength)},
    {PER_DATA_BYTE (PAD_DQS, ALL_BYTES, RegDataTxSlewRate),  (TXPREPN_ENTRY *)&TxPrePNDqDqs,   OFFSET_OF (MEM_PS_BLOCK, DqsStrength)},
  };

  TXPREPN_ENTRY *TabPtr;
  UINT8 TxSlewRate;
  UINT8 *DrvStrenPtr;
  UINT8 i;
  UINT8 j;

  // Expect all TxPre tables have the same number of entries
  ASSERT ((GET_SIZE_OF (TxPrePNDqDqs) == GET_SIZE_OF (TxPrePNCmdAddr)) && (GET_SIZE_OF (TxPrePNCmdAddr) == GET_SIZE_OF (TxPrePNClk)));

  if (NBPtr->MemPstate == 0) {
    // Program D18F2x9C_x0002_0087_dct[3:0][DisAutoComp, DisPredriverCal] = {1,1}.
    MemNSetBitFieldNb (NBPtr, BFDisAutoComp, 1);
    MemNSetBitFieldNb (NBPtr, BFDisPredriverCal, 1);

    TxSlewRate = 0;
    for (i = 0; i < GET_SIZE_OF (ProgTxPrePN); i++) {
      DrvStrenPtr = ((UINT8 *) NBPtr->PsPtr) + ProgTxPrePN[i].PsOffset;
      TabPtr = ProgTxPrePN[i].TabPtr;
      for (j = 0; j < GET_SIZE_OF (TxPrePNDqDqs); j++) {
        if (NBPtr->DCTPtr->Timings.Speed <= TabPtr[j].MaxSpeed) {
          if (*DrvStrenPtr <= TabPtr[j].DrvStrenP) {
            TxSlewRate = TabPtr[j].TxPrePNVal[CONVERT_VDDIO_TO_ENCODED (NBPtr->RefPtr->DDRVoltage, DDR3_TECHNOLOGY)];
            ASSERT (TxSlewRate != 0xFF);
            break;
          }
        }
      }
      ASSERT (j < GET_SIZE_OF (TxPrePNDqDqs));

      MemNSetBitFieldNb (NBPtr, ProgTxPrePN[i].BfName, ((TxSlewRate >> 4) & 0xF) | ((TxSlewRate << 4) & 0xF0));
    }

    // Program D18F2x9C_x0002_0087_dct[3:0][DisAutoComp] = 0.
    // DisAutoComp will be cleared after setting up FIFO pointers
  }
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function programs the phy registers to configure CAD bus and data bus for DDR3
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNProgramCadDataBusD3CZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  UINT16 RxRdPtrOffset;
  UINT16 TxRdPtrOffset;
  UINT16 BankAddrReg;
  UINT16 BankAddrRegPerDimm;
  UINT8 Dimm;
  UINT8 i;
  UINT8 OrAddr13;
  UINT8 OrAddr14;
  UINT8 OrAddr15;
  BANK_ADDR_MAP BankAddrMap[10] = { {0x1, 0, 0, 0},
                                    {0x2, 0, 0, 0},
                                    {0x5, 1, 0, 0},
                                    {0x6, 0, 0, 0},
                                    {0x7, 1, 1, 0},
                                    {0x8, 1, 0, 0},
                                    {0x9, 1, 1, 0},
                                    {0xA, 1, 1, 1},
                                    {0xB, 1, 1, 1},
                                    {0xC, 1, 1, 1},
                                  };

  //------------------------------------------------
  // CAD bus configuration
  //------------------------------------------------
  MemNSetBitFieldNb (NBPtr, RegCadTxImpedance, 0);
  IDS_HDT_CONSOLE (MEM_FLOW, "\t\t\tCKE\n");
  MemNSetBitFieldNb (NBPtr, PER_CAD_PAD (PAD_CKE, ALL_PADS, RegCadTxImpedance), (NBPtr->PsPtr->CkeStrength << 6) | NBPtr->PsPtr->CkeStrength);
  IDS_HDT_CONSOLE (MEM_FLOW, "\t\t\tCS\n");
  MemNSetBitFieldNb (NBPtr, PER_CAD_PAD (PAD_CS, ALL_PADS, RegCadTxImpedance), (NBPtr->PsPtr->CsOdtStrength << 6) | NBPtr->PsPtr->CsOdtStrength);
  IDS_HDT_CONSOLE (MEM_FLOW, "\t\t\tODT\n");
  MemNSetBitFieldNb (NBPtr, PER_CAD_PAD (PAD_ODT, ALL_PADS, RegCadTxImpedance), (NBPtr->PsPtr->CsOdtStrength << 6) | NBPtr->PsPtr->CsOdtStrength);
  IDS_HDT_CONSOLE (MEM_FLOW, "\t\t\tAddrCmd\n");
  MemNSetBitFieldNb (NBPtr, PER_CAD_PAD (PAD_ADDR_CMD, ALL_PADS, RegCadTxImpedance), (NBPtr->PsPtr->AddrCmdStrength << 6) | NBPtr->PsPtr->AddrCmdStrength);
  IDS_HDT_CONSOLE (MEM_FLOW, "\t\t\tCLK\n");
  MemNSetBitFieldNb (NBPtr, PER_CAD_PAD (PAD_CLK, ALL_PADS, RegCadTxImpedance), (NBPtr->PsPtr->ClkStrength << 6) | NBPtr->PsPtr->ClkStrength);

  OrAddr13 = 0;
  OrAddr14 = 0;
  OrAddr15 = 0;
  BankAddrReg = (UINT16)NBPtr->GetBitField (NBPtr, BFDramBankAddrReg);
  for (Dimm = 0; Dimm <= 3; Dimm ++) {
    BankAddrRegPerDimm = (BankAddrReg >> (4 * Dimm)) & 0xF;
    if (BankAddrRegPerDimm != 0) {
      for (i = 0; i < GET_SIZE_OF (BankAddrMap); i ++) {
        if (BankAddrRegPerDimm == BankAddrMap[i].BankAddr) {
          OrAddr13 |= BankAddrMap[i].Addr13;
          OrAddr14 |= BankAddrMap[i].Addr14;
          OrAddr15 |= BankAddrMap[i].Addr15;
          break;
        }
      }
      ASSERT (i != GET_SIZE_OF (BankAddrMap));
    }
  }

  if (OrAddr13 == 0) {
    MemNSetBitFieldNb (NBPtr, PER_CAD_PAD (PAD_ADDR_CMD_A13, ALL_PADS, RegCadTxImpedance), 0);
  }
  if (OrAddr14 == 0) {
    MemNSetBitFieldNb (NBPtr, PER_CAD_PAD (PAD_ADDR_CMD_A14, ALL_PADS, RegCadTxImpedance), 0);
  }
  if (OrAddr15 == 0) {
    MemNSetBitFieldNb (NBPtr, PER_CAD_PAD (PAD_ADDR_CMD_A15, ALL_PADS, RegCadTxImpedance), 0);
  }

  //------------------------------------------------
  // Data bus configuration
  //------------------------------------------------
  // Program D18F2x9C_x0002_0087_dct[1:0][DisAutoComp, DisPredriverCal] = {1,1}.
  MemNSetBitFieldNb (NBPtr, BFDisAutoComp, 1);
  MemNSetBitFieldNb (NBPtr, BFDisPredriverCal, 1);

  // Only the value for a single control unit register is described. The values in the table should be broadcast to all
  // instances of registers of the same control unit type, unless otherwise noted.
  IDS_HDT_CONSOLE (MEM_FLOW, "\t\t\tDQ\n");
  MemNSetBitFieldNb (NBPtr, PER_DATA_BYTE (PAD_DQ, ALL_BYTES, RegDataTxImpedance), (NBPtr->PsPtr->DqStrength << 7) | NBPtr->PsPtr->DqStrength);
  IDS_HDT_CONSOLE (MEM_FLOW, "\t\t\tDQS\n");
  MemNSetBitFieldNb (NBPtr, PER_DATA_BYTE (PAD_DQS, ALL_BYTES, RegDataTxImpedance), (NBPtr->PsPtr->DqsStrength << 7) | NBPtr->PsPtr->DqsStrength);
  if (NBPtr->DCTPtr->Timings.Dimmx4Present == 0) {
    IDS_HDT_CONSOLE (MEM_FLOW, "\t\t\tDQS_L\n");
    MemNSetBitFieldNb (NBPtr, PER_DATA_BYTE (PAD_DQS_L, ALL_BYTES, RegDataTxImpedance), 0);
  }

  IDS_HDT_CONSOLE (MEM_FLOW, "\t\t\tProc ODT\n");
  MemNSetBitFieldNb (NBPtr, PER_DATA_BYTE (PAD_DQ, ALL_BYTES, RegDataRxImpedance), (NBPtr->PsPtr->OdtStrength << 4) | NBPtr->PsPtr->OdtStrength);
  MemNSetBitFieldNb (NBPtr, PER_DATA_BYTE (PAD_DQS, ALL_BYTES, RegDataRxImpedance), (NBPtr->PsPtr->OdtStrength << 4) | NBPtr->PsPtr->OdtStrength);

  // Program D18F2x9C_x0002_0087_dct[1:0][DisAutoComp] = 0.
  MemNSetBitFieldNb (NBPtr, BFDisAutoComp, 0);

  //------------------------------------------------
  // FIFO pointer init
  //------------------------------------------------
  // 3. D18F2x9C_x0[3,1:0][F,7:0]1_0028_dct[1:0][RxRdPtrOffset] as follows:
  //    Broadcast the value to all chips.
  //    RxRdPtrOffset = MIN(18, CASL).
  RxRdPtrOffset = MIN (18, NBPtr->DCTPtr->Timings.CasL);
  // 4. D18F2x9C_x0[3,1:0][F,7:0]1_0028_dct[1:0][TxRdPtrOffset] as follows:
  //    Broadcast the value to all chips.
  //    TxRdPtrOffset = MAX(5, CWL).
  TxRdPtrOffset = MAX (5, (NBPtr->DCTPtr->Timings.Speed / 133) + 2);
  MemNSetBitFieldNb (NBPtr, RegDataRdPtrOffset, (TxRdPtrOffset << 6) | RxRdPtrOffset);
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function initializes FIFO configurations for DDR3
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */
VOID
MemNPhyFifoConfigD3CZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  UINT16 Speed;
  UINT8  RdPtrInit;
  UINT8  DataRdPtrInit;
  UINT8  NbPs;
  UINT32 NbClkFreqMhz;
  UINT8  MinRdPtrInit;
  UINT8  CpuRevisionCz;

  RdPtrInit = 0;
  MinRdPtrInit = 0;
  CpuRevisionCz = (UINT8) MemNGetBitFieldNb (NBPtr, BFBaseModel);

  // 1. For each NbPstate, excluding the "NbPstate PMU" instance, program
  //    Broadcast the value to all timing groups and chips.
  //    D18F2x9C_x00[F,3:0]0_[F,3:0][8,3:0]2E_dct[1:0][RdPtrInitVal]= Table 38.
  //    D18F2x9C_x00[F,8:0]1_0[8,3:0]2E_dct[1:0][RdPtrInitVal] = Table 38.
  for (NbPs = 0; NbPs < 4; NbPs++) {
    NbClkFreqMhz = MemNGetNbClkFreqByPstateUnb (NBPtr, NbPs);
    if (MemNGetBitFieldNb (NBPtr, BFMemPstate0 + NbPs) == 0) {
      Speed = NBPtr->DCTPtr->Timings.TargetSpeed;
      IDS_HDT_CONSOLE (MEM_FLOW, "\t\tNBP%d - M0\n", NbPs);
    } else {
      Speed = DDR667_FREQUENCY;
      IDS_HDT_CONSOLE (MEM_FLOW, "\t\tNBP%d - M1\n", NbPs);
    }

    switch (Speed) {
    case DDR667_FREQUENCY:
    case DDR800_FREQUENCY:
    case DDR1066_FREQUENCY:
      RdPtrInit = 0x14;
      break;
    case DDR1333_FREQUENCY:
      RdPtrInit = (NbClkFreqMhz >= 800 && NbClkFreqMhz <= 1000) ? 0x10 : 0x14;
      break;
    case DDR1600_FREQUENCY:
    case DDR1866_FREQUENCY:
      RdPtrInit = 0x14;
      break;
    case DDR2133_FREQUENCY:
    case DDR2400_FREQUENCY:
      RdPtrInit = 0x10;
      break;
    default:
      ASSERT (FALSE);  // MemClk not supported.
    }

    DataRdPtrInit = RdPtrInit;
    MemNSetBitFieldNb (NBPtr, PER_NB_PS (NbPs, RegRdPtrInitVal), RdPtrInit);
    MemNSetBitFieldNb (NBPtr, PER_NB_PS (NbPs, RegDataRdPtrInitVal), DataRdPtrInit);
  }

  // Clear DisAutoComp to complete predriver programming
  MemNSetBitFieldNb (NBPtr, BFDisAutoComp, 0);
}

/*----------------------------------------------------------------------------
 *                              LOCAL FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */



