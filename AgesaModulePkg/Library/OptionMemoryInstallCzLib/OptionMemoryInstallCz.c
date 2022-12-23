/* $NoKeywords:$ */
/**
 * @file
 *
 * Install of build option: Memory
 *
 * Contains AMD AGESA install macros and test conditions. Output is the
 * defaults tables reflecting the User's build options selection.
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Options
 * @e \$Revision: 326571 $   @e \$Date: 2015-09-06 20:19:27 +0800 (Sun, 06 Sep 2015) $
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
 **/

/* Memory Includes */
#include "AGESA.h"
#include "CarrizoFp4Install.h"
#include "OptionMemory.h"

#define FILECODE LIBRARY_OPTIONMEMORYINSTALLCZLIB_OPTIONMEMORYINSTALLCZ_FILECODE

/*-------------------------------------------------------------------------------
 *  This option file is designed to be included into the platform solution install
 *  file. The platform solution install file will define the options status.
 *  Check to validate the definition
 */

/*----------------------------------------------------------------------------------
 * FEATURE BLOCK FUNCTIONS
 *
 *  This section defines function names that depend upon options that are selected
 *  in the platform solution install file.
 */
BOOLEAN MemFDefRet (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  return FALSE;
}

BOOLEAN MemMDefRet (
  IN   MEM_MAIN_DATA_BLOCK *MMPtr
  )
{
  return TRUE;
}

BOOLEAN MemMDefRetFalse (
  IN   MEM_MAIN_DATA_BLOCK *MMPtr
  )
{
  return FALSE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *      This function is the default return for non-training technology features
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 */
/*
BOOLEAN MemTFeatDef (
  IN OUT   MEM_TECH_BLOCK *TechPtr
  )
{
  return TRUE;
}
*/

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function initializes the northbridge block for dimm identification translator
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in,out]   *MemPtr  - Pointer to the MEM_DATA_STRUCT
 *     @param[in,out]   NodeID   - ID of current node to construct
 *     @return          TRUE     - This is the correct constructor for the targeted node.
 *     @return          FALSE    - This isn't the correct constructor for the targeted node.
 */
BOOLEAN MemNIdentifyDimmConstructorRetDef (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN OUT   MEM_DATA_STRUCT *MemPtr,
  IN       UINT8 NodeID
  )
{
  return FALSE;
}

AGESA_STATUS MemNTransSysAddrToCsRetDef (
  IN OUT   AMD_IDENTIFY_DIMM *AmdDimmIdentify,
  IN       MEM_MAIN_DATA_BLOCK *mmPtr
  )
{
  return AGESA_ERROR;
}

/*----------------------------------------------------------------------------------
 * TABLE FEATURE BLOCK FUNCTIONS
 *
 *  This section defines function names that depend upon options that are selected
 *  in the platform solution install file.
 */
UINT8 MemFTableDefRet (
  IN OUT   MEM_TABLE_ALIAS **MTPtr
  )
{
  return 0;
}
/*----------------------------------------------------------------------------------
 * FEATURE S3 BLOCK FUNCTIONS
 *
 *  This section defines function names that depend upon options that are selected
 *  in the platform solution install file.
 */
BOOLEAN MemFS3DefConstructorRet (
  IN OUT   VOID *S3NBPtr,
  IN OUT   MEM_DATA_STRUCT *MemPtr,
  IN       UINT8 NodeID
  )
{
  return TRUE;
}

extern MEM_RESUME_CONSTRUCTOR MemS3ResumeConstructNBBlockCZ;
#define MEM_FEATURE_S3_RESUME_CONSTRUCTOR_CZ MemS3ResumeConstructNBBlockCZ
extern OPTION_MEM_FEATURE_MAIN MemMS3Save;
#define MEM_MAIN_FEATURE_MEM_S3_SAVE MemMS3Save
extern MEM_IDENDIMM_CONSTRUCTOR MemNIdentifyDimmConstructorCZ;
#define MEM_IDENDIMM_CZ MemNIdentifyDimmConstructorCZ
extern MEM_TRANS_SYS_ADDR_TO_CS MemFTransSysAddrToCsCZ;
#define MEM_TRANS_SYS_ADDR_TO_CS_CZ MemFTransSysAddrToCsCZ

/*----------------------------------------------------------------------------------
 * NORTHBRIDGE BLOCK CONSTRUCTOR AND INITIALIZER FUNCTION DEFAULT ASSIGNMENTS
 *
 *----------------------------------------------------------------------------------
*/
extern MEM_FLOW_CFG MemMFlowD34CZ;
#define MEM_MAIN_FLOW_CONTROL_PTR_CZ MemMFlowD34CZ

MEM_FLOW_CFG* memFlowControlInstalled = MEM_MAIN_FLOW_CONTROL_PTR_CZ;
#define MEM_MAIN_FEATURE_ONLINE_SPARE  MemMDefRet
#define MEM_FEATURE_ONLINE_SPARE  MemFDefRet

extern OPTION_MEM_FEATURE_MAIN MemMContextSave;
extern OPTION_MEM_FEATURE_MAIN MemMContextRestore;
#define MEM_MAIN_FEATURE_MEM_SAVE     MemMContextSave
#define MEM_MAIN_FEATURE_MEM_RESTORE  MemMContextRestore

extern OPTION_MEM_FEATURE_NB MemFInterleaveBanks;
#define MEM_FEATURE_BANK_INTERLEAVE  MemFInterleaveBanks
extern OPTION_MEM_FEATURE_NB MemFUndoInterleaveBanks;
#define MEM_FEATURE_UNDO_BANK_INTERLEAVE MemFUndoInterleaveBanks

#define MEM_FEATURE_NODE_INTERLEAVE_CHECK  MemFDefRet
#define MEM_FEATURE_NODE_INTERLEAVE  MemFDefRet
#define MEM_MAIN_FEATURE_NODE_INTERLEAVE  MemMDefRet

extern OPTION_MEM_FEATURE_NB MemFInterleaveChannels;
#define MEM_FEATURE_CHANNEL_INTERLEAVE  MemFInterleaveChannels

extern OPTION_MEM_FEATURE_MAIN MemMEcc;
#define MEM_MAIN_FEATURE_ECC  MemMEcc
extern OPTION_MEM_FEATURE_NB MemFCheckECC;
extern OPTION_MEM_FEATURE_NB MemFInitECC;
#define MEM_FEATURE_CK_ECC   MemFCheckECC
#define MEM_FEATURE_ECC   MemFInitECC
#define MEM_FEATURE_ECCX8  MemMDefRet

#define MEM_FEATURE_EMP   MemFInitEMP

extern OPTION_MEM_FEATURE_MAIN MemMMctMemClr;
#define MEM_MAIN_FEATURE_MEM_CLEAR  MemMMctMemClr

#define MEM_MAIN_FEATURE_AGGRESSOR  MemMDefRet
#define MEM_FEATURE_AGGRESSOR  MemFDefRet

#undef MEM_MAIN_FEATURE_MEM_DMI
extern OPTION_MEM_FEATURE_MAIN MemFDMISupport34;
#define MEM_MAIN_FEATURE_MEM_DMI MemFDMISupport34

extern OPTION_MEM_FEATURE_MAIN MemFCratSupport;
#define MEM_MAIN_FEATURE_MEM_CRAT MemFCratSupport

extern OPTION_MEM_FEATURE_NB MemFOnDimmThermal;
#define MEM_FEATURE_ONDIMMTHERMAL MemFOnDimmThermal

extern OPTION_MEM_FEATURE_MAIN MemMLvDdr3;
extern OPTION_MEM_FEATURE_NB MemFLvDdr3;
#define MEM_MAIN_FEATURE_LVDDR3 MemMLvDdr3
#define MEM_FEATURE_LVDDR3 MemFLvDdr3

extern OPTION_MEM_FEATURE_NB MemFLvDdr4;
#define MEM_FEATURE_LVDDR4 MemFLvDdr4

extern OPTION_MEM_FEATURE_NB MemFInterleaveRegion;
#define MEM_FEATURE_REGION_INTERLEAVE    MemFInterleaveRegion

extern OPTION_MEM_FEATURE_MAIN MemMUmaAlloc;
#define MEM_MAIN_FEATURE_UMAALLOC   MemMUmaAlloc

#define MEM_MAIN_FEATURE_TRAINING  MemMDefRet

extern OPTION_MEM_FEATURE_MAIN MemMRASExcludeDIMM;
#define MEM_MAIN_FEATURE_DIMM_EXCLUDE  MemMRASExcludeDIMM
extern OPTION_MEM_FEATURE_NB MemFRASExcludeDIMM;
#define MEM_FEATURE_DIMM_EXCLUDE  MemFRASExcludeDIMM

extern OPTION_MEM_FEATURE_NB MemFAMP;
#define MEM_FEATURE_AMP  MemFAMP

#define MEM_FEATURE_DATA_EYE  MemFDefRet


  /*----------------------------------------------------------------------------------
   * TECHNOLOGY BLOCK CONSTRUCTOR FUNCTION ASSIGNMENTS
   *
   *----------------------------------------------------------------------------------
  */
#define MEM_TECH_CONSTRUCTOR_DDR2

extern MEM_TECH_CONSTRUCTOR MemConstructTechBlock3;
#define MEM_TECH_CONSTRUCTOR_DDR3 MemConstructTechBlock3,
#define  MEM_TECH_FEATURE_HW_DRAMINIT MemTFeatDef
#define MEM_TECH_FEATURE_SW_DRAMINIT  MemTFeatDef

extern MEM_TECH_CONSTRUCTOR MemConstructTechBlock4;
#define MEM_TECH_CONSTRUCTOR_DDR4 MemConstructTechBlock4,
#define  MEM_TECH_FEATURE_HW_DRAMINIT MemTFeatDef
#define MEM_TECH_FEATURE_SW_DRAMINIT  MemTFeatDef

  /*---------------------------------------------------------------------------------------------------
   * FEATURE BLOCKS
   *
   *  This section instantiates a feature block structure for each memory controller installed
   *  by the platform solution install file.
   *---------------------------------------------------------------------------------------------------
   */
extern OPTION_MEM_FEATURE_NB MemFStandardTraining;

  /*---------------------------------------------------------------------------------------------------
   * CARRIZO FEATURE BLOCK
   *---------------------------------------------------------------------------------------------------
   */
    /*-------------
     * DDR3 FEATURES
     *--------------
    */
#undef MEM_MAIN_FEATURE_LVDDR3
extern OPTION_MEM_FEATURE_MAIN MemMLvDdr3PerformanceEnhPre;
#define MEM_MAIN_FEATURE_LVDDR3 MemMLvDdr3PerformanceEnhPre

    /*--------------
     * DDR4 FEATURES
     *--------------
    */
#undef MEM_MAIN_FEATURE_LVDDR4
//extern OPTION_MEM_FEATURE_MAIN MemMLvDdr4PerformanceEnhPre;
//#define MEM_MAIN_FEATURE_LVDDR4 MemMLvDdr4PerformanceEnhPre
#define MEM_MAIN_FEATURE_LVDDR4 MemMDefRet

#undef MEM_LOAD_PMU_FIRMWARE
extern OPTION_MEM_FEATURE_NB MemNLoadPmuFirmwareCZ;
#define MEM_LOAD_PMU_FIRMWARE MemNLoadPmuFirmwareCZ

#undef MEM_TECH_FEATURE_DRAMINIT
#define MEM_TECH_FEATURE_DRAMINIT   MemTFeatDef

extern OPTION_MEM_FEATURE_NB MemNInitEarlySampleSupportCZ;
#undef MEM_EARLY_SAMPLE_SUPPORT
#define MEM_EARLY_SAMPLE_SUPPORT    MemNInitEarlySampleSupportCZ

extern OPTION_MEM_FEATURE_NB MemFInterleaveMultiChannels;
#undef  MEM_FEATURE_CHANNEL_INTERLEAVE
#define MEM_FEATURE_CHANNEL_INTERLEAVE MemFInterleaveMultiChannels

#undef  MEM_FEATURE_REGION_INTERLEAVE
#define MEM_FEATURE_REGION_INTERLEAVE MemFDefRet

#undef MEM_FEATURE_TRAINING
#define MEM_FEATURE_TRAINING    MemFDefRet
#undef MEM_TECH_FEATURE_CPG
#define MEM_TECH_FEATURE_CPG    MemFDefRet
#undef MEM_TECH_FEATURE_HWRXEN
#define MEM_TECH_FEATURE_HWRXEN    MemFDefRet

#undef MEM_NB_SUPPORT_CZ
#undef MEM_NB_FEAT_BLOCK_CZ
extern MEM_NB_CONSTRUCTOR MemConstructNBBlockCZ;
extern MEM_INITIALIZER MemNInitDefaultsCZ;
#define MEM_NB_SUPPORT_CZ { MEM_NB_SUPPORT_STRUCT_VERSION, MemConstructNBBlockCZ, MemNInitDefaultsCZ, MEM_FEATURE_S3_RESUME_CONSTRUCTOR_CZ, MEM_IDENDIMM_CZ, MEM_TRANS_SYS_ADDR_TO_CS_CZ }
#define MEM_NB_FEAT_BLOCK_CZ {MEM_FEAT_BLOCK_NB_STRUCT_VERSION, MemFDefRet, MemFDefRet, MemFDefRet, MemFDefRet, MemFDefRet, MemFDefRet, MemFDefRet, MemFDefRet, MemFDefRet, \
                              MemFDefRet, MemFDefRet, MemFDefRet, MemTFeatDef, MemFDefRet, MemFDefRet, MemFDefRet, MemFDefRet, MemFDefRet, MemFDefRet, \
                              MemFDefRet, MemFDefRet, MemFDefRet, MemFDefRet, MemFDefRet}

  /*---------------------------------------------------------------------------------------------------
   * MAIN FEATURE BLOCK
   *---------------------------------------------------------------------------------------------------
   */
#define MEM_FEAT_BLOCK_MAIN {MEM_FEAT_BLOCK_MAIN_STRUCT_VERSION, MEM_MAIN_FEATURE_TRAINING, MEM_MAIN_FEATURE_DIMM_EXCLUDE, MEM_MAIN_FEATURE_ONLINE_SPARE, \
                            MEM_MAIN_FEATURE_NODE_INTERLEAVE, MEM_MAIN_FEATURE_ECC, MEM_MAIN_FEATURE_MEM_CLEAR, MEM_MAIN_FEATURE_MEM_DMI, MEM_MAIN_FEATURE_MEM_CRAT, \
                            MEM_MAIN_FEATURE_LVDDR3, MEM_MAIN_FEATURE_UMAALLOC, MEM_MAIN_FEATURE_MEM_SAVE, MEM_MAIN_FEATURE_MEM_RESTORE, MEM_MAIN_FEATURE_MEM_S3_SAVE, \
                            MEM_MAIN_FEATURE_AGGRESSOR, MEM_MAIN_FEATURE_LVDDR4}

  /*---------------------------------------------------------------------------------------------------
   * Technology Training SPECIFIC CONFIGURATION
   *
   *
   *---------------------------------------------------------------------------------------------------
   */
  // Set Default values //
#undef NB_TRAIN_FLOW_DDR3
#define NB_TRAIN_FLOW_DDR3    (BOOLEAN (*) (MEM_NB_BLOCK*)) memDefTrue

#undef NB_TRAIN_FLOW_DDR2
#define NB_TRAIN_FLOW_DDR2    (BOOLEAN (*) (MEM_NB_BLOCK*)) memDefTrue

#define MEM_TECH_TRAINING_FEAT_NULL_TERNMIATOR 0

#define NB_TRAIN_FLOW_DDR2    (BOOLEAN (*) (MEM_NB_BLOCK*)) memDefTrue
#define NB_TRAIN_FLOW_DDR3    (BOOLEAN (*) (MEM_NB_BLOCK*)) memDefTrue
#undef MEM_TECH_CONSTRUCTOR_DDR2
#define MEM_TECH_CONSTRUCTOR_DDR2

#define MEM_TECH_ENABLE_TRAINING_SEQUENCE_END { MEM_NB_SUPPORT_STRUCT_VERSION, 0, 0, 0 }
MEM_FEAT_TRAIN_SEQ memTrainSequenceDDR2[] = {
  MEM_TECH_ENABLE_TRAINING_SEQUENCE_END
};

MEM_FEAT_TRAIN_SEQ memTrainSequenceDDR3[] = {
  MEM_TECH_ENABLE_TRAINING_SEQUENCE_END
};
  /*---------------------------------------------------------------------------------------------------
   * NB TRAINING FLOW CONTROL
   *
   *
   *---------------------------------------------------------------------------------------------------
   */
OPTION_MEM_FEATURE_NB* memNTrainFlowControl[] = {    // Training flow control
  NB_TRAIN_FLOW_DDR2,
  NB_TRAIN_FLOW_DDR3,
};
  /*---------------------------------------------------------------------------------------------------
   * TECHNOLOGY BLOCK
   *
   *
   *---------------------------------------------------------------------------------------------------
   */
MEM_TECH_CONSTRUCTOR* memTechInstalled[] = {    // Types of technology installed
  MEM_TECH_CONSTRUCTOR_DDR2
  MEM_TECH_CONSTRUCTOR_DDR3
  MEM_TECH_CONSTRUCTOR_DDR4
  NULL
};
   /*---------------------------------------------------------------------------------------------------
   * PLATFORM SPECIFIC BLOCK FORM FACTOR DEFINITION
   *
   *
   *---------------------------------------------------------------------------------------------------
   */

  /*---------------------------------------------------------------------------------------------------
   * PLATFORM-SPECIFIC CONFIGURATION
   *
   *
   *---------------------------------------------------------------------------------------------------
   */

  /*----------------------------------------------------------------------
   * DEFAULT PSCFG DEFINITIONS
   *
   *----------------------------------------------------------------------
   */

MEM_PLATFORM_CFG* memPlatformTypeInstalled[] = {
  NULL
};
CONST UINTN SIZE_OF_PLATFORM = (sizeof (memPlatformTypeInstalled) / sizeof (MEM_PLATFORM_CFG*));
#if SIZE_OF_PLATFORM > MAX_PLATFORM_TYPES
  #error   Size of memPlatformTypeInstalled array larger than MAX_PLATFORM_TYPES
#endif

  /*---------------------------------------------------------------------------------------------------
   * EXTRACTABLE PLATFORM SPECIFIC CONFIGURATION
   *
   *
   *---------------------------------------------------------------------------------------------------
   */
#define MEM_PSC_FLOW_BLOCK_END NULL
#define PSC_TBL_END NULL
#define MEM_PSC_FLOW_DEFTRUE (BOOLEAN (*) (MEM_NB_BLOCK*, MEM_PSC_TABLE_BLOCK *)) memDefTrue

#define MEM_PSC_FLOW_BLOCK_D3_CZ
#define MEM_PSC_FLOW_BLOCK_D4_CZ


extern PSC_TBL_ENTRY CZMaxFreqTblEntUD3;
#define PSC_TBL_CZ_UDIMM3_MAX_FREQ &CZMaxFreqTblEntUD3,

extern PSC_TBL_ENTRY CZCadBusTblEnUTree3;
#define PSC_TBL_CZ_UDIMM3_CAD_BUS_TREE  &CZCadBusTblEnUTree3,
extern PSC_TBL_ENTRY CZCadBusTblEnUDC3;
#define PSC_TBL_CZ_UDIMM3_CAD_BUS_DAISH_CHAIN  &CZCadBusTblEnUDC3,

extern PSC_TBL_ENTRY CZDataBusTblEnUTree3;
#define PSC_TBL_CZ_UDIMM3_DATA_BUS_TREE  &CZDataBusTblEnUTree3,
extern PSC_TBL_ENTRY CZDataBusTblEnUDC3;
#define PSC_TBL_CZ_UDIMM3_DATA_BUS_DAISY_CHAIN  &CZDataBusTblEnUDC3,
extern PSC_TBL_ENTRY CZMaxFreqTblEntSOD3;
#define PSC_TBL_CZ_SODIMM3_MAX_FREQ  &CZMaxFreqTblEntSOD3,

extern PSC_TBL_ENTRY CZCadBusTblEnSOTree3;
#define PSC_TBL_CZ_SODIMM3_CAD_BUS_TREE  &CZCadBusTblEnSOTree3,
extern PSC_TBL_ENTRY CZCadBusTblEnSODC3;
#define PSC_TBL_CZ_SODIMM3_CAD_BUS_DAISY_CHAIN  &CZCadBusTblEnSODC3,

extern PSC_TBL_ENTRY CZDataBusTblEnSOTree3;
#define PSC_TBL_CZ_SODIMM3_DATA_BUS_TREE  &CZDataBusTblEnSOTree3,
extern PSC_TBL_ENTRY CZDataBusTblEnSODC3;
#define PSC_TBL_CZ_SODIMM3_DATA_BUS_DAISY_CHAIN  &CZDataBusTblEnSODC3,
extern PSC_TBL_ENTRY CZMaxFreqTblEntUD4;
#define PSC_TBL_CZ_UDIMM4_MAX_FREQ &CZMaxFreqTblEntUD4,

extern PSC_TBL_ENTRY CZCadBusTblEnUTreeD4;
#define PSC_TBL_CZ_UDIMM4_CAD_BUS_TREE &CZCadBusTblEnUTreeD4,
extern PSC_TBL_ENTRY CZDataBusTblEnUTreeD4_A0;
#define PSC_TBL_CZ_UDIMM4_DATA_BUS_A0_TREE &CZDataBusTblEnUTreeD4_A0,
extern PSC_TBL_ENTRY CZDataBusTblEnUTreeD4;
#define PSC_TBL_CZ_UDIMM4_DATA_BUS_TREE &CZDataBusTblEnUTreeD4,

extern PSC_TBL_ENTRY CZCadBusTblEnUDCD4;
#define PSC_TBL_CZ_UDIMM4_CAD_BUS_DAISY_CHAIN &CZCadBusTblEnUDCD4,
extern PSC_TBL_ENTRY CZDataBusTblEnUDCD4_A0;
#define PSC_TBL_CZ_UDIMM4_DATA_BUS_A0_DAISY_CHAIN &CZDataBusTblEnUDCD4_A0,
extern PSC_TBL_ENTRY CZDataBusTblEnUDCD4;
#define PSC_TBL_CZ_UDIMM4_DATA_BUS_DAISY_CHAIN &CZDataBusTblEnUDCD4,

extern PSC_TBL_ENTRY BRCadBusTblEnUTreeD4;
#define PSC_TBL_BR_UDIMM4_CAD_BUS_TREE &BRCadBusTblEnUTreeD4,
extern PSC_TBL_ENTRY BRDataBusTblEnUTreeD4;
#define PSC_TBL_BR_UDIMM4_DATA_BUS_A0_TREE &BRDataBusTblEnUTreeD4,

extern PSC_TBL_ENTRY BRCadBusTblEnUDCD4;
#define PSC_TBL_BR_UDIMM4_CAD_BUS_DAISY_CHAIN &BRCadBusTblEnUDCD4,
extern PSC_TBL_ENTRY BRDataBusTblEnUDCD4;
#define PSC_TBL_BR_UDIMM4_DATA_BUS_A0_DAISY_CHAIN &BRDataBusTblEnUDCD4,
extern PSC_TBL_ENTRY CZMaxFreqTblEntSOD4;
#define PSC_TBL_CZ_SODIMM4_MAX_FREQ  &CZMaxFreqTblEntSOD4,
extern PSC_TBL_ENTRY BRMaxFreqTblEntSOD4;
#define PSC_TBL_BR_SODIMM4_MAX_FREQ  &BRMaxFreqTblEntSOD4,

extern PSC_TBL_ENTRY CZCadBusTblEnSOTree4;
#define PSC_TBL_CZ_SODIMM4_CAD_BUS_TREE  &CZCadBusTblEnSOTree4,
extern PSC_TBL_ENTRY CZDataBusTblEnSOTree4_A0;
#define PSC_TBL_CZ_SODIMM4_DATA_BUS_A0_TREE  &CZDataBusTblEnSOTree4_A0,
extern PSC_TBL_ENTRY CZDataBusTblEnSOTree4;
#define PSC_TBL_CZ_SODIMM4_DATA_BUS_TREE  &CZDataBusTblEnSOTree4,

extern PSC_TBL_ENTRY CZCadBusTblEnSODC4;
#define PSC_TBL_CZ_SODIMM4_CAD_BUS_DAISY_CHAIN  &CZCadBusTblEnSODC4,
extern PSC_TBL_ENTRY CZDataBusTblEnSODC4_A0;
#define PSC_TBL_CZ_SODIMM4_DATA_BUS_A0_DAISY_CHAIN  &CZDataBusTblEnSODC4_A0,
extern PSC_TBL_ENTRY CZDataBusTblEnSODC4;
#define PSC_TBL_CZ_SODIMM4_DATA_BUS_DAISY_CHAIN  &CZDataBusTblEnSODC4,

extern MEM_PSC_FLOW MemPGetMaxFreqSupported;

extern PSC_TBL_ENTRY CZOdtPatTblEnt3;
extern MEM_PSC_FLOW MemPLookupDataBusCfgTabs3;

PSC_TBL_ENTRY* memPSCTblODTPatArrayD3CZ[] = {
  &CZOdtPatTblEnt3,
  PSC_TBL_END
};

PSC_TBL_ENTRY* memPSCTblMaxFreqArrayD3CZ[] = {
  PSC_TBL_CZ_SODIMM3_MAX_FREQ
  PSC_TBL_CZ_UDIMM3_MAX_FREQ
  PSC_TBL_END
};

PSC_TBL_ENTRY* memPSCTblCadBusArrayD3CZ[] = {
  PSC_TBL_CZ_UDIMM3_CAD_BUS_TREE
  PSC_TBL_CZ_UDIMM3_CAD_BUS_DAISH_CHAIN
  PSC_TBL_CZ_SODIMM3_CAD_BUS_TREE
  PSC_TBL_CZ_SODIMM3_CAD_BUS_DAISY_CHAIN
  PSC_TBL_END
};

PSC_TBL_ENTRY* memPSCTblDataBusArrayD3CZ[] = {
  PSC_TBL_CZ_UDIMM3_DATA_BUS_TREE
  PSC_TBL_CZ_UDIMM3_DATA_BUS_DAISY_CHAIN
  PSC_TBL_CZ_SODIMM3_DATA_BUS_TREE
  PSC_TBL_CZ_SODIMM3_DATA_BUS_DAISY_CHAIN
  PSC_TBL_END
};

MEM_PSC_TABLE_BLOCK memPSCTblBlockD3CZ = {
  (PSC_TBL_ENTRY **)&memPSCTblMaxFreqArrayD3CZ,
  (PSC_TBL_ENTRY **)&memPSCTblDataBusArrayD3CZ,
  (PSC_TBL_ENTRY **)&memPSCTblODTPatArrayD3CZ,
  (PSC_TBL_ENTRY **)&memPSCTblCadBusArrayD3CZ,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL
};

MEM_PSC_FLOW_BLOCK memPlatSpecFlowD3CZ = {
  &memPSCTblBlockD3CZ,
  MemPGetMaxFreqSupported,
  MemPLookupDataBusCfgTabs3,
  MEM_PSC_FLOW_DEFTRUE,
  MEM_PSC_FLOW_DEFTRUE,
  MEM_PSC_FLOW_DEFTRUE,
  MEM_PSC_FLOW_DEFTRUE,
  MEM_PSC_FLOW_DEFTRUE,
  MEM_PSC_FLOW_DEFTRUE,
  MEM_PSC_FLOW_DEFTRUE,
  MEM_PSC_FLOW_DEFTRUE,
  MEM_PSC_FLOW_DEFTRUE,
  MEM_PSC_FLOW_DEFTRUE
};
#undef MEM_PSC_FLOW_BLOCK_D3_CZ
#define MEM_PSC_FLOW_BLOCK_D3_CZ &memPlatSpecFlowD3CZ,

extern PSC_TBL_ENTRY CZOdtPatTblEnt4;
extern MEM_PSC_FLOW MemPLookupDataBusCfgTabs4;

PSC_TBL_ENTRY* memPSCTblODTPatArrayD4CZ[] = {
  &CZOdtPatTblEnt4,
  PSC_TBL_END
};

PSC_TBL_ENTRY* memPSCTblMaxFreqArrayD4CZ[] = {
  PSC_TBL_CZ_UDIMM4_MAX_FREQ
  PSC_TBL_CZ_SODIMM4_MAX_FREQ
  PSC_TBL_BR_SODIMM4_MAX_FREQ
  PSC_TBL_END
};

PSC_TBL_ENTRY* memPSCTblCadBusArrayD4CZ[] = {
  PSC_TBL_CZ_UDIMM4_CAD_BUS_TREE
  PSC_TBL_CZ_UDIMM4_CAD_BUS_DAISY_CHAIN
  PSC_TBL_BR_UDIMM4_CAD_BUS_TREE
  PSC_TBL_BR_UDIMM4_CAD_BUS_DAISY_CHAIN
  PSC_TBL_CZ_SODIMM4_CAD_BUS_TREE
  PSC_TBL_CZ_SODIMM4_CAD_BUS_DAISY_CHAIN
  PSC_TBL_END
};

PSC_TBL_ENTRY* memPSCTblDataBusArrayD4CZ[] = {
  PSC_TBL_CZ_UDIMM4_DATA_BUS_A0_TREE
  PSC_TBL_CZ_UDIMM4_DATA_BUS_TREE
  PSC_TBL_CZ_UDIMM4_DATA_BUS_A0_DAISY_CHAIN
  PSC_TBL_CZ_UDIMM4_DATA_BUS_DAISY_CHAIN
  PSC_TBL_BR_UDIMM4_DATA_BUS_A0_TREE
  PSC_TBL_BR_UDIMM4_DATA_BUS_A0_DAISY_CHAIN
  PSC_TBL_CZ_SODIMM4_DATA_BUS_A0_TREE
  PSC_TBL_CZ_SODIMM4_DATA_BUS_TREE
  PSC_TBL_CZ_SODIMM4_DATA_BUS_A0_DAISY_CHAIN
  PSC_TBL_CZ_SODIMM4_DATA_BUS_DAISY_CHAIN
  PSC_TBL_END
};

MEM_PSC_TABLE_BLOCK memPSCTblBlockD4CZ = {
  (PSC_TBL_ENTRY **)&memPSCTblMaxFreqArrayD4CZ,
  (PSC_TBL_ENTRY **)&memPSCTblDataBusArrayD4CZ,
  (PSC_TBL_ENTRY **)&memPSCTblODTPatArrayD4CZ,
  (PSC_TBL_ENTRY **)&memPSCTblCadBusArrayD4CZ,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL
};

MEM_PSC_FLOW_BLOCK memPlatSpecFlowD4CZ = {
  &memPSCTblBlockD4CZ,
  MemPGetMaxFreqSupported,
  MemPLookupDataBusCfgTabs4,
  MEM_PSC_FLOW_DEFTRUE,
  MEM_PSC_FLOW_DEFTRUE,
  MEM_PSC_FLOW_DEFTRUE,
  MEM_PSC_FLOW_DEFTRUE,
  MEM_PSC_FLOW_DEFTRUE,
  MEM_PSC_FLOW_DEFTRUE,
  MEM_PSC_FLOW_DEFTRUE,
  MEM_PSC_FLOW_DEFTRUE,
  MEM_PSC_FLOW_DEFTRUE,
  MEM_PSC_FLOW_DEFTRUE
};
#undef MEM_PSC_FLOW_BLOCK_D4_CZ
#define MEM_PSC_FLOW_BLOCK_D4_CZ &memPlatSpecFlowD4CZ,

MEM_PSC_FLOW_BLOCK* memPlatSpecFlowArray[] = {
  MEM_PSC_FLOW_BLOCK_D3_CZ
  MEM_PSC_FLOW_BLOCK_D4_CZ
  MEM_PSC_FLOW_BLOCK_END
};

  /*---------------------------------------------------------------------------------------------------
  *
  *  LRDIMM CONTROL
  *
  *---------------------------------------------------------------------------------------------------
  */

#define MEM_TECH_FEATURE_LRDIMM_INIT    MemTFeatDef

MEM_TECH_LRDIMM memLrdimmSupported = {
  MEM_TECH_LRDIMM_STRUCT_VERSION,
  MEM_TECH_FEATURE_LRDIMM_INIT
};

/*---------------------------------------------------------------------------------------------------
 * OPTION MEMORY INSTALL
 *
 *---------------------------------------------------------------------------------------------------
 */
MEM_OPTION_INSTALL_STRUCT OptionMemoryInstall = {
  OPTION_MEM_INSTALL_VERSION,
  memPlatformTypeInstalled,
  memPlatSpecFlowArray,
  memTechInstalled,
  MEM_MAIN_FLOW_CONTROL_PTR_CZ,
  MEM_NB_SUPPORT_CZ,
  MEM_FEAT_BLOCK_MAIN,
  MEM_NB_FEAT_BLOCK_CZ
};

