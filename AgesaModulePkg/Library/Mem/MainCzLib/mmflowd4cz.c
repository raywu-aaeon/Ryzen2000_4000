/* $NoKeywords:$ */
/**
 * @file
 *
 * mmflowd4cz.c
 *
 * Main Memory initialization sequence for DDR4 only for CZ
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/Main/CZ)
 * @e \$Revision: 323467 $ @e \$Date: 2015-07-30 09:05:15 +0800 (Thu, 30 Jul 2015) $
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
#include "Library/AmdMemBaseV5Lib.h"
#include "Library/AmdCalloutLib.h"
#include "Library/FabricPstatesLib.h"
#include "Library/IdsLib.h"
#include "Ids.h"
#include "OptionMemory.h"
#include "mport.h"
#include "mm.h"
#include "mn.h"
#include "mncz.h"
#include "mnD4cz.h"
#include "mt.h"
#include "mt4.h"
#include "mu.h"
#include "mmlvddr4.h"
#include "mnreg.h"
#include "mnpmu.h"
#include "mnPmuSramMsgBlockCZ.h"
#include "Filecode.h"
CODE_GROUP (G3_DXE)
RDATA_GROUP (G3_DXE)

#define FILECODE LIBRARY_MEM_MAINCZLIB_MMFLOWD4CZ_FILECODE
/* features */
#include "mftds.h"

extern MEM_FEAT_BLOCK_MAIN MemFeatMain;
extern OPTION_MEM_FEATURE_MAIN MemMS3Save;

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
AGESA_STATUS
MemMFlowD4CZ (
  IN OUT   MEM_MAIN_DATA_BLOCK *MemMainPtr
  );
/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *      This function defines the memory initialization flow for
 *      systems that only support DDR4 and CZ processor.
 *
 *     @param[in,out]   *MemMainPtr   - Pointer to the MEM_MAIN_DATA_BLOCK
 *
 *     @return          AGESA_STATUS
 *                          - AGESA_FATAL
 *                          - AGESA_CRITICAL
 *                          - AGESA_SUCCESS
 */
AGESA_STATUS
MemMFlowD4CZ (
  IN OUT   MEM_MAIN_DATA_BLOCK *MemMainPtr
  )
{
  MEM_NB_BLOCK  *NBPtr;
  MEM_DATA_STRUCT *MemPtr;
  MEM_OPTION_INSTALL_STRUCT *OptionMemoryInstallPtr;

  NBPtr = MemMainPtr->NBPtr;
  MemPtr = MemMainPtr->MemPtr;
  OptionMemoryInstallPtr = (MEM_OPTION_INSTALL_STRUCT *)NBPtr->MemPtr->OptionMemoryInstallPtr;

  GetLogicalIdOfSocket (MemPtr->DiesPerSystem[BSP_DIE].SocketId, &(MemPtr->DiesPerSystem[BSP_DIE].LogicalCpuid), &(MemPtr->StdHeader));

  //----------------------------------------------------------------
  // Memory Context Restore
  //----------------------------------------------------------------
  if (OptionMemoryInstallPtr->MemFeatMain.MemRestore (MemMainPtr)) {

    // Memory DMI support
    if (!OptionMemoryInstallPtr->MemFeatMain.MemDmi (MemMainPtr)) {
      return AGESA_CRITICAL;
    }

    // Memory CRAT support
    if (!OptionMemoryInstallPtr->MemFeatMain.MemCrat (MemMainPtr)) {
      return AGESA_CRITICAL;
    }

    return AGESA_SUCCESS;
  }

  MemFInitTableDrive (&NBPtr[BSP_DIE], MTBeforeInitializeMCT);

  // Clear DisDllShutdownSR prior any P-State changes.
  MemNConfigureDisDllShutdownSrCZ (NBPtr);

  //----------------------------------------------------------------
  // Force NB-Pstate to NBP0
  //----------------------------------------------------------------
  IDS_HDT_CONSOLE (MEM_FLOW, "Force NBPState to NBP0\n");
  MemNChangeNbFrequencyWrapUnb (NBPtr, 0);

  if (NBPtr->MemPtr->ParameterListPtr->DimmTypeDddr4Capable == TRUE) {
    IDS_HDT_CONSOLE (MEM_FLOW, "\nAnalyze DDR4 DIMM SPD Data\n");
    if (MemTDIMMPresence4 (NBPtr[BSP_DIE].TechPtr) && (NBPtr[BSP_DIE].MCTPtr->DimmPresent != 0)) {
      //
      // Setup D4 Platform Specific Pointers here.
      //
      MemNInitNBDataD4CZ (NBPtr);
      return MemMD4FlowCZ (MemMainPtr);
    } else {
      IDS_HDT_CONSOLE (MEM_FLOW, "\nNo DDR4 DIMMs found.\n");
      return AGESA_FATAL; // DDR4 requested but No DDR4 DIMMs found
    }
  } else {
    return AGESA_FATAL; // UNSUPPORTED DIMMs requested
  }
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *      This function defines the DDR4 initialization flow
 *      when only DDR4 DIMMs are present in the system
 *
 *     @param[in,out]   *MemMainPtr   - Pointer to the MEM_MAIN_DATA_BLOCK
 *
 *     @return          AGESA_STATUS
 *                          - AGESA_FATAL
 *                          - AGESA_CRITICAL
 *                          - AGESA_SUCCESS
 */
AGESA_STATUS
MemMD4FlowCZ (
  IN OUT   MEM_MAIN_DATA_BLOCK *MemMainPtr
  )
{
  UINT8            Dct;
  UINT8            ByteLane;
  MEM_NB_BLOCK     *NBPtr;
  ID_INFO          CallOutIdInfo;
  INT8             MemPstate;
  UINT8            LowestMemPstate;
  UINT8            PmuImage;
  UINT8            CSTestFail;
  BOOLEAN          ErrorRecovery;
  BOOLEAN          IgnoreErr;
  UINT8            i;
  UINT8            TimesMrlRetrain;
  BOOLEAN          PmuResult;
  FABRIC_PSTATE_INFO        NbPstateInfo;
  UINT32           VrefHspeed;
  MEM_OPTION_INSTALL_STRUCT *OptionMemoryInstallPtr;
  MEM_TABLE_ALIAS  MemRxDlyOverrideTab[] = {{MTAfterDqsRwPosTrn, 0, MTDcts, MTDIMMs, 0, VT_ARRAY, BFRdDqs2dDly, {0}},
                                            {MTEnd, 0,  0, 0, 0, 0}
                                            };
  MEM_TABLE_ALIAS  MemTxDlyOverrideTab[] = {{MTAfterDqsRwPosTrn, 0, MTDcts, MTDIMMs, 0, VT_ARRAY, BFWrDat2dDly, {0}},
                                            {MTEnd, 0,  0, 0, 0, 0}
                                            };

  NBPtr = &MemMainPtr->NBPtr[BSP_DIE];
  ErrorRecovery = TRUE;
  IgnoreErr = FALSE;
  CSTestFail = 0;
  PmuResult = FALSE;
  OptionMemoryInstallPtr = (MEM_OPTION_INSTALL_STRUCT *)NBPtr->MemPtr->OptionMemoryInstallPtr;

  IDS_HDT_CONSOLE (MEM_FLOW, "DDR4 Mode\n");

  //----------------------------------------------------------------
  // Clock and power gate unused channels
  //----------------------------------------------------------------
  MemNClockAndPowerGateUnusedDctCZ (NBPtr);

  //----------------------------------------------------------------
  // Set DDR4 mode
  //----------------------------------------------------------------
  MemNSetDdrModeD4CZ (NBPtr);

  //----------------------------------------------------------------
  // Low voltage DDR4
  //----------------------------------------------------------------
  /// @todo: Need a default feature function  to set these values
  NBPtr->RefPtr->DDRVoltage = VOLT1_2;
  MemMainPtr->mmSharedPtr->VoltageMap = VDDIO_DETERMINED;
  /// @todo: Update LVDDR4 Feature to support DDR4 TBD1 and TBD2 Voltages.
  // DDR4 Currently Only supports 1.2V
  // Levelize DDR4 voltage based on socket, as each socket has its own voltage for dimms.
  // AGESA_TESTPOINT (TpProcMemLvDdr4, &(MemMainPtr->MemPtr->StdHeader));
  // if (!MemFeatMain.LvDDR4 (MemMainPtr)) {
  //  return AGESA_FATAL;
  // }

  //----------------------------------------------------------------
  // Find the maximum speed that all DCTs are capable running at
  //----------------------------------------------------------------
  IDS_HDT_CONSOLE (MEM_FLOW, "Determine Target Speed\n");
  if (!MemTSPDGetTargetSpeed4 (NBPtr->TechPtr)) {
    return AGESA_FATAL;
  }

  //------------------------------------------------
  // Finalize target frequency
  //------------------------------------------------
  /// @todo: No LV DDR4 Support Currently
  //if (!MemMLvDdr4PerformanceEnhFinalize (MemMainPtr)) {
  //  return AGESA_FATAL;
  //}

  //----------------------------------------------------------------
  //  Program DCT address map
  //----------------------------------------------------------------
  IDS_HDT_CONSOLE (MEM_FLOW, "\nConfigure DCTs and Set Addr Map\n");
  for (Dct = 0; Dct < NBPtr->DctCount; Dct++) {
    IDS_HDT_CONSOLE (MEM_STATUS, "\tDct %d\n", Dct);
    MemNSwitchDCTNb (NBPtr, Dct);
    if (NBPtr->DCTPtr->Timings.DctDimmValid == 0) {
      MemNDisableDctCZ (NBPtr);
    } else {
      IDS_HDT_CONSOLE (MEM_FLOW, "\t\tMap Chip selects\n");
      if (MemTSPDSetBanks4 (NBPtr->TechPtr)) {
        if (MemNStitchMemoryNb (NBPtr)) {
          if (NBPtr->DCTPtr->Timings.CsEnabled == 0) {
            MemNDisableDctCZ (NBPtr);
          } else {
            IDS_HDT_CONSOLE (MEM_FLOW, "\t\tDQ Mappings\n");
            MemNProgramDqMappingsD4CZ (NBPtr);
            IDS_HDT_CONSOLE (MEM_FLOW, "\t\tAuto Config\n");
            MemNAutoConfigCZ (NBPtr);
            IDS_HDT_CONSOLE (MEM_FLOW, "\t\tSet Training Config\n");
            MemNConfigureDctForTrainingD4CZ (NBPtr);
          }
        }
      }
    }
  }

  IDS_OPTION_HOOK (IDS_BEFORE_DRAM_INIT, NBPtr, &(MemMainPtr->MemPtr->StdHeader));
  //----------------------------------------------------------------
  //  Init Phy mode
  //----------------------------------------------------------------
  IDS_HDT_CONSOLE (MEM_FLOW, "\nInit Phy Mode\n");
  for (Dct = 0; Dct < NBPtr->DctCount; Dct++) {
    MemNSwitchDCTNb  (NBPtr, Dct);
    if (NBPtr->DCTPtr->Timings.DctMemSize != 0) {
      IDS_HDT_CONSOLE (MEM_STATUS, "\tDct %d\n", Dct);

      // 1. Program D18F2x9C_x0002_0099_dct[1:0][PmuReset,PmuStall] = 1,1.
      // 2. Program D18F2x9C_x0002_000E_dct[1:0][PhyDisable]=0. Tester_mode=0.
      MemNPmuResetNb (NBPtr);

      // 3. According to the type of DRAM attached, program the following phy mode
      MemNSetPhyDdrModeCZ (NBPtr, DRAM_TYPE_DDR4_CZ);
    }
  }

  //----------------------------------------------------------------
  //  Program Mem Pstate dependent registers
  //----------------------------------------------------------------
  IDS_HDT_CONSOLE (MEM_FLOW, "\nProgram Mem PState Dependent Registers\n");
  // Only configure M0 Context when in emulation mode.
  LowestMemPstate = 0;
  ///@todo
  //IEM_SKIP_CODE (IEM_EARLY_DCT_CONFIG) {
  // PMU Requires that both Mem PState Contexts are be configured.
  LowestMemPstate = 1;
  //}
  // Intialize customer Vref overrides
  for (Dct = 0; Dct < NBPtr->DctCount; Dct ++) {
    for (MemPstate = LowestMemPstate; MemPstate >= 0; MemPstate--) {
      NBPtr->RefPtr->CpuVrefOverride[Dct][MemPstate].VrefOp = OP_AUTO;
    }
  }

  for (MemPstate = LowestMemPstate; MemPstate >= 0; MemPstate--) {
    // When memory pstate is enabled, this loop will goes through M1 first then M0
    // Otherwise, this loop only goes through M0.
    IDS_HDT_CONSOLE (MEM_FLOW, "\n");
    MemNSwitchMemPstateCZ (NBPtr, MemPstate);

    // By default, start up speed is DDR1333 for M1
    // For M0, we need to set speed to highest possible frequency
    if (MemPstate == 0) {
      for (Dct = 0; Dct < NBPtr->DctCount; Dct++) {
        MemNSwitchDCTNb (NBPtr, Dct);
        NBPtr->DCTPtr->Timings.Speed = NBPtr->DCTPtr->Timings.TargetSpeed;
        if (NBPtr->DCTPtr->Timings.DctMemSize != 0) {
          NBPtr->RefPtr->TargetSpeed = NBPtr->DCTPtr->Timings.TargetSpeed;
        }
      }
    }
    IDS_HDT_CONSOLE (MEM_FLOW, "\tMemClkFreq = %d MHz\n", NBPtr->DCTPtr->Timings.Speed);

    // Program SPD timings and frequency dependent settings
    for (Dct = 0; Dct < NBPtr->DctCount; Dct++) {
      MemNSwitchDCTNb (NBPtr, Dct);

      if (NBPtr->DCTPtr->Timings.DctMemSize != 0) {
        IDS_HDT_CONSOLE (MEM_STATUS, "\tDct %d\n", Dct);

        IDS_HDT_CONSOLE (MEM_FLOW, "\t\tProgram SPD Timings\n");
        if (MemTAutoCycTiming4 (NBPtr->TechPtr)) {
          IDS_HDT_CONSOLE (MEM_FLOW, "\t\tSet MemClk Frequency for MPState %d\n", MemPstate);
          MemNProgramMemPstateRegD4CZ (NBPtr, MemPstate);
          IDS_HDT_CONSOLE (MEM_FLOW, "\t\tProgram Platform Specific Values\n");
          if (MemNPlatformSpecCZ (NBPtr)) {
            MemNSetBitFieldNb (NBPtr, BFMemClkDis, 0);
            // 7. Program default CAD bus values.
            // 8. Program default data bus values.
            IDS_HDT_CONSOLE (MEM_FLOW, "\t\tCAD Data Bus Config\n");
            MemNProgramCadDataBusD4CZ (NBPtr);

            IDS_HDT_CONSOLE (MEM_FLOW, "\t\tPredriver Init\n");
            MemNPredriverInitD4CZ (NBPtr);

            IDS_HDT_CONSOLE (MEM_FLOW, "\t\tMode Register Initialization\n");
            MemNModeRegisterInitializationD4CZ (NBPtr);

            // Enable Phy Power Savings for DDR4
            IDS_HDT_CONSOLE (MEM_FLOW, "\t\tDRAM PHY Power Savings\n");
            MemNDramPhyPowerSavingsCZ (NBPtr, DRAM_TYPE_DDR4_CZ);

            // Table Driven Overrides
            MemFInitTableDrive (NBPtr, MTAfterPlatformSpec);
          }
        }
      }
    }

    MemFInitTableDrive (NBPtr, MTBeforeDInit);
  }


  //----------------------------------------------------------------
  //  Program Phy
  //----------------------------------------------------------------
  IDS_HDT_CONSOLE( MEM_FLOW, "\nProgram DDR Phy\n");
  for (Dct = 0; Dct < NBPtr->DctCount; Dct++) {
    MemNSwitchDCTNb  (NBPtr, Dct);

    if (NBPtr->DCTPtr->Timings.DctMemSize != 0) {
      IDS_HDT_CONSOLE (MEM_STATUS, "\tDct %d\n", Dct);

      // 4. Program general phy static configuration
      MemNPhyGenCfgCZ (NBPtr);

      // 5. Phy Voltage Level Programming
      MemNPhyVoltageLevelCZ (NBPtr, DRAM_TYPE_DDR4_CZ);

      // 7. Program DRAM channel frequency
      MemNProgramChannelFreqCZ (NBPtr, DRAM_TYPE_DDR4_CZ);

      // Step 8 and 9 are done in MemPs dependent section

      // 10. Program FIFO pointer init values
      MemNPhyFifoConfigD4CZ (NBPtr);
    }
  }

  MemFInitTableDrive (NBPtr, MTBeforeTrn);

  IEM_INSERT_CODE (IEM_EARLY_DEVICE_INIT, IemEarlyDeviceInitD4CZ, (NBPtr));

  //------------------------------------------------
  // Callout before Dram Init
  //------------------------------------------------
  AGESA_TESTPOINT (TpProcMemBeforeAgesaHookBeforeDramInit, &(MemMainPtr->MemPtr->StdHeader));
  CallOutIdInfo.IdField.SocketId = NBPtr->MCTPtr->SocketId;
  CallOutIdInfo.IdField.ModuleId = NBPtr->MCTPtr->DieId;
  //------------------------------------------------------------------------
  // Callout to Platform BIOS to set the VDDP/VDDR voltage
  //------------------------------------------------------------------------
  MemMainPtr->MemPtr->ParameterListPtr->VddpVddrVoltage.IsValid = TRUE;
  MemMainPtr->MemPtr->ParameterListPtr->VddpVddrVoltage.Voltage = VOLT1_05;
  if ((NBPtr->MCTPtr->LogicalCpuid.Revision & AMD_REV_F15_BR_ALL) != 0) {
    FabricPstatesGetPstateInfo (NBPtr->MCTPtr->SocketId, NBPtr->MCTPtr->DieId, 0, &NbPstateInfo);
    if (NbPstateInfo.Frequency <= 1100) {
      MemMainPtr->MemPtr->ParameterListPtr->VddpVddrVoltage.Voltage = VOLT0_95;
    }
  }
  IDS_HDT_CONSOLE (MEM_FLOW, "\nVDDP = %s\n", (MemMainPtr->MemPtr->ParameterListPtr->VddpVddrVoltage.Voltage == VOLT1_05) ? "1.05V":
                                              ((MemMainPtr->MemPtr->ParameterListPtr->VddpVddrVoltage.Voltage == VOLT0_95) ? "0.95V" : "Unsupported"));

  IDS_HDT_CONSOLE (MEM_FLOW, "\nCalling out to Platform BIOS on Socket %d, Module %d...\n", CallOutIdInfo.IdField.SocketId, CallOutIdInfo.IdField.ModuleId);
  AgesaHookBeforeDramInit ((UINTN) CallOutIdInfo.IdInformation, MemMainPtr->MemPtr);
  IDS_HDT_CONSOLE (MEM_FLOW, "\nVDDIO = %s\n", GET_VDDIO_STRING(NBPtr->RefPtr->DDRVoltage, DDR4_TECHNOLOGY));
  AGESA_TESTPOINT (TpProcMemAfterAgesaHookBeforeDramInit, &(NBPtr->MemPtr->StdHeader));

  //----------------------------------------------------------------
  // Enable PHY Calibration
  //----------------------------------------------------------------
  IDS_HDT_CONSOLE (MEM_FLOW, "\nEnable Phy Calibration\n");
  for (Dct = 0; Dct < NBPtr->DctCount; Dct++) {
    MemNSwitchDCTNb (NBPtr, Dct);
    if (NBPtr->DCTPtr->Timings.DctDimmValid != 0) {
      MemNEnablePhyCalibrationCZ (NBPtr);
    }
  }

  //----------------------------------------------------------------------------
  // Deassert MemResetL
  //----------------------------------------------------------------------------
  IDS_HDT_CONSOLE (MEM_FLOW, "\nDeassert MemResetL\n");
  for (Dct = 0; Dct < NBPtr->DctCount; Dct++) {
    MemNSwitchDCTNb (NBPtr, Dct);
    if (NBPtr->DCTPtr->Timings.DctMemSize != 0) {
      // Deassert Procedure:
      //   MemResetL = 0
      //   Go to LP2
      //   Go to PS0
      MemNSetBitFieldNb (NBPtr, BFMemResetL, 0);
      MemNSetBitFieldNb (NBPtr, RegPwrStateCmd, 4);
      MemNSetBitFieldNb (NBPtr, RegPwrStateCmd, 0);
    }
  }

  IEM_SKIP_CODE (IEM_EARLY_DEVICE_INIT) {
    MemUWait10ns (20000, NBPtr->MemPtr);
  }
  IDS_OPTION_HOOK (IDS_BEFORE_DQS_TRAINING, MemMainPtr, &(MemMainPtr->MemPtr->StdHeader));

  //----------------------------------------------------------------------------
  //  Program PMU SRAM Message Block, Initiate PMU based Dram init and training
  //----------------------------------------------------------------------------
  IDS_HDT_CONSOLE (MEM_FLOW, "\nBegin PMU Based DRAM Init and Training\n");
  //
  // Allocate Message Block on the heap
  //
  IDS_HDT_CONSOLE (MEM_FLOW, "\tAllocate the PMU SRAM Message Block buffer\n");
  if (MemNInitPmuSramMsgBlockCZ (NBPtr) == FALSE) {
    IDS_HDT_CONSOLE (MEM_FLOW, "\tNot able to allocate the PMU SRAM Message Block buffer\n");
    // Not able to initialize the PMU SRAM Message Block buffer.  Log an event.
    PutEventLog (AGESA_FATAL, MEM_ERROR_HEAP_ALLOCATE_FOR_PMU_SRAM_MSG_BLOCK, 0, 0, 0, 0, &(MemMainPtr->MemPtr->StdHeader));
    return AGESA_FATAL;
  }

  NBPtr->MCTPtr->ChannelTrainFail = 0;

  for (PmuImage = 0; PmuImage < NBPtr->PmuFirmwareImageTableSize; PmuImage++) {
    //
    // Load PMU Firmware Image
    //
    NBPtr->PmuFirmwareImage = PmuImage;
    //
    // Check PMU Firmware Image
    //
    if (MemNCheckPmuFirmwareImageCZ (NBPtr)) {
      MemNLoadPmuFirmwareCZ (NBPtr);
      //NBPtr->FeatPtr->LoadPmuFirmware (NBPtr);
      for (Dct = 0; Dct < NBPtr->DctCount; Dct++) {
        MemNSwitchDCTNb  (NBPtr, Dct);
        if (NBPtr->DCTPtr->Timings.DctMemSize != 0) {
          IDS_HDT_CONSOLE (MEM_STATUS, "\n\tDct %d\n", Dct);
          for (MemPstate = LowestMemPstate; MemPstate >= 0; MemPstate--) {
            // When memory pstate is enabled, this loop will goes through M1 first then M0
            // Otherwise, this loop only goes through M0.
            IDS_HDT_CONSOLE (MEM_FLOW, "\t\t");
            MemNSwitchMemPstateCZ (NBPtr, MemPstate);

            IDS_HDT_CONSOLE (MEM_FLOW, "\t\tStore MPState Dependent Memory Timings in PMU Msg Block\n");
            MemNPopulatePmuSramTimingsD4CZ (NBPtr);
          }

          MemNPopulatePmuSramConfigD4CZ (NBPtr);
          MemNSetPmuSequenceControlD4CZ (NBPtr);
          IEM_INSERT_CODE (IEM_BEFORE_PMU_MSG_BLOCK_WRITE, IemBeforePmuSramMsgBlockWriteCZ, (NBPtr));
          if (MemNWritePmuSramMsgBlockCZ (NBPtr) == FALSE) {
            IDS_HDT_CONSOLE (MEM_FLOW, "\t\tNot able to load the PMU SRAM Message Block in to DMEM\n");
            // Not able to load the PMU SRAM Message Block in to DMEM.  Log an event.
            PutEventLog (AGESA_FATAL, MEM_ERROR_HEAP_LOCATE_FOR_PMU_SRAM_MSG_BLOCK, 0, 0, 0, 0, &(MemMainPtr->MemPtr->StdHeader));
            return AGESA_FATAL;
          }

          // Query for the calibrate completion.
          MemNPendOnPhyCalibrateCompletionCZ (NBPtr);

          MemNStartPmuNb (NBPtr);
        }
      }

      IDS_HDT_CONSOLE (MEM_STATUS, "\n\tWait for PMU Complete on all channels\n");
      for (Dct = 0; Dct < NBPtr->DctCount; Dct++) {
        MemNSwitchDCTNb  (NBPtr, Dct);
        if (NBPtr->DCTPtr->Timings.DctMemSize != 0) {
          //
          // Clear training status bits
          //
          NBPtr->DCTPtr->Timings.CsTrainFail = 0;

          IDS_HDT_CONSOLE (MEM_STATUS, "\t\tDct %d\n", Dct);
          //
          // Wait for PMU Completion
          //
          PmuResult = MemNPendOnPmuCompletionNb (NBPtr);
          //
          // Update PMU Message block from SRAM
          //
          MemNReadPmuSramMsgBlockCZ (NBPtr);
          if (PmuResult == FALSE) {
            //
            // PMU Training Failure
            //
            AGESA_TESTPOINT (TpProcMemPmuFailed, &(MemMainPtr->MemPtr->StdHeader));
            CSTestFail = ((PMU_SRAM_MSG_BLOCK_CZ*)NBPtr->PsPtr->PmuSramMsgBlockPtr)->CsTestFail;
            NBPtr->DCTPtr->Timings.CsTrainFail = CSTestFail;
            NBPtr->MCTPtr->ChannelTrainFail |= (UINT32)1 << Dct;
            IDS_HDT_CONSOLE (MEM_FLOW, "\n\t\tPMU Training Failure. CSTestFail[CS7:CS0] = %x\n", CSTestFail);
            PutEventLog (AGESA_FATAL, MEM_ERROR_PMU_TRAINING, 0, 0, Dct, CSTestFail, &(MemMainPtr->MemPtr->StdHeader));
            MemMainPtr->mmSharedPtr->LastPmuTrainFail = TRUE;
            if (MemMainPtr->mmSharedPtr->TimesPmuRetrain == 0) {
              if (!NBPtr->MemPtr->ErrorHandling (NBPtr->MCTPtr, Dct, CSTestFail, &(MemMainPtr->MemPtr->StdHeader))) {
                ASSERT (FALSE);
              }
            } else {
              IDS_HDT_CONSOLE (MEM_FLOW, "\n\t\tAttempting PMU retraining...\n");
              IDS_HDT_CONSOLE (MEM_FLOW, "\nDe-allocate PMU SRAM Message Block buffer\n");
              if (MemNPostPmuSramMsgBlockCZ (NBPtr) == FALSE) {
                IDS_HDT_CONSOLE (MEM_FLOW, "\tNot able to free the PMU SRAM Message Block buffer\n");
                // Not able to free the PMU SRAM Message Block buffer.  Log an event.
                PutEventLog (AGESA_FATAL, MEM_ERROR_HEAP_DEALLOCATE_FOR_PMU_SRAM_MSG_BLOCK, 0, 0, 0, 0, &(MemMainPtr->MemPtr->StdHeader));
                ASSERT (FALSE);
              }
              return AGESA_FATAL;
            }
          } else {
            // MemNPendOnPmuCompletionNb
            IDS_HDT_CONSOLE (MEM_STATUS, "\t\tPMU Finished\n");
            // Update After 2D training
            if (PmuImage == 1) {
              IDS_HDT_CONSOLE (MEM_FLOW, "\n\t\tUpdate MRS 6 Buffer with trained VrefDQ\n");
              for (MemPstate = LowestMemPstate; MemPstate >= 0; MemPstate--) {
                IDS_HDT_CONSOLE (MEM_FLOW, "\t\t");
                MemNSwitchMemPstateCZ (NBPtr, MemPstate);
                MemNSetBitFieldNb (NBPtr, BFMxMr6, (MemPstate == 0) ?
                                   ((PMU_SRAM_MSG_BLOCK_CZ*)NBPtr->PsPtr->PmuSramMsgBlockPtr)->Annex.D4u.M0_MR6 :
                                   ((PMU_SRAM_MSG_BLOCK_CZ*)NBPtr->PsPtr->PmuSramMsgBlockPtr)->Annex.D4u.M1_MR6);
                IDS_HDT_CONSOLE (MEM_FLOW, "\t\t\tMxMr6(M%d) = %x\n", MemPstate, (MemPstate == 0) ?
                                   ((PMU_SRAM_MSG_BLOCK_CZ*)NBPtr->PsPtr->PmuSramMsgBlockPtr)->Annex.D4u.M0_MR6 :
                                   ((PMU_SRAM_MSG_BLOCK_CZ*)NBPtr->PsPtr->PmuSramMsgBlockPtr)->Annex.D4u.M1_MR6);
              }
            }
            // Update DqVref for M-Pstate change
            if ((((PMU_SRAM_MSG_BLOCK_CZ*)NBPtr->PsPtr->PmuSramMsgBlockPtr)->Annex.D4u.M0_MR6 & 0x7F) !=
                (((PMU_SRAM_MSG_BLOCK_CZ*)NBPtr->PsPtr->PmuSramMsgBlockPtr)->Annex.D4u.M1_MR6 & 0x7F) &&
                (MemNGetBitFieldNb (NBPtr, BFMxMrsEn) & 0x40) != 0) {
              MemNSetBitFieldNb (NBPtr, BFVrefTrainMrsEn, 1);
              MemNSetBitFieldNb (NBPtr, BFVrefTrain3Mrs6, 1);
            }
            // Set calibration rate.
            // 2.10.10.2.8.3 Auto Calibration
            MemNRateOfPhyCalibrateCZ (NBPtr);
          } // Dct Memsize
        }
      } // Wait all channels
    } // Check PMU Firmware Image
  } // Load all PMU images
  IDS_HDT_CONSOLE (MEM_FLOW, "\nPMU Based Training complete\n");

  for (MemPstate = LowestMemPstate; MemPstate >= 0; MemPstate--) {
    MemNSwitchMemPstateCZ (NBPtr, MemPstate);
    MemFInitTableDrive (NBPtr, MTAfterDqsRwPosTrn);
  }

  // Workaround to compensate RxDly/TxDly/VrefHspeed trained by PMU FW
  for (Dct = 0; Dct < NBPtr->DctCount; Dct++) {
    MemNSwitchDCTNb  (NBPtr, Dct);
    if (NBPtr->DCTPtr->Timings.DctDimmValid != 0) {
      MemRxDlyOverrideTab[0].dct = Dct;
      MemTxDlyOverrideTab[0].dct = Dct;
      for (MemPstate = LowestMemPstate; MemPstate >= 0; MemPstate--) {
        MemNSwitchMemPstateCZ (NBPtr, MemPstate);
        VrefHspeed = MemNGetBitFieldNb (NBPtr, BFVrefHspeed);
        if (OP_ADD == NBPtr->PsPtr->VrefOp) {
          VrefHspeed += NBPtr->PsPtr->VrefOffset;
        } else if (OP_SUB == NBPtr->PsPtr->VrefOp) {
          VrefHspeed -= NBPtr->PsPtr->VrefOffset;
        }
        // Customer overrides
        if (OP_ADD == NBPtr->RefPtr->CpuVrefOverride[Dct][MemPstate].VrefOp) {
          VrefHspeed += NBPtr->RefPtr->CpuVrefOverride[Dct][MemPstate].VrefOffset;
        } else if (OP_SUB == NBPtr->RefPtr->CpuVrefOverride[Dct][MemPstate].VrefOp) {
          VrefHspeed -= NBPtr->RefPtr->CpuVrefOverride[Dct][MemPstate].VrefOffset;
        } else if (OP_OVERRIDE == NBPtr->RefPtr->CpuVrefOverride[Dct][MemPstate].VrefOp) {
          VrefHspeed = NBPtr->RefPtr->CpuVrefOverride[Dct][MemPstate].VrefOffset;
        }
        MemNSetBitFieldNb (NBPtr, BFVrefHspeed, VrefHspeed);

        // Compensate RxDly
        if (OP_ADD == NBPtr->PsPtr->RxDlyOp) {
          MemRxDlyOverrideTab[0].attr = MTAdd;
        } else if (OP_SUB == NBPtr->PsPtr->RxDlyOp) {
          MemRxDlyOverrideTab[0].attr = MTSubtract;
        }
        for (ByteLane = 0; ByteLane < 18; ByteLane ++) {
          MemRxDlyOverrideTab[0].data.bytelanevalue[ByteLane] = NBPtr->PsPtr->RxDlyOffset;
        }
        SetTableValuesLoop (NBPtr, &MemRxDlyOverrideTab[0], MTAfterDqsRwPosTrn);

        // Compensate TxDly
        if (OP_ADD == NBPtr->PsPtr->TxDlyOp) {
          MemTxDlyOverrideTab[0].attr = MTAdd;
        } else if (OP_SUB == NBPtr->PsPtr->TxDlyOp) {
          MemTxDlyOverrideTab[0].attr = MTSubtract;
        }
        for (ByteLane = 0; ByteLane < 18; ByteLane ++) {
          MemTxDlyOverrideTab[0].data.bytelanevalue[ByteLane] = NBPtr->PsPtr->TxDlyOffset;
        }
        SetTableValuesLoop (NBPtr, &MemTxDlyOverrideTab[0], MTAfterDqsRwPosTrn);
      }
    }
  }

  //----------------------------------------------------------------
  // Disable chipselects that failed training
  //----------------------------------------------------------------
  IDS_HDT_CONSOLE (MEM_FLOW, "\nDIMM Excludes\n");
  MemNDimmExcludesCZ (NBPtr);

  IEM_INSERT_CODE (IEM_LATE_DCT_CONFIG, IemLateDctConfigD4CZ, (NBPtr));

  //----------------------------------------------------------------
  //  Synchronize Channels
  //----------------------------------------------------------------
  MemNSyncChannelInitCZ (NBPtr);

  //----------------------------------------------------------------
  //  Train MaxRdLatency
  //----------------------------------------------------------------
  IEM_SKIP_CODE (IEM_LATE_MAX_RD_LAT) {
    NBPtr->TechPtr->FindMaxDlyForMaxRdLat = MemTFindMaxRcvrEnDlyTrainedByPmuByte;
    NBPtr->TechPtr->ResetDCTWrPtr = MemNResetRcvFifoCZ;
    IDS_HDT_CONSOLE (MEM_FLOW, "\nTrain MaxRdLatency at each NBPState\n");
    TimesMrlRetrain = DEFAULT_MRL_RETRAIN_TIMES;
    IDS_OPTION_HOOK (IDS_MEM_MRL_RETRAIN_TIMES, &TimesMrlRetrain, &(MemMainPtr->MemPtr->StdHeader));
    for (i = 0; i < TimesMrlRetrain; i ++) {
      if (i > 0) {
        // Force NB P-state 0 for multiple rounds of MRL training
        NBPtr->NbFreqChgState = 0;
        MemNChangeNbFrequencyWrapUnb (NBPtr, 0);
      }
      MemTTrainMaxLatencyCZ (NBPtr->TechPtr);
      // The fourth loop will restore the Northbridge P-State control register
      // to the original value.
      for (NBPtr->NbFreqChgState = 1; NBPtr->NbFreqChgState <= 4; NBPtr->NbFreqChgState++) {
        if (!MemNChangeNbFrequencyWrapUnb (NBPtr, NBPtr->NbFreqChgState) || (NBPtr->NbFreqChgState == 4)) {
          break;
        }
        MemTTrainMaxLatencyCZ (NBPtr->TechPtr);
      }
    }
  }

  //----------------------------------------------------------------
  //  Configure DCT for normal operation
  //----------------------------------------------------------------
  IDS_HDT_CONSOLE (MEM_FLOW, "\nMission Mode Config\n");
  for (Dct = 0; Dct < NBPtr->DctCount; Dct++) {
    MemNSwitchDCTNb (NBPtr, Dct);

    if (NBPtr->DCTPtr->Timings.DctMemSize != 0) {
      IDS_HDT_CONSOLE (MEM_STATUS, "\tDct %d\n", Dct);

      MemNConfigureDctNormalD4CZ (NBPtr);

      //----------------------------------------------------------------
      //  Program turnaround timings
      //----------------------------------------------------------------
      for (MemPstate = LowestMemPstate; MemPstate >= 0; MemPstate--) {
        IDS_HDT_CONSOLE (MEM_FLOW, "\t");
        MemNSwitchMemPstateCZ (NBPtr, MemPstate);
        MemNProgramTurnaroundTimingsD4CZ (NBPtr);

        //----------------------------------------------------------------
        // After Mem Pstate1 Partial Training Table values
        //----------------------------------------------------------------
        MemFInitTableDrive (NBPtr, MTAfterMemPstate1PartialTrn);
      }
    }
  }

  IEM_INSERT_CODE (IEM_LATE_MAX_RD_LAT, IemLateMaxRdLatD4CZ, (NBPtr));
  IDS_HDT_CONSOLE (MEM_FLOW, "\nAdditional DRAM PHY Power Savings\n");
  for (Dct = 0; Dct < NBPtr->DctCount; Dct++) {
    MemNSwitchDCTNb (NBPtr, Dct);
    if (NBPtr->DCTPtr->Timings.DctMemSize != 0) {
      MemNAddlDramPhyPowerSavingsCZ (NBPtr);
    }
  }

  //----------------------------------------------------------------
  //  Initialize Channels interleave address bit.
  //----------------------------------------------------------------
  MemNInitChannelIntlvAddressBitCZ (NBPtr);

  //----------------------------------------------------------------
  // Assign physical address ranges for DCTs and node. Also, enable channel interleaving.
  //----------------------------------------------------------------
  IDS_HDT_CONSOLE (MEM_FLOW, "HT Mem Map\n");
  if (!NBPtr->FeatPtr->InterleaveChannels (NBPtr)) {
    MemNHtMemMapCZ (NBPtr);
  }

  //----------------------------------------------------
  // If there is no dimm on the system, do fatal exit
  //----------------------------------------------------
  if (NBPtr->RefPtr->SysLimit == 0) {
    PutEventLog (AGESA_FATAL, MEM_ERROR_NO_DIMM_FOUND_ON_SYSTEM, 0, 0, 0, 0, &(MemMainPtr->MemPtr->StdHeader));
    return AGESA_FATAL;
  }

  //----------------------------------------------------------------
  // CpuMemTyping
  //----------------------------------------------------------------
  IDS_HDT_CONSOLE (MEM_FLOW, "Mem Typing\n");
  MemNCPUMemTypingNb (NBPtr);

  IDS_OPTION_HOOK (IDS_AFTER_DQS_TRAINING, MemMainPtr, &(MemMainPtr->MemPtr->StdHeader));
  //----------------------------------------------------------------
  // After Training Table values
  //----------------------------------------------------------------
  MemFInitTableDrive (NBPtr, MTAfterTrn);

  //----------------------------------------------------------------
  // Interleave banks
  //----------------------------------------------------------------
  IDS_HDT_CONSOLE (MEM_FLOW, "Bank Interleave\n");
  if (NBPtr->FeatPtr->InterleaveBanks (NBPtr)) {
    if (NBPtr->MCTPtr->ErrCode == AGESA_FATAL) {
      return AGESA_FATAL;
    }
  }

  //----------------------------------------------------------------
  // After Programming Interleave registers
  //----------------------------------------------------------------
  MemFInitTableDrive (NBPtr, MTAfterInterleave);

  //----------------------------------------------------------------
  // Memory Clear
  //----------------------------------------------------------------
  AGESA_TESTPOINT (TpProcMemMemClr, &(MemMainPtr->MemPtr->StdHeader));
  if (!OptionMemoryInstallPtr->MemFeatMain.MemClr (MemMainPtr)) {
    return AGESA_FATAL;
  }

  //----------------------------------------------------------------
  // ECC
  //----------------------------------------------------------------
  if (!OptionMemoryInstallPtr->MemFeatMain.InitEcc (MemMainPtr)) {
    return AGESA_FATAL;
  }

  //----------------------------------------------------------------
  // C6 and ACP Engine Storage Allocation
  //----------------------------------------------------------------
  IDS_HDT_CONSOLE (MEM_FLOW, "Allocate C6 and ACP Engine Storage\n");
  MemNAllocateC6AndAcpEngineStorageCZ (NBPtr);

  //----------------------------------------------------------------
  // UMA Allocation & UMAMemTyping
  //----------------------------------------------------------------
  AGESA_TESTPOINT (TpProcMemUMAMemTyping, &(MemMainPtr->MemPtr->StdHeader));
  IDS_HDT_CONSOLE (MEM_FLOW, "UMA Allocation\n");
  if (!OptionMemoryInstallPtr->MemFeatMain.UmaAllocation (MemMainPtr)) {
    return AGESA_FATAL;
  }

  //----------------------------------------------------------------
  // OnDimm Thermal
  //----------------------------------------------------------------
  IDS_HDT_CONSOLE (MEM_FLOW, "OnDIMM Thermal\n");
  if (NBPtr->FeatPtr->OnDimmThermal (NBPtr)) {
    if (NBPtr->MCTPtr->ErrCode == AGESA_FATAL) {
      return AGESA_FATAL;
    }
  }

  //----------------------------------------------------------------
  // Finalize MCT
  //----------------------------------------------------------------
  MemNFinalizeMctCZ (NBPtr);
  MemFInitTableDrive (NBPtr, MTAfterFinalizeMCT);

  //----------------------------------------------------------------
  // Memory Context Save
  //----------------------------------------------------------------
  OptionMemoryInstallPtr->MemFeatMain.MemSave (MemMainPtr);

  //----------------------------------------------------------------
  // Memory DMI support
  //----------------------------------------------------------------
  if (!OptionMemoryInstallPtr->MemFeatMain.MemDmi (MemMainPtr)) {
    return AGESA_CRITICAL;
  }

  //----------------------------------------------------------------
  // Memory CRAT support
  //----------------------------------------------------------------
  if (!OptionMemoryInstallPtr->MemFeatMain.MemCrat (MemMainPtr)) {
    return AGESA_CRITICAL;
  }

  //----------------------------------------------------------------
  // Save memory S3 data
  //----------------------------------------------------------------
  IDS_HDT_CONSOLE (MEM_FLOW, "S3 Save\n");
  if (!MemMS3Save (MemMainPtr)) {
    return AGESA_CRITICAL;
  }

  //----------------------------------------------------------------
  //  De-allocate the PMU SRAM Message Block buffer.
  //----------------------------------------------------------------
  IDS_HDT_CONSOLE (MEM_FLOW, "\nDe-allocate PMU SRAM Message Block buffer\n");
  if (MemNPostPmuSramMsgBlockCZ (NBPtr) == FALSE) {
    IDS_HDT_CONSOLE (MEM_FLOW, "\tNot able to free the PMU SRAM Message Block buffer\n");
    // Not able to free the PMU SRAM Message Block buffer.  Log an event.
    PutEventLog (AGESA_FATAL, MEM_ERROR_HEAP_DEALLOCATE_FOR_PMU_SRAM_MSG_BLOCK, 0, 0, 0, 0, &(MemMainPtr->MemPtr->StdHeader));
    return AGESA_FATAL;
  }

  //----------------------------------------------------------------
  // Switch back to DCT 0 before sending control back
  //----------------------------------------------------------------
  MemNSwitchDCTNb (NBPtr, 0);

  return AGESA_SUCCESS;
}

/*----------------------------------------------------------------------------
 *                              LOCAL FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */

