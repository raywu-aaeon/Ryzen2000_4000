/* $NoKeywords:$ */
/**
 * @file
 *
 * mnpmucz.c
 *
 * Support functions for memory training using PMU for CZ
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/NB/CZ)
 * @e \$Revision: 316426 $ @e \$Date: 2015-04-08 14:51:16 +0800 (Wed, 08 Apr 2015) $
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
#include "mm.h"
#include "mn.h"
#include "mu.h"
#include "mt.h"
#include "mtsdi3.h"
#include "mnreg.h"
#include "mnpmu.h"
#include "mnPmuFirmwareCZ.h"
#include "Filecode.h"
#include "Library/AmdHeapLib.h"
#include "mnPmuSramMsgBlockCZ.h"
#include "OptionMemory.h"
#include "mncz.h"
CODE_GROUP (G3_DXE)
RDATA_GROUP (G3_DXE)


#define FILECODE LIBRARY_MEM_NBCZLIB_MNPMUCZ_FILECODE



/*----------------------------------------------------------------------------
 *                          DEFINITIONS AND MACROS
 *
 *----------------------------------------------------------------------------
 */
#define PMU_TRAINS_ECC_LANES       0x80    ///< PMU trains ECC lanes
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
 *     This function populates the Base DRAM Configuration common to all DRAM
 *      types for the purpose of passing to PMU SRAM
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNPopulatePmuSramConfigCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  UINT8 AddrMirror;
  UINT8 i;
  PMU_SRAM_MSG_BLOCK_CZ *PmuSramMsgBlockPtr;
  PmuSramMsgBlockPtr = (PMU_SRAM_MSG_BLOCK_CZ *) NBPtr->PsPtr->PmuSramMsgBlockPtr;
  //
  //  Enable MTEST signal for debug
  //
  ///@todo
  //DEBUG_CODE (
  //  PmuSramMsgBlockPtr->MsgMisc = 0x01;
  //)

  PmuSramMsgBlockPtr->TableRevision = 5;
  PmuSramMsgBlockPtr->CpuId = MemNGetBitFieldNb (NBPtr, RegCpuid);
  PmuSramMsgBlockPtr->CsPresent = (UINT8) NBPtr->DCTPtr->Timings.CsPresent;
  //
  // PerRankTiming
  //
  if (MemNGetBitFieldNb (NBPtr, BFPerRankTimingEn) == 1) {
    PmuSramMsgBlockPtr->DctCfg |= SMB_PER_RANK_TMG;
  }
  //
  // Address Mirror
  //
  AddrMirror = 0;
  for (i = 0; i < 8; i++) {
    if (((i & 1) != 0) && ((NBPtr->DCTPtr->Timings.DimmMirrorPresent & (1 << (i >> 1))) != 0)) {
      AddrMirror |= 1 << i;
    }
  }

  PmuSramMsgBlockPtr->AddrMirror = AddrMirror;

  PmuSramMsgBlockPtr->HdtCtrl = PMU_HDT_CTL_LEVEL;
  //
  // Dram Type / Module Type
  //
  PmuSramMsgBlockPtr->DramType = NBPtr->PsPtr->SpdDramType;
  PmuSramMsgBlockPtr->ModuleType = NBPtr->PsPtr->SpdModuleType;
  //
  // Bit 7 of ModuleType of byte offset 9 in the SMB is the ECC train bit.
  //
  if (NBPtr->RefPtr->EnableEccFeature && NBPtr->MCTPtr->Status[SbEccDimms]) {
    PmuSramMsgBlockPtr->ModuleType |= PMU_TRAINS_ECC_LANES;
  }
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function passes to PMU DRAM timings over PMU SRAM for DRAM init and training.
 *     Timings are MemPstate dependent.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNPopulatePmuSramTimingsCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  PMU_SRAM_MSG_BLOCK_CZ *PmuSramMsgBlockPtr;
  PmuSramMsgBlockPtr = (PMU_SRAM_MSG_BLOCK_CZ *) NBPtr->PsPtr->PmuSramMsgBlockPtr;
  //
  // 2T Timing Mode
  //
  PmuSramMsgBlockPtr->DctCfg |= (NBPtr->ChannelPtr->SlowMode) ? SMB_2T_TMG : 0;

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function load appropriate PMU firmware image.
 *
 *
 *     @param[in,out]   *NBPtr     - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNLoadPmuFirmwareCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  MemNLoadPmuFirmwareImageCZ (NBPtr);
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *      Disable PMU on all DCTs
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNDisablePmuCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  // Program D18F2x9C_x0002_0099_dct[3:0][PmuReset,PmuStall] = 1,1.
  MemNSetBitFieldNb (NBPtr, BFPmuStall, 1);
  MemNSetBitFieldNb (NBPtr, BFPmuReset, 1);

  // Program D18F2x9C_x0002_0099_dct[1:0][SRAM_SD] = 1
  MemNSetBitFieldNb (NBPtr, BFPmuSramSd, 1);

  // Program D18F2x9C_x0002_0080[3:0][PmuClkDiv]]=7 (PMU CLK turned off).
  MemNSetBitFieldNb (NBPtr, PER_MEM_PS (0, BFPMUClkDiv), 7);
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *    Checks whether PMU Firmware Image Should be run
 *
 *
 *     @param[in,out]   *NBPtr     - Pointer to the MEM_NB_BLOCK
 *
 *     Returns: TRUE - Image Should be run
 *              FLASE - Image Should not be run
 *
 */

BOOLEAN
MemNCheckPmuFirmwareImageCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  BOOLEAN result;
  //
  // Validate Image in table
  //
  result = TRUE;

  if (((PMU_FIRMWARE*) NBPtr->PmuFirmwareImageTable)[NBPtr->PmuFirmwareImage].SramSize == PMU_IMAGE_NOT_USEABLE) {
    //
    // Unusable image
    //
    result = FALSE;
  }
  if (NBPtr->PmuFirmwareImage == 1) {
    //
    // 2D Training Image (Skip if 1D Mode)
    //
    if (NBPtr->RefPtr->PmuTrainMode == PMU_TRAIN_1D) {
      result = FALSE;
    }
  }
  return result;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *    Load PMU Image to PMU SRAM.
 *
 *
 *     @param[in,out]   *NBPtr     - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNLoadPmuFirmwareImageCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  UINT8 PmuFirmwareImage;
  PMU_FIRMWARE *PmuFirmwareImagePtr;
  UINT16 i;
  UINT8 Dct;

  // Sanity check the size of the PMU SRAM
  ASSERT (PMU_SRAM_DMEM_SIZE_CZ <= PMU_SRAM_DMEM_SIZE_MAX);
  ASSERT (PMU_SRAM_IMEM_SIZE_CZ <= PMU_SRAM_IMEM_SIZE_MAX);
  // Check the FW Image Table Pointer
  ASSERT (NBPtr->PmuFirmwareImage < PMU_IMAGE_MAX_CZ);

  PmuFirmwareImage = NBPtr->PmuFirmwareImage;
  PmuFirmwareImagePtr = &((PMU_FIRMWARE*) NBPtr->PmuFirmwareImageTable)[PmuFirmwareImage];

  for (Dct = 0; Dct < NBPtr->DctCount; Dct++) {
    MemNSwitchDCTNb  (NBPtr, Dct);
    if (PmuFirmwareImage > 0) {
      // Program D18F2x9C_x0002_0099_dct[3:0][PmuReset,PmuStall] = 1,1.
      // Program D18F2x9C_x0002_000E_dct[3:0][PhyDisable]=0. Tester_mode=0.
      MemNPmuResetNb (NBPtr);
    }
    MemNSetBitFieldNb (NBPtr, BFPmuReset, 0);
  }
  // Switch back to Dct 0
  MemNSwitchDCTNb  (NBPtr, 0);

  // Set DctCfgBcEn to broadcast to all enabled DCTs
  MemNSetBitFieldNb (NBPtr, BFDctCfgBcEn, 1);

  // Write the word to D18F2x9C_x0005_[BFF:0000]_dct[3:0] and using the autoincrement feature.
  IDS_HDT_CONSOLE (MEM_FLOW, "\tLoading PMU Data Image %d to DMEM\n", PmuFirmwareImage);
  MemNSetBitFieldNb (NBPtr, RegDctAddlOffset, PMU_FIRMWARE_SRAM_START | DCT_ACCESS_WRITE | DCT_OFFSET_AUTO_INC_EN | PMU_SRAM_DMEM_OFFSET);

  for (i = 0; i < PMU_SRAM_DMEM_SIZE_CZ / sizeof (PmuFirmwareImagePtr->SramDataImage[0]); i++) {
    MemNSetBitFieldNb (NBPtr, RegDctAddlData, PmuFirmwareImagePtr->SramDataImage[i]);
  }
  MemNSetBitFieldNb (NBPtr, RegDctAddlOffset, 0);

  // Write the word to D18F2x9C_x0005_[5BFF:4000]_dct[3:0] and using the autoincrement feature.
  IDS_HDT_CONSOLE (MEM_FLOW, "\tLoading PMU Code Image %d to IMEM\n", PmuFirmwareImage);
  MemNSetBitFieldNb (NBPtr, RegDctAddlOffset, PMU_FIRMWARE_SRAM_START | DCT_ACCESS_WRITE | DCT_OFFSET_AUTO_INC_EN | PMU_SRAM_IMEM_OFFSET);
  for (i = 0; i < PMU_SRAM_IMEM_SIZE_CZ / sizeof (PmuFirmwareImagePtr->SramCodeImage[0]); i++) {
    MemNSetBitFieldNb (NBPtr, RegDctAddlData, PmuFirmwareImagePtr->SramCodeImage[i]);
  }

  MemNSetBitFieldNb (NBPtr, RegDctAddlOffset, 0);
  // Disable DCT broadcast
  MemNSetBitFieldNb (NBPtr, BFDctCfgBcEn, 0);
  IDS_HDT_CONSOLE (MEM_FLOW, "\tPMU firmware revision %x is loaded successfully!\n", ((PMU_SRAM_MSG_BLOCK_CZ*)&PmuFirmwareImagePtr->SramDataImage)->PmuRevision) ;
}


