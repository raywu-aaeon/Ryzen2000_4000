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

#ifndef _OPTION_MEMORY_INSTALL_H_
#define _OPTION_MEMORY_INSTALL_H_

/* Memory Includes */
#include "OptionMemory.h"

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

#if (OPTION_POST_MEM_INIT == FALSE)
  /* -----------------------------------------------------------------------------*/
  /**
   *
   *      This function is used in place of an un-supported function that returns FALSE.
   *
   */
  BOOLEAN memDefFalse (
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
  BOOLEAN MemTFeatDef (
    IN OUT   MEM_TECH_BLOCK *TechPtr
    )
  {
    return TRUE;
  }

  /* -----------------------------------------------------------------------------*/
  /**
   *
   *         This is the default return function
   */
  VOID  memDefRet (
    )
  {
  }

  /* -----------------------------------------------------------------------------*/
  /**
   *
   *      This function is the default return function that returns TRUE
   *
   */
  BOOLEAN memDefTrue (
    )
  {
    return TRUE;
  }

  /* -----------------------------------------------------------------------------*/
  /**
   *
   *         This is the default return function for flow control
   */
  AGESA_STATUS MemMFlowDef (
    IN OUT   MEM_MAIN_DATA_BLOCK *MemMainPtr
    )
  {
    MemMainPtr->MemPtr->IsFlowControlSupported = FALSE;
    return AGESA_SUCCESS;
  }
// Set Defaults //
#define MEM_MAIN_FEATURE_MEM_S3_SAVE MemMDefRet

#endif

#if (OPTION_MEMCTLR_CZ == TRUE)
  #if ((AGESA_ENTRY_INIT_RESUME == TRUE) || (AGESA_ENTRY_INIT_RTB == TRUE) || (AGESA_ENTRY_INIT_LATE_RESTORE == TRUE) || ((AGESA_ENTRY_INIT_POST) && (OPTION_S3_MEM_SUPPORT == TRUE)))
    #if (OPTION_S3_MEM_SUPPORT == TRUE)
      extern MEM_RESUME_CONSTRUCTOR MemS3ResumeConstructNBBlockCZ;
      #define MEM_FEATURE_S3_RESUME_CONSTRUCTOR_CZ MemS3ResumeConstructNBBlockCZ
      #if ((AGESA_ENTRY_INIT_RESUME == TRUE) || (AGESA_ENTRY_INIT_RTB == TRUE) || (AGESA_ENTRY_INIT_LATE_RESTORE == TRUE))
        extern OPTION_MEM_FEATURE_MAIN MemMS3Save;
        #define MEM_MAIN_FEATURE_MEM_S3_SAVE MemMS3Save
      #else
        #define MEM_MAIN_FEATURE_MEM_S3_SAVE MemMDefRet
      #endif
    #else
      #define MEM_FEATURE_S3_RESUME_CONSTRUCTOR_CZ MemFS3DefConstructorRet
      #define MEM_MAIN_FEATURE_MEM_S3_SAVE MemMDefRet
    #endif
  #else
    #define MEM_FEATURE_S3_RESUME_CONSTRUCTOR_CZ MemFS3DefConstructorRet
    #define MEM_MAIN_FEATURE_MEM_S3_SAVE MemMDefRet
  #endif
  #if (AGESA_ENTRY_INIT_GENERAL_SERVICES == TRUE)
    extern MEM_IDENDIMM_CONSTRUCTOR MemNIdentifyDimmConstructorCZ;
    #define MEM_IDENDIMM_CZ MemNIdentifyDimmConstructorCZ
    extern MEM_TRANS_SYS_ADDR_TO_CS MemFTransSysAddrToCsCZ;
    #define MEM_TRANS_SYS_ADDR_TO_CS_CZ MemFTransSysAddrToCsCZ
  #else
    #define MEM_IDENDIMM_CZ MemNIdentifyDimmConstructorRetDef
    #define MEM_TRANS_SYS_ADDR_TO_CS_CZ MemNTransSysAddrToCsRetDef
  #endif
#endif // OPTION_MEMCTLR_CZ

#if (OPTION_MEMCTLR_ST == TRUE)
  #if ((AGESA_ENTRY_INIT_RESUME == TRUE) || (AGESA_ENTRY_INIT_RTB == TRUE) || (AGESA_ENTRY_INIT_LATE_RESTORE == TRUE) || ((AGESA_ENTRY_INIT_POST) && (OPTION_S3_MEM_SUPPORT == TRUE)))
    #if (OPTION_S3_MEM_SUPPORT == TRUE)
      extern MEM_RESUME_CONSTRUCTOR MemS3ResumeConstructNBBlockST;
      #define MEM_FEATURE_S3_RESUME_CONSTRUCTOR_ST MemS3ResumeConstructNBBlockST
      #if ((AGESA_ENTRY_INIT_RESUME == TRUE) || (AGESA_ENTRY_INIT_RTB == TRUE) || (AGESA_ENTRY_INIT_LATE_RESTORE == TRUE))
        extern OPTION_MEM_FEATURE_MAIN MemMS3Save;
        #define MEM_MAIN_FEATURE_MEM_S3_SAVE MemMS3Save
      #else
        #define MEM_MAIN_FEATURE_MEM_S3_SAVE MemMDefRet
      #endif
    #else
      #define MEM_FEATURE_S3_RESUME_CONSTRUCTOR_ST MemFS3DefConstructorRet
      #define MEM_MAIN_FEATURE_MEM_S3_SAVE MemMDefRet
    #endif
  #else
    #define MEM_FEATURE_S3_RESUME_CONSTRUCTOR_ST MemFS3DefConstructorRet
    #define MEM_MAIN_FEATURE_MEM_S3_SAVE MemMDefRet
  #endif
  #if (AGESA_ENTRY_INIT_GENERAL_SERVICES == TRUE)
    extern MEM_IDENDIMM_CONSTRUCTOR MemNIdentifyDimmConstructorST;
    #define MEM_IDENDIMM_ST MemNIdentifyDimmConstructorST
    extern MEM_TRANS_SYS_ADDR_TO_CS MemFTransSysAddrToCsST;
    #define MEM_TRANS_SYS_ADDR_TO_CS_ST MemFTransSysAddrToCsST
  #else
    #define MEM_IDENDIMM_ST MemNIdentifyDimmConstructorRetDef
    #define MEM_TRANS_SYS_ADDR_TO_CS_ST MemNTransSysAddrToCsRetDef
  #endif
#endif // OPTION_MEMCTLR_ST
/*----------------------------------------------------------------------------------
 * NORTHBRIDGE BLOCK CONSTRUCTOR AND INITIALIZER FUNCTION DEFAULT ASSIGNMENTS
 *
 *----------------------------------------------------------------------------------
*/
#define MEM_NB_SUPPORT_CZ
#define MEM_NB_SUPPORT_ST
#define MEM_NB_SUPPORT_END { MEM_NB_SUPPORT_STRUCT_VERSION, 0, 0, 0, 0, 0, 0 }


#if (AGESA_ENTRY_INIT_POST == TRUE)
  /*----------------------------------------------------------------------------------
   * FLOW CONTROL FUNCTION
   *
   *  This section selects the function that controls the memory initialization sequence
   *  based upon the number of processor families that the BIOS will support.
   */
  extern MEM_FLOW_CFG MemMFlowDef;

  #if (OPTION_MEMCTLR_CZ == TRUE)
    //
    // DDR3 Only
    //
    #if ((OPTION_DDR3 == TRUE) && (OPTION_DDR4 == FALSE))
      extern MEM_FLOW_CFG MemMFlowD3CZ;
      #define MEM_MAIN_FLOW_CONTROL_PTR_CZ MemMFlowD3CZ,
    #else
      //
      // DDR4 Only
      //
      #if ((OPTION_DDR3 == FALSE) && (OPTION_DDR4 == TRUE))
        extern MEM_FLOW_CFG MemMFlowD4CZ;
        #define MEM_MAIN_FLOW_CONTROL_PTR_CZ MemMFlowD4CZ,
      #else
        //
        // DDR3 and DDR4 Combo
        //
        extern MEM_FLOW_CFG MemMFlowD34CZ;
        #define MEM_MAIN_FLOW_CONTROL_PTR_CZ MemMFlowD34CZ,
      #endif
    #endif
  #else
    #define MEM_MAIN_FLOW_CONTROL_PTR_CZ MemMFlowDef,
  #endif

  #if (OPTION_MEMCTLR_ST == TRUE)
    //
    // DDR3 Only
    //
    #if ((OPTION_DDR3 == TRUE) && (OPTION_DDR4 == FALSE))
      extern MEM_FLOW_CFG MemMFlowD3ST;
      #define MEM_MAIN_FLOW_CONTROL_PTR_ST MemMFlowD3ST,
    #else
      //
      // DDR4 Only
      //
      #if ((OPTION_DDR3 == FALSE) && (OPTION_DDR4 == TRUE))
        extern MEM_FLOW_CFG MemMFlowD4ST;
        #define MEM_MAIN_FLOW_CONTROL_PTR_ST MemMFlowD4ST,
      #else
        //
        // DDR3 and DDR4 Combo
        //
        extern MEM_FLOW_CFG MemMFlowD34ST;
        #define MEM_MAIN_FLOW_CONTROL_PTR_ST MemMFlowD34ST,
      #endif
    #endif
  #else
    #define MEM_MAIN_FLOW_CONTROL_PTR_ST MemMFlowDef,
  #endif

  MEM_FLOW_CFG* memFlowControlInstalled[] = {
    MEM_MAIN_FLOW_CONTROL_PTR_CZ
    MEM_MAIN_FLOW_CONTROL_PTR_ST
    NULL
  };

  #if (OPTION_ONLINE_SPARE == TRUE)
    extern OPTION_MEM_FEATURE_MAIN MemMOnlineSpare;
    #define MEM_MAIN_FEATURE_ONLINE_SPARE  MemMOnlineSpare
    extern OPTION_MEM_FEATURE_NB MemFOnlineSpare;
    #define MEM_FEATURE_ONLINE_SPARE  MemFOnlineSpare
  #else
    #define MEM_MAIN_FEATURE_ONLINE_SPARE  MemMDefRet
    #define MEM_FEATURE_ONLINE_SPARE  MemFDefRet
  #endif

  #if (OPTION_MEM_RESTORE == TRUE)
    extern OPTION_MEM_FEATURE_MAIN MemMContextSave;
    extern OPTION_MEM_FEATURE_MAIN MemMContextRestore;
    #define MEM_MAIN_FEATURE_MEM_SAVE     MemMContextSave
    #define MEM_MAIN_FEATURE_MEM_RESTORE  MemMContextRestore
  #else
    #define MEM_MAIN_FEATURE_MEM_SAVE     MemMDefRet
    #define MEM_MAIN_FEATURE_MEM_RESTORE  MemMDefRetFalse
  #endif

  #if (OPTION_BANK_INTERLEAVE == TRUE)
    extern OPTION_MEM_FEATURE_NB MemFInterleaveBanks;
    #define MEM_FEATURE_BANK_INTERLEAVE  MemFInterleaveBanks
    extern OPTION_MEM_FEATURE_NB MemFUndoInterleaveBanks;
    #define MEM_FEATURE_UNDO_BANK_INTERLEAVE MemFUndoInterleaveBanks
  #else
    #define MEM_FEATURE_BANK_INTERLEAVE  MemFDefRet
    #define MEM_FEATURE_UNDO_BANK_INTERLEAVE MemFDefRet
  #endif

  #if (OPTION_NODE_INTERLEAVE == TRUE)
    extern OPTION_MEM_FEATURE_MAIN MemMInterleaveNodes;
    #define MEM_MAIN_FEATURE_NODE_INTERLEAVE  MemMInterleaveNodes
    extern OPTION_MEM_FEATURE_NB MemFCheckInterleaveNodes;
    extern OPTION_MEM_FEATURE_NB MemFInterleaveNodes;
    #define MEM_FEATURE_NODE_INTERLEAVE_CHECK  MemFCheckInterleaveNodes
    #define MEM_FEATURE_NODE_INTERLEAVE  MemFInterleaveNodes
  #else
    #define MEM_FEATURE_NODE_INTERLEAVE_CHECK  MemFDefRet
    #define MEM_FEATURE_NODE_INTERLEAVE  MemFDefRet
    #define MEM_MAIN_FEATURE_NODE_INTERLEAVE  MemMDefRet
  #endif

  #if (OPTION_DCT_INTERLEAVE == TRUE)
    extern OPTION_MEM_FEATURE_NB MemFInterleaveChannels;
    #define MEM_FEATURE_CHANNEL_INTERLEAVE  MemFInterleaveChannels
  #else
    #define MEM_FEATURE_CHANNEL_INTERLEAVE  MemFDefRet
  #endif

  #if (OPTION_ECC == TRUE)
    extern OPTION_MEM_FEATURE_MAIN MemMEcc;
    #define MEM_MAIN_FEATURE_ECC  MemMEcc
    extern OPTION_MEM_FEATURE_NB MemFCheckECC;
    extern OPTION_MEM_FEATURE_NB MemFInitECC;
    #define MEM_FEATURE_CK_ECC   MemFCheckECC
    #define MEM_FEATURE_ECC   MemFInitECC
    #define MEM_FEATURE_ECCX8  MemMDefRet
  #else
    #define MEM_MAIN_FEATURE_ECC  MemMDefRet
    #define MEM_FEATURE_CK_ECC   MemFDefRet
    #define MEM_FEATURE_ECC   MemFDefRet
    #define MEM_FEATURE_ECCX8  MemMDefRet
  #endif

  #if (OPTION_EMP == TRUE)
    extern OPTION_MEM_FEATURE_NB MemFInitEMP;
    #define MEM_FEATURE_EMP   MemFInitEMP
  #else
    #define MEM_FEATURE_EMP   MemFDefRet
  #endif

  #if (OPTION_POST_MEM_INIT == TRUE)
    extern OPTION_MEM_FEATURE_MAIN MemMMctMemClr;
    #define MEM_MAIN_FEATURE_MEM_CLEAR  MemMMctMemClr
  #else
    #define MEM_MAIN_FEATURE_MEM_CLEAR   MemMDefRet
  #endif

  #if (OPTION_AGGRESSOR == TRUE)
    extern OPTION_MEM_FEATURE_MAIN MemMAggressor;
    #define MEM_MAIN_FEATURE_AGGRESSOR  MemMAggressor
    extern OPTION_MEM_FEATURE_NB MemFAggressorInit;
    #define MEM_FEATURE_AGGRESSOR  MemFAggressorInit
  #else //#if (OPTION_AGGRESSOR == FALSE)
    #define MEM_MAIN_FEATURE_AGGRESSOR  MemMDefRet
    #define MEM_FEATURE_AGGRESSOR  MemFDefRet
  #endif

  #if (OPTION_DMI == TRUE)
    #if ((OPTION_DDR3 == TRUE) && (OPTION_DDR4 == TRUE))
      #undef MEM_MAIN_FEATURE_MEM_DMI
      extern OPTION_MEM_FEATURE_MAIN MemFDMISupport34;
      #define MEM_MAIN_FEATURE_MEM_DMI MemFDMISupport34
    #elif (OPTION_DDR3 == TRUE)
      #undef MEM_MAIN_FEATURE_MEM_DMI
      extern OPTION_MEM_FEATURE_MAIN MemFDMISupport3;
      #define MEM_MAIN_FEATURE_MEM_DMI MemFDMISupport3
    #elif (OPTION_DDR4 == TRUE)
      #undef MEM_MAIN_FEATURE_MEM_DMI
      extern OPTION_MEM_FEATURE_MAIN MemFDMISupport4;
      #define MEM_MAIN_FEATURE_MEM_DMI MemFDMISupport4
    #else
      #define MEM_MAIN_FEATURE_MEM_DMI MemMDefRet
    #endif
  #else
    #define MEM_MAIN_FEATURE_MEM_DMI MemMDefRet
  #endif

  #if (OPTION_CRAT == TRUE)
    #if (OPTION_POST_MEM_INIT == TRUE)
      extern OPTION_MEM_FEATURE_MAIN MemFCratSupport;
      #define MEM_MAIN_FEATURE_MEM_CRAT MemFCratSupport
    #else
      #define MEM_MAIN_FEATURE_MEM_CRAT MemMDefRet
    #endif
  #else
    #define MEM_MAIN_FEATURE_MEM_CRAT MemMDefRet
  #endif

  #if (OPTION_ONDIMMTHERMAL == TRUE)
    extern OPTION_MEM_FEATURE_NB MemFOnDimmThermal;
    #define MEM_FEATURE_ONDIMMTHERMAL MemFOnDimmThermal
  #else
    #define MEM_FEATURE_ONDIMMTHERMAL MemFDefRet
  #endif

  #if (OPTION_DDR3 == TRUE)
    extern OPTION_MEM_FEATURE_MAIN MemMLvDdr3;
    extern OPTION_MEM_FEATURE_NB MemFLvDdr3;
    #define MEM_MAIN_FEATURE_LVDDR3 MemMLvDdr3
    #define MEM_FEATURE_LVDDR3 MemFLvDdr3
  #else
    #define MEM_MAIN_FEATURE_LVDDR3 MemMDefRet
    #define MEM_FEATURE_LVDDR3 MemFDefRet
  #endif
  #if (OPTION_DDR4 == TRUE)
    extern OPTION_MEM_FEATURE_NB MemFLvDdr4;
    #define MEM_FEATURE_LVDDR4 MemFLvDdr4
  #else
    #define MEM_FEATURE_LVDDR4 MemFDefRet
  #endif
  extern OPTION_MEM_FEATURE_NB MemFInterleaveRegion;
  #define MEM_FEATURE_REGION_INTERLEAVE    MemFInterleaveRegion
  #if (OPTION_POST_MEM_INIT == TRUE)
    extern OPTION_MEM_FEATURE_MAIN MemMUmaAlloc;
    #define MEM_MAIN_FEATURE_UMAALLOC   MemMUmaAlloc
  #else
    #define MEM_MAIN_FEATURE_UMAALLOC   MemMDefRet
  #endif

  #if (OPTION_PARALLEL_TRAINING == TRUE)
    extern OPTION_MEM_FEATURE_MAIN MemMParallelTraining;
    #define MEM_MAIN_FEATURE_TRAINING  MemMParallelTraining
  #else
    #if (OPTION_POST_MEM_INIT == TRUE)
      extern OPTION_MEM_FEATURE_MAIN MemMStandardTraining;
      #define MEM_MAIN_FEATURE_TRAINING  MemMStandardTraining
    #else
      #define MEM_MAIN_FEATURE_TRAINING  MemMDefRet
    #endif
  #endif

  #if (OPTION_DIMM_EXCLUDE == TRUE)
    extern OPTION_MEM_FEATURE_MAIN MemMRASExcludeDIMM;
    #define MEM_MAIN_FEATURE_DIMM_EXCLUDE  MemMRASExcludeDIMM
    extern OPTION_MEM_FEATURE_NB MemFRASExcludeDIMM;
    #define MEM_FEATURE_DIMM_EXCLUDE  MemFRASExcludeDIMM
  #else
    #define MEM_FEATURE_DIMM_EXCLUDE  MemFDefRet
    #define MEM_MAIN_FEATURE_DIMM_EXCLUDE  MemMDefRet
  #endif

  #if (OPTION_AMP == TRUE)
    extern OPTION_MEM_FEATURE_NB MemFAMP;
    #define MEM_FEATURE_AMP  MemFAMP
  #else
    #define MEM_FEATURE_AMP  MemFDefRet
  #endif

  #if (OPTION_DATA_EYE == TRUE)
    extern OPTION_MEM_FEATURE_NB MemF2DDataEyeInit;
    #define MEM_FEATURE_DATA_EYE  MemF2DDataEyeInit
  #else //#if (OPTION_DATA_EYE == FALSE)
    #define MEM_FEATURE_DATA_EYE  MemFDefRet
  #endif

  /*----------------------------------------------------------------------------------
   * TECHNOLOGY BLOCK CONSTRUCTOR FUNCTION ASSIGNMENTS
   *
   *----------------------------------------------------------------------------------
  */
  #if OPTION_DDR2 == TRUE
    extern MEM_TECH_CONSTRUCTOR MemConstructTechBlock2;
    #define MEM_TECH_CONSTRUCTOR_DDR2 MemConstructTechBlock2,
    #if (OPTION_HW_DRAM_INIT == TRUE)
      extern MEM_TECH_FEAT MemTDramInitHw;
      #define MEM_TECH_FEATURE_HW_DRAMINIT  MemTDramInitHw
    #else
      #define MEM_TECH_FEATURE_HW_DRAMINIT  MemTFeatDef
    #endif
    #if (OPTION_SW_DRAM_INIT == TRUE)
      #define MEM_TECH_FEATURE_SW_DRAMINIT  MemTFeatDef
    #else
      #define MEM_TECH_FEATURE_SW_DRAMINIT  MemTFeatDef
    #endif
  #else
    #define MEM_TECH_CONSTRUCTOR_DDR2
  #endif
  #if OPTION_DDR3 == TRUE
    extern MEM_TECH_CONSTRUCTOR MemConstructTechBlock3;
    #define MEM_TECH_CONSTRUCTOR_DDR3 MemConstructTechBlock3,
    #if (OPTION_HW_DRAM_INIT == TRUE)
      extern MEM_TECH_FEAT MemTDramInitHw;
      #define MEM_TECH_FEATURE_HW_DRAMINIT  MemTDramInitHw
    #else
      #define  MEM_TECH_FEATURE_HW_DRAMINIT MemTFeatDef
    #endif
    #if (OPTION_SW_DRAM_INIT == TRUE)
      #define MEM_TECH_FEATURE_SW_DRAMINIT  MemTDramInitSw3
    #else
      #define MEM_TECH_FEATURE_SW_DRAMINIT  MemTFeatDef
    #endif
  #else
    #define MEM_TECH_CONSTRUCTOR_DDR3
    #define MEM_TECH_FEATURE_SW_DRAMINIT  MemTFeatDef
  #endif

  #if OPTION_DDR4 == TRUE
    extern MEM_TECH_CONSTRUCTOR MemConstructTechBlock4;
    #define MEM_TECH_CONSTRUCTOR_DDR4 MemConstructTechBlock4,
    #if (OPTION_HW_DRAM_INIT == TRUE)
      #define  MEM_TECH_FEATURE_HW_DRAMINIT MemTFeatDef
    #endif
    #if (OPTION_SW_DRAM_INIT == TRUE)
      #define MEM_TECH_FEATURE_SW_DRAMINIT  MemTFeatDef
    #endif
  #else
    #define MEM_TECH_CONSTRUCTOR_DDR4
  #endif

  /*---------------------------------------------------------------------------------------------------
   * FEATURE BLOCKS
   *
   *  This section instantiates a feature block structure for each memory controller installed
   *  by the platform solution install file.
   *---------------------------------------------------------------------------------------------------
   */

  #if (OPTION_HW_DQS_REC_EN_TRAINING == TRUE)
    extern OPTION_MEM_FEATURE_NB MemNInitDqsTrainRcvrEnHwNb;
  #endif
  extern OPTION_MEM_FEATURE_NB MemFStandardTraining;

  /*---------------------------------------------------------------------------------------------------
   * CARRIZO FEATURE BLOCK
   *---------------------------------------------------------------------------------------------------
   */
  #if (OPTION_MEMCTLR_CZ == TRUE)
    /*-------------
     * DDR3 FEATURES
     *--------------
    */
    #if OPTION_DDR3
      #undef MEM_MAIN_FEATURE_LVDDR3
      extern OPTION_MEM_FEATURE_MAIN MemMLvDdr3PerformanceEnhPre;
      #define MEM_MAIN_FEATURE_LVDDR3 MemMLvDdr3PerformanceEnhPre
    #else
      #undef MEM_TECH_CONSTRUCTOR_DDR3
      #define MEM_TECH_CONSTRUCTOR_DDR3  (MEM_TECH_CONSTRUCTOR *) MemTFeatDef,
    #endif
    /*--------------
     * DDR4 FEATURES
     *--------------
    */
    #if OPTION_DDR4
      #undef MEM_MAIN_FEATURE_LVDDR4
      //extern OPTION_MEM_FEATURE_MAIN MemMLvDdr4PerformanceEnhPre;
      //#define MEM_MAIN_FEATURE_LVDDR4 MemMLvDdr4PerformanceEnhPre
      #define MEM_MAIN_FEATURE_LVDDR4 MemMDefRet
    #else
      #undef MEM_TECH_CONSTRUCTOR_DDR4
      #define MEM_TECH_CONSTRUCTOR_DDR4  (MEM_TECH_CONSTRUCTOR *) MemTFeatDef,
      #undef MEM_MAIN_FEATURE_LVDDR4
      #define MEM_MAIN_FEATURE_LVDDR4 MemMDefRet
    #endif

    #undef MEM_LOAD_PMU_FIRMWARE
    extern OPTION_MEM_FEATURE_NB MemNLoadPmuFirmwareCZ;
    #define MEM_LOAD_PMU_FIRMWARE MemNLoadPmuFirmwareCZ

    #undef MEM_TECH_FEATURE_DRAMINIT
    #define MEM_TECH_FEATURE_DRAMINIT   MemTFeatDef

    #if (OPTION_EARLY_SAMPLES == TRUE)
      extern OPTION_MEM_FEATURE_NB MemNInitEarlySampleSupportCZ;
      #undef MEM_EARLY_SAMPLE_SUPPORT
      #define MEM_EARLY_SAMPLE_SUPPORT    MemNInitEarlySampleSupportCZ
    #else
      #define MEM_EARLY_SAMPLE_SUPPORT    MemFDefRet
    #endif

    #if (OPTION_DCT_INTERLEAVE == TRUE)
      extern OPTION_MEM_FEATURE_NB MemFInterleaveMultiChannels;
      #undef  MEM_FEATURE_CHANNEL_INTERLEAVE
      #define MEM_FEATURE_CHANNEL_INTERLEAVE MemFInterleaveMultiChannels
    #endif

    #undef  MEM_FEATURE_REGION_INTERLEAVE
    #define MEM_FEATURE_REGION_INTERLEAVE MemFDefRet

    #undef MEM_FEATURE_TRAINING
    #define MEM_FEATURE_TRAINING    MemFDefRet
    #undef MEM_TECH_FEATURE_CPG
    #define MEM_TECH_FEATURE_CPG    MemFDefRet
    #undef MEM_TECH_FEATURE_HWRXEN
    #define MEM_TECH_FEATURE_HWRXEN    MemFDefRet

    MEM_FEAT_BLOCK_NB  MemFeatBlockCZ = {
      MEM_FEAT_BLOCK_NB_STRUCT_VERSION,
      MEM_FEATURE_ONLINE_SPARE,
      MEM_FEATURE_BANK_INTERLEAVE,
      MEM_FEATURE_UNDO_BANK_INTERLEAVE,
      MEM_FEATURE_NODE_INTERLEAVE_CHECK,
      MEM_FEATURE_NODE_INTERLEAVE,
      MEM_FEATURE_CHANNEL_INTERLEAVE,
      MEM_FEATURE_REGION_INTERLEAVE,
      MEM_FEATURE_CK_ECC,
      MEM_FEATURE_ECC,
      MEM_FEATURE_TRAINING,
      MEM_FEATURE_LVDDR3,
      MEM_FEATURE_ONDIMMTHERMAL,
      MEM_TECH_FEATURE_DRAMINIT,
      MEM_FEATURE_DIMM_EXCLUDE,
      MEM_EARLY_SAMPLE_SUPPORT,
      MEM_TECH_FEATURE_CPG,
      MEM_TECH_FEATURE_HWRXEN,
      MEM_FEATURE_AMP,
      MemFDefRet,
      MemFDefRet,
      MemFDefRet,
      MemFDefRet,
      MEM_LOAD_PMU_FIRMWARE,
      MemFDefRet // MEM_FEATURE_LVDDR4
    };

    #undef MEM_NB_SUPPORT_CZ
    extern MEM_NB_CONSTRUCTOR MemConstructNBBlockCZ;
    extern MEM_INITIALIZER MemNInitDefaultsCZ;
    #define MEM_NB_SUPPORT_CZ { MEM_NB_SUPPORT_STRUCT_VERSION, MemConstructNBBlockCZ, MemNInitDefaultsCZ, &MemFeatBlockCZ, MEM_FEATURE_S3_RESUME_CONSTRUCTOR_CZ, MEM_IDENDIMM_CZ, MEM_TRANS_SYS_ADDR_TO_CS_CZ },
  #endif // OPTION_MEMCTRL_CZ

  #if (OPTION_MEMCTLR_ST == TRUE)
    /*-------------
     * DDR3 FEATURES
     *--------------
    */
    #if OPTION_DDR3
      #undef MEM_MAIN_FEATURE_LVDDR3
      extern OPTION_MEM_FEATURE_MAIN MemMLvDdr3PerformanceEnhPre;
      #define MEM_MAIN_FEATURE_LVDDR3 MemMLvDdr3PerformanceEnhPre
    #else
      #undef MEM_TECH_CONSTRUCTOR_DDR3
      #define MEM_TECH_CONSTRUCTOR_DDR3  (MEM_TECH_CONSTRUCTOR *) MemTFeatDef,
    #endif
    /*--------------
     * DDR4 FEATURES
     *--------------
    */
    #if OPTION_DDR4
      #undef MEM_MAIN_FEATURE_LVDDR4
      //extern OPTION_MEM_FEATURE_MAIN MemMLvDdr4PerformanceEnhPre;
      //#define MEM_MAIN_FEATURE_LVDDR4 MemMLvDdr4PerformanceEnhPre
      #define MEM_MAIN_FEATURE_LVDDR4 MemMDefRet
    #else
      #undef MEM_TECH_CONSTRUCTOR_DDR4
      #define MEM_TECH_CONSTRUCTOR_DDR4  (MEM_TECH_CONSTRUCTOR *) MemTFeatDef,
      #undef MEM_MAIN_FEATURE_LVDDR4
      #define MEM_MAIN_FEATURE_LVDDR4 MemMDefRet
    #endif

    #undef MEM_LOAD_PMU_FIRMWARE
    extern OPTION_MEM_FEATURE_NB MemNLoadPmuFirmwareST;
    #define MEM_LOAD_PMU_FIRMWARE MemNLoadPmuFirmwareST

    #undef MEM_TECH_FEATURE_DRAMINIT
    #define MEM_TECH_FEATURE_DRAMINIT   MemTFeatDef

    #if (OPTION_EARLY_SAMPLES == TRUE)
      extern OPTION_MEM_FEATURE_NB MemNInitEarlySampleSupportST;
      #undef MEM_EARLY_SAMPLE_SUPPORT
      #define MEM_EARLY_SAMPLE_SUPPORT    MemNInitEarlySampleSupportST
    #else
      #define MEM_EARLY_SAMPLE_SUPPORT    MemFDefRet
    #endif

    #if (OPTION_DCT_INTERLEAVE == TRUE)
      extern OPTION_MEM_FEATURE_NB MemFInterleaveMultiChannels;
      #undef  MEM_FEATURE_CHANNEL_INTERLEAVE
      #define MEM_FEATURE_CHANNEL_INTERLEAVE MemFInterleaveMultiChannels
    #endif

    #undef  MEM_FEATURE_REGION_INTERLEAVE
    #define MEM_FEATURE_REGION_INTERLEAVE MemFDefRet

    #undef MEM_FEATURE_TRAINING
    #define MEM_FEATURE_TRAINING    MemFDefRet
    #undef MEM_TECH_FEATURE_CPG
    #define MEM_TECH_FEATURE_CPG    MemFDefRet
    #undef MEM_TECH_FEATURE_HWRXEN
    #define MEM_TECH_FEATURE_HWRXEN    MemFDefRet

    MEM_FEAT_BLOCK_NB  MemFeatBlockST = {
      MEM_FEAT_BLOCK_NB_STRUCT_VERSION,
      MEM_FEATURE_ONLINE_SPARE,
      MEM_FEATURE_BANK_INTERLEAVE,
      MEM_FEATURE_UNDO_BANK_INTERLEAVE,
      MEM_FEATURE_NODE_INTERLEAVE_CHECK,
      MEM_FEATURE_NODE_INTERLEAVE,
      MEM_FEATURE_CHANNEL_INTERLEAVE,
      MEM_FEATURE_REGION_INTERLEAVE,
      MEM_FEATURE_CK_ECC,
      MEM_FEATURE_ECC,
      MEM_FEATURE_TRAINING,
      MEM_FEATURE_LVDDR3,
      MEM_FEATURE_ONDIMMTHERMAL,
      MEM_TECH_FEATURE_DRAMINIT,
      MEM_FEATURE_DIMM_EXCLUDE,
      MEM_EARLY_SAMPLE_SUPPORT,
      MEM_TECH_FEATURE_CPG,
      MEM_TECH_FEATURE_HWRXEN,
      MEM_FEATURE_AMP,
      MemFDefRet,
      MemFDefRet,
      MemFDefRet,
      MemFDefRet,
      MEM_LOAD_PMU_FIRMWARE,
      MemFDefRet // MEM_FEATURE_LVDDR4
    };

    #undef MEM_NB_SUPPORT_ST
    extern MEM_NB_CONSTRUCTOR MemConstructNBBlockST;
    extern MEM_INITIALIZER MemNInitDefaultsST;
    #define MEM_NB_SUPPORT_ST { MEM_NB_SUPPORT_STRUCT_VERSION, MemConstructNBBlockST, MemNInitDefaultsST, &MemFeatBlockST, MEM_FEATURE_S3_RESUME_CONSTRUCTOR_ST, MEM_IDENDIMM_ST, MEM_TRANS_SYS_ADDR_TO_CS_ST },
  #endif // OPTION_MEMCTRL_ST

  /*---------------------------------------------------------------------------------------------------
   * MAIN FEATURE BLOCK
   *---------------------------------------------------------------------------------------------------
   */
  MEM_FEAT_BLOCK_MAIN MemFeatMain = {
    MEM_FEAT_BLOCK_MAIN_STRUCT_VERSION,
    MEM_MAIN_FEATURE_TRAINING,
    MEM_MAIN_FEATURE_DIMM_EXCLUDE,
    MEM_MAIN_FEATURE_ONLINE_SPARE,
    MEM_MAIN_FEATURE_NODE_INTERLEAVE,
    MEM_MAIN_FEATURE_ECC,
    MEM_MAIN_FEATURE_MEM_CLEAR,
    MEM_MAIN_FEATURE_MEM_DMI,
    MEM_MAIN_FEATURE_MEM_CRAT,
    MEM_MAIN_FEATURE_LVDDR3,
    MEM_MAIN_FEATURE_UMAALLOC,
    MEM_MAIN_FEATURE_MEM_SAVE,
    MEM_MAIN_FEATURE_MEM_RESTORE,
    MEM_MAIN_FEATURE_MEM_S3_SAVE,
    MEM_MAIN_FEATURE_AGGRESSOR,
    MEM_MAIN_FEATURE_LVDDR4
  };


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

  #if OPTION_MEMCTLR_CZ
    #define NB_TRAIN_FLOW_DDR2    (BOOLEAN (*) (MEM_NB_BLOCK*)) memDefTrue
    #ifndef NB_TRAIN_FLOW_DDR3
      #undef NB_TRAIN_FLOW_DDR3
      #define NB_TRAIN_FLOW_DDR3    (BOOLEAN (*) (MEM_NB_BLOCK*)) memDefTrue
    #endif
    #undef MEM_TECH_CONSTRUCTOR_DDR2
    #define MEM_TECH_CONSTRUCTOR_DDR2
  #endif

  #if OPTION_MEMCTLR_ST
    #define NB_TRAIN_FLOW_DDR2    (BOOLEAN (*) (MEM_NB_BLOCK*)) memDefTrue
    #ifndef NB_TRAIN_FLOW_DDR3
      #undef NB_TRAIN_FLOW_DDR3
      #define NB_TRAIN_FLOW_DDR3    (BOOLEAN (*) (MEM_NB_BLOCK*)) memDefTrue
    #endif
    #undef MEM_TECH_CONSTRUCTOR_DDR2
    #define MEM_TECH_CONSTRUCTOR_DDR2
  #endif

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
  #if OPTION_MEMCTLR_CZ
    #if OPTION_DDR3
      #if OPTION_UDIMMS
        #if OPTION_FP4_SOCKET_SUPPORT
          extern PSC_TBL_ENTRY CZMaxFreqTblEntUFP4D3;
          #define PSC_TBL_CZ_UDIMM3_MAX_FREQ_FP4  &CZMaxFreqTblEntUFP4D3,
        #else
          #define PSC_TBL_CZ_UDIMM3_MAX_FREQ_FP4
        #endif
        #if OPTION_AM4_SOCKET_SUPPORT
          extern PSC_TBL_ENTRY CZMaxFreqTblEntUAM4D3;
          #define PSC_TBL_CZ_UDIMM3_MAX_FREQ_AM4  &CZMaxFreqTblEntUAM4D3,
        #else
          #define PSC_TBL_CZ_UDIMM3_MAX_FREQ_AM4
        #endif
        extern PSC_TBL_ENTRY CZCadBusTblEnU3;
        #define PSC_TBL_CZ_UDIMM3_CAD_BUS  &CZCadBusTblEnU3,
        extern PSC_TBL_ENTRY CZDataBusTblEnU3;
        #define PSC_TBL_CZ_UDIMM3_DATA_BUS  &CZDataBusTblEnU3,
      #else
        #define PSC_TBL_CZ_UDIMM3_CAD_BUS
        #define PSC_TBL_CZ_UDIMM3_DATA_BUS
        #define PSC_TBL_CZ_UDIMM3_MAX_FREQ_FP4
        #define PSC_TBL_CZ_UDIMM3_MAX_FREQ_AM4
      #endif
      #if OPTION_SODIMMS
        #if OPTION_FP4_SOCKET_SUPPORT
          extern PSC_TBL_ENTRY CZMaxFreqTblEntSOFP4D3;
          #define PSC_TBL_CZ_SODIMM3_MAX_FREQ_FP4  &CZMaxFreqTblEntSOFP4D3,
        #else
          #define PSC_TBL_CZ_SODIMM3_MAX_FREQ_FP4
        #endif
        extern PSC_TBL_ENTRY CZCadBusTblEnSO3;
        #define PSC_TBL_CZ_SODIMM3_CAD_BUS  &CZCadBusTblEnSO3,
        extern PSC_TBL_ENTRY CZDataBusTblEnSO3;
        #define PSC_TBL_CZ_SODIMM3_DATA_BUS  &CZDataBusTblEnSO3,
      #else
        #define PSC_TBL_CZ_SODIMM3_CAD_BUS
        #define PSC_TBL_CZ_SODIMM3_DATA_BUS
        #define PSC_TBL_CZ_SODIMM3_MAX_FREQ_FP4
      #endif
    #else
      #define PSC_TBL_CZ_UDIMM3_CAD_BUS
      #define PSC_TBL_CZ_UDIMM3_DATA_BUS
      #define PSC_TBL_CZ_UDIMM3_MAX_FREQ_FP4
      #define PSC_TBL_CZ_UDIMM3_MAX_FREQ_AM4
      #define PSC_TBL_CZ_SODIMM3_CAD_BUS
      #define PSC_TBL_CZ_SODIMM3_DATA_BUS
      #define PSC_TBL_CZ_SODIMM3_MAX_FREQ_FP4
    #endif
    #if OPTION_DDR4
      #if OPTION_UDIMMS
        #if OPTION_FP4_SOCKET_SUPPORT
          extern PSC_TBL_ENTRY CZMaxFreqTblEntUFP4D4;
          #define PSC_TBL_CZ_UDIMM4_MAX_FREQ_FP4  &CZMaxFreqTblEntUFP4D4,
        #else
          #define PSC_TBL_CZ_UDIMM4_MAX_FREQ_FP4
        #endif
        #if OPTION_AM4_SOCKET_SUPPORT
          extern PSC_TBL_ENTRY CZMaxFreqTblEntUAM4D4;
          #define PSC_TBL_CZ_UDIMM4_MAX_FREQ_AM4 &CZMaxFreqTblEntUAM4D4,
        #else
          #define PSC_TBL_CZ_UDIMM4_MAX_FREQ_AM4
        #endif
        extern PSC_TBL_ENTRY CZCadBusTblEnU4;
        #define PSC_TBL_CZ_UDIMM4_CAD_BUS  &CZCadBusTblEnU4,
        extern PSC_TBL_ENTRY CZDataBusTblEnU4_A0;
        #define PSC_TBL_CZ_UDIMM4_DATA_BUS_A0  &CZDataBusTblEnU4_A0,
        extern PSC_TBL_ENTRY CZDataBusTblEnU4;
        #define PSC_TBL_CZ_UDIMM4_DATA_BUS  &CZDataBusTblEnU4,
      #else
        #define PSC_TBL_CZ_UDIMM4_CAD_BUS
        #define PSC_TBL_CZ_UDIMM4_DATA_BUS_A0
        #define PSC_TBL_CZ_UDIMM4_DATA_BUS
        #define PSC_TBL_CZ_UDIMM4_MAX_FREQ_FP4
        #define PSC_TBL_CZ_UDIMM4_MAX_FREQ_AM4
      #endif
      #if OPTION_SODIMMS
        #if OPTION_FP4_SOCKET_SUPPORT
          extern PSC_TBL_ENTRY CZMaxFreqTblEntSOFP4D4;
          #define PSC_TBL_CZ_SODIMM4_MAX_FREQ_FP4  &CZMaxFreqTblEntSOFP4D4,
        #else
          #define PSC_TBL_CZ_SODIMM4_MAX_FREQ_FP4
        #endif
        extern PSC_TBL_ENTRY CZCadBusTblEnSO4;
        #define PSC_TBL_CZ_SODIMM4_CAD_BUS  &CZCadBusTblEnSO4,
        extern PSC_TBL_ENTRY CZDataBusTblEnSO4_A0;
        #define PSC_TBL_CZ_SODIMM4_DATA_BUS_A0  &CZDataBusTblEnSO4_A0,
        extern PSC_TBL_ENTRY CZDataBusTblEnSO4;
        #define PSC_TBL_CZ_SODIMM4_DATA_BUS  &CZDataBusTblEnSO4,
      #else
        #define PSC_TBL_CZ_SODIMM4_CAD_BUS
        #define PSC_TBL_CZ_SODIMM4_DATA_BUS_A0
        #define PSC_TBL_CZ_SODIMM4_DATA_BUS
        #define PSC_TBL_CZ_SODIMM4_MAX_FREQ_FP4
      #endif
    #else
      #define PSC_TBL_CZ_UDIMM4_CAD_BUS
      #define PSC_TBL_CZ_UDIMM4_DATA_BUS_A0
      #define PSC_TBL_CZ_UDIMM4_DATA_BUS
      #define PSC_TBL_CZ_UDIMM4_MAX_FREQ_FP4
      #define PSC_TBL_CZ_UDIMM4_MAX_FREQ_AM4
      #define PSC_TBL_CZ_SODIMM4_CAD_BUS
      #define PSC_TBL_CZ_SODIMM4_DATA_BUS_A0
      #define PSC_TBL_CZ_SODIMM4_DATA_BUS
      #define PSC_TBL_CZ_SODIMM4_MAX_FREQ_FP4
    #endif

    extern MEM_PSC_FLOW MemPGetMaxFreqSupported;

    #if OPTION_DDR3

      extern PSC_TBL_ENTRY CZOdtPatTblEnt3;
      extern MEM_PSC_FLOW MemPLookupDataBusCfgTabs3;

      PSC_TBL_ENTRY* memPSCTblODTPatArrayD3CZ[] = {
        &CZOdtPatTblEnt3,
        PSC_TBL_END
      };

      PSC_TBL_ENTRY* memPSCTblMaxFreqArrayD3CZ[] = {
        PSC_TBL_CZ_SODIMM3_MAX_FREQ_FP4
        PSC_TBL_CZ_UDIMM3_MAX_FREQ_FP4
        PSC_TBL_CZ_UDIMM3_MAX_FREQ_AM4
        PSC_TBL_END
      };

      PSC_TBL_ENTRY* memPSCTblCadBusArrayD3CZ[] = {
        PSC_TBL_CZ_SODIMM3_CAD_BUS
        PSC_TBL_CZ_UDIMM3_CAD_BUS
        PSC_TBL_END
      };

      PSC_TBL_ENTRY* memPSCTblDataBusArrayD3CZ[] = {
        PSC_TBL_CZ_SODIMM3_DATA_BUS
        PSC_TBL_CZ_UDIMM3_DATA_BUS
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
    #endif

    #if OPTION_DDR4

      extern PSC_TBL_ENTRY CZOdtPatTblEnt4;
      extern MEM_PSC_FLOW MemPLookupDataBusCfgTabs4;

      PSC_TBL_ENTRY* memPSCTblODTPatArrayD4CZ[] = {
        &CZOdtPatTblEnt4,
        PSC_TBL_END
      };

      PSC_TBL_ENTRY* memPSCTblMaxFreqArrayD4CZ[] = {
        PSC_TBL_CZ_SODIMM4_MAX_FREQ_FP4
        PSC_TBL_CZ_UDIMM4_MAX_FREQ_FP4
        PSC_TBL_CZ_UDIMM4_MAX_FREQ_AM4
        PSC_TBL_END
      };

      PSC_TBL_ENTRY* memPSCTblCadBusArrayD4CZ[] = {
        PSC_TBL_CZ_SODIMM4_CAD_BUS
        PSC_TBL_CZ_UDIMM4_CAD_BUS
        PSC_TBL_END
      };

      PSC_TBL_ENTRY* memPSCTblDataBusArrayD4CZ[] = {
        PSC_TBL_CZ_SODIMM4_DATA_BUS_A0
        PSC_TBL_CZ_SODIMM4_DATA_BUS
        PSC_TBL_CZ_UDIMM4_DATA_BUS_A0
        PSC_TBL_CZ_UDIMM4_DATA_BUS
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
    #endif
  #endif

  #define MEM_PSC_FLOW_BLOCK_D3_ST
  #define MEM_PSC_FLOW_BLOCK_D4_ST
  #if OPTION_MEMCTLR_ST
    #if OPTION_DDR3
      #if OPTION_UDIMMS
        #if OPTION_FP4_SOCKET_SUPPORT
          extern PSC_TBL_ENTRY STMaxFreqTblEntUFP4D3;
          #define PSC_TBL_ST_UDIMM3_MAX_FREQ_FP4  &STMaxFreqTblEntUFP4D3,
        #else
          #define PSC_TBL_ST_UDIMM3_MAX_FREQ_FP4
        #endif
        #if OPTION_FT4_SOCKET_SUPPORT
          extern PSC_TBL_ENTRY STMaxFreqTblEntUFT4D3;
          #define PSC_TBL_ST_UDIMM3_MAX_FREQ_FT4  &STMaxFreqTblEntUFT4D3,
        #else
          #define PSC_TBL_ST_UDIMM3_MAX_FREQ_FT4
        #endif
        extern PSC_TBL_ENTRY STCadBusTblEnU3;
        #define PSC_TBL_ST_UDIMM3_CAD_BUS  &STCadBusTblEnU3,
        extern PSC_TBL_ENTRY STDataBusTblEnU3;
        #define PSC_TBL_ST_UDIMM3_DATA_BUS  &STDataBusTblEnU3,
      #else
        #define PSC_TBL_ST_UDIMM3_CAD_BUS
        #define PSC_TBL_ST_UDIMM3_DATA_BUS
        #define PSC_TBL_ST_UDIMM3_MAX_FREQ_FP4
        #define PSC_TBL_ST_UDIMM3_MAX_FREQ_FT4
      #endif
      #if OPTION_SODIMMS
        #if OPTION_FP4_SOCKET_SUPPORT
          extern PSC_TBL_ENTRY STMaxFreqTblEntSOFP4D3;
          #define PSC_TBL_ST_SODIMM3_MAX_FREQ_FP4  &STMaxFreqTblEntSOFP4D3,
        #else
          #define PSC_TBL_ST_SODIMM3_MAX_FREQ_FP4
        #endif
        #if OPTION_FT4_SOCKET_SUPPORT
          extern PSC_TBL_ENTRY STMaxFreqTblEntSOFT4D3;
          #define PSC_TBL_ST_SODIMM3_MAX_FREQ_FT4  &STMaxFreqTblEntSOFT4D3,
        #else
          #define PSC_TBL_ST_SODIMM3_MAX_FREQ_FT4
        #endif
        extern PSC_TBL_ENTRY STCadBusTblEnSO3;
        #define PSC_TBL_ST_SODIMM3_CAD_BUS  &STCadBusTblEnSO3,
        extern PSC_TBL_ENTRY STDataBusTblEnSO3;
        #define PSC_TBL_ST_SODIMM3_DATA_BUS  &STDataBusTblEnSO3,
      #else
        #define PSC_TBL_ST_SODIMM3_CAD_BUS
        #define PSC_TBL_ST_SODIMM3_DATA_BUS
        #define PSC_TBL_ST_SODIMM3_MAX_FREQ_FP4
        #define PSC_TBL_ST_SODIMM3_MAX_FREQ_FT4
      #endif
    #else
      #define PSC_TBL_ST_UDIMM3_CAD_BUS
      #define PSC_TBL_ST_UDIMM3_DATA_BUS
      #define PSC_TBL_ST_UDIMM3_MAX_FREQ_FP4
      #define PSC_TBL_ST_SODIMM3_CAD_BUS
      #define PSC_TBL_ST_SODIMM3_DATA_BUS
      #define PSC_TBL_ST_SODIMM3_MAX_FREQ_FP4
      #define PSC_TBL_ST_SODIMM3_MAX_FREQ_FT4
    #endif
    #if OPTION_DDR4
      #if OPTION_UDIMMS
        #if OPTION_FP4_SOCKET_SUPPORT
          extern PSC_TBL_ENTRY STMaxFreqTblEntUFP4D4;
          #define PSC_TBL_ST_UDIMM4_MAX_FREQ_FP4  &STMaxFreqTblEntUFP4D4,
        #else
          #define PSC_TBL_ST_UDIMM4_MAX_FREQ_FP4
        #endif
        #if OPTION_FT4_SOCKET_SUPPORT
          extern PSC_TBL_ENTRY STMaxFreqTblEntUFT4D4;
          #define PSC_TBL_ST_UDIMM4_MAX_FREQ_FT4  &STMaxFreqTblEntUFT4D4,
        #else
          #define PSC_TBL_ST_UDIMM4_MAX_FREQ_FT4
        #endif
        extern PSC_TBL_ENTRY STCadBusTblEnU4;
        #define PSC_TBL_ST_UDIMM4_CAD_BUS  &STCadBusTblEnU4,
        extern PSC_TBL_ENTRY STDataBusTblEnU4_A0;
        #define PSC_TBL_ST_UDIMM4_DATA_BUS_A0  &STDataBusTblEnU4_A0,
        extern PSC_TBL_ENTRY STDataBusTblEnU4;
        #define PSC_TBL_ST_UDIMM4_DATA_BUS  &STDataBusTblEnU4,
      #else
        #define PSC_TBL_ST_UDIMM4_CAD_BUS
        #define PSC_TBL_ST_UDIMM4_DATA_BUS_A0
        #define PSC_TBL_ST_UDIMM4_DATA_BUS
        #define PSC_TBL_ST_UDIMM4_MAX_FREQ_FP4
        #define PSC_TBL_ST_UDIMM4_MAX_FREQ_FT4
      #endif
      #if OPTION_SODIMMS
        #if OPTION_FP4_SOCKET_SUPPORT
          extern PSC_TBL_ENTRY STMaxFreqTblEntSOFP4D4;
          #define PSC_TBL_ST_SODIMM4_MAX_FREQ_FP4  &STMaxFreqTblEntSOFP4D4,
        #else
          #define PSC_TBL_ST_SODIMM4_MAX_FREQ_FP4
        #endif
        #if OPTION_FT4_SOCKET_SUPPORT
          extern PSC_TBL_ENTRY STMaxFreqTblEntSOFT4D4;
          #define PSC_TBL_ST_SODIMM4_MAX_FREQ_FT4  &STMaxFreqTblEntSOFT4D4,
        #else
          #define PSC_TBL_ST_SODIMM4_MAX_FREQ_FT4
        #endif
        extern PSC_TBL_ENTRY STCadBusTblEnSO4;
        #define PSC_TBL_ST_SODIMM4_CAD_BUS  &STCadBusTblEnSO4,
        extern PSC_TBL_ENTRY STDataBusTblEnSO4_A0;
        #define PSC_TBL_ST_SODIMM4_DATA_BUS_A0  &STDataBusTblEnSO4_A0,
        extern PSC_TBL_ENTRY STDataBusTblEnSO4;
        #define PSC_TBL_ST_SODIMM4_DATA_BUS  &STDataBusTblEnSO4,
      #else
        #define PSC_TBL_ST_SODIMM4_CAD_BUS
        #define PSC_TBL_ST_SODIMM4_DATA_BUS_A0
        #define PSC_TBL_ST_SODIMM4_DATA_BUS
        #define PSC_TBL_ST_SODIMM4_MAX_FREQ_FP4
        #define PSC_TBL_ST_SODIMM4_MAX_FREQ_FT4
      #endif
    #else
      #define PSC_TBL_ST_UDIMM4_CAD_BUS
      #define PSC_TBL_ST_UDIMM4_DATA_BUS_A0
      #define PSC_TBL_ST_UDIMM4_DATA_BUS
      #define PSC_TBL_ST_UDIMM4_MAX_FREQ_FP4
      #define PSC_TBL_ST_UDIMM4_MAX_FREQ_FT4
      #define PSC_TBL_ST_SODIMM4_CAD_BUS
      #define PSC_TBL_ST_SODIMM4_DATA_BUS_A0
      #define PSC_TBL_ST_SODIMM4_DATA_BUS
      #define PSC_TBL_ST_SODIMM4_MAX_FREQ_FP4
      #define PSC_TBL_ST_SODIMM4_MAX_FREQ_FT4
    #endif

    extern MEM_PSC_FLOW MemPGetMaxFreqSupported;

    #if OPTION_DDR3

      extern PSC_TBL_ENTRY STOdtPatTblEnt3;
      extern MEM_PSC_FLOW MemPLookupDataBusCfgTabs3;

      PSC_TBL_ENTRY* memPSCTblODTPatArrayD3ST[] = {
        &STOdtPatTblEnt3,
        PSC_TBL_END
      };

      PSC_TBL_ENTRY* memPSCTblMaxFreqArrayD3ST[] = {
        PSC_TBL_ST_SODIMM3_MAX_FREQ_FP4
        PSC_TBL_ST_SODIMM3_MAX_FREQ_FT4
        PSC_TBL_ST_UDIMM3_MAX_FREQ_FP4
        PSC_TBL_ST_UDIMM3_MAX_FREQ_FT4
        PSC_TBL_END
      };

      PSC_TBL_ENTRY* memPSCTblCadBusArrayD3ST[] = {
        PSC_TBL_ST_SODIMM3_CAD_BUS
        PSC_TBL_ST_UDIMM3_CAD_BUS
        PSC_TBL_END
      };

      PSC_TBL_ENTRY* memPSCTblDataBusArrayD3ST[] = {
        PSC_TBL_ST_SODIMM3_DATA_BUS
        PSC_TBL_ST_UDIMM3_DATA_BUS
        PSC_TBL_END
      };

      MEM_PSC_TABLE_BLOCK memPSCTblBlockD3ST = {
        (PSC_TBL_ENTRY **)&memPSCTblMaxFreqArrayD3ST,
        (PSC_TBL_ENTRY **)&memPSCTblDataBusArrayD3ST,
        (PSC_TBL_ENTRY **)&memPSCTblODTPatArrayD3ST,
        (PSC_TBL_ENTRY **)&memPSCTblCadBusArrayD3ST,
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

      MEM_PSC_FLOW_BLOCK memPlatSpecFlowD3ST = {
        &memPSCTblBlockD3ST,
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
      #undef MEM_PSC_FLOW_BLOCK_D3_ST
      #define MEM_PSC_FLOW_BLOCK_D3_ST &memPlatSpecFlowD3ST,
    #endif

    #if OPTION_DDR4

      extern PSC_TBL_ENTRY STOdtPatTblEnt4;
      extern MEM_PSC_FLOW MemPLookupDataBusCfgTabs4;

      PSC_TBL_ENTRY* memPSCTblODTPatArrayD4ST[] = {
        &STOdtPatTblEnt4,
        PSC_TBL_END
      };

      PSC_TBL_ENTRY* memPSCTblMaxFreqArrayD4ST[] = {
        PSC_TBL_ST_SODIMM4_MAX_FREQ_FP4
        PSC_TBL_ST_SODIMM4_MAX_FREQ_FT4
        PSC_TBL_ST_UDIMM4_MAX_FREQ_FP4
        PSC_TBL_ST_UDIMM4_MAX_FREQ_FT4
        PSC_TBL_END
      };

      PSC_TBL_ENTRY* memPSCTblCadBusArrayD4ST[] = {
        PSC_TBL_ST_SODIMM4_CAD_BUS
        PSC_TBL_ST_UDIMM4_CAD_BUS
        PSC_TBL_END
      };

      PSC_TBL_ENTRY* memPSCTblDataBusArrayD4ST[] = {
        PSC_TBL_ST_SODIMM4_DATA_BUS_A0
        PSC_TBL_ST_SODIMM4_DATA_BUS
        PSC_TBL_ST_UDIMM4_DATA_BUS_A0
        PSC_TBL_ST_UDIMM4_DATA_BUS
        PSC_TBL_END
      };

      MEM_PSC_TABLE_BLOCK memPSCTblBlockD4ST = {
        (PSC_TBL_ENTRY **)&memPSCTblMaxFreqArrayD4ST,
        (PSC_TBL_ENTRY **)&memPSCTblDataBusArrayD4ST,
        (PSC_TBL_ENTRY **)&memPSCTblODTPatArrayD4ST,
        (PSC_TBL_ENTRY **)&memPSCTblCadBusArrayD4ST,
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

      MEM_PSC_FLOW_BLOCK memPlatSpecFlowD4ST = {
        &memPSCTblBlockD4ST,
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
      #undef MEM_PSC_FLOW_BLOCK_D4_ST
      #define MEM_PSC_FLOW_BLOCK_D4_ST &memPlatSpecFlowD4ST,
    #endif
  #endif

  MEM_PSC_FLOW_BLOCK* memPlatSpecFlowArray[] = {
    MEM_PSC_FLOW_BLOCK_D3_CZ
    MEM_PSC_FLOW_BLOCK_D4_CZ
    MEM_PSC_FLOW_BLOCK_D3_ST
    MEM_PSC_FLOW_BLOCK_D4_ST
    MEM_PSC_FLOW_BLOCK_END
  };

  /*---------------------------------------------------------------------------------------------------
  *
  *  LRDIMM CONTROL
  *
  *---------------------------------------------------------------------------------------------------
  */
  #if (OPTION_LRDIMMS == TRUE)
    #define MEM_TECH_FEATURE_LRDIMM_INIT    MemTFeatDef
  #else //#if (OPTION_LRDIMMS == FALSE)
    #define MEM_TECH_FEATURE_LRDIMM_INIT    MemTFeatDef
  #endif
  MEM_TECH_LRDIMM memLrdimmSupported = {
    MEM_TECH_LRDIMM_STRUCT_VERSION,
    MEM_TECH_FEATURE_LRDIMM_INIT
  };
#else
  /*---------------------------------------------------------------------------------------------------
   * MAIN FLOW CONTROL
   *
   *
   *---------------------------------------------------------------------------------------------------
   */
  MEM_FLOW_CFG* memFlowControlInstalled[] = {
    NULL
  };
  /*---------------------------------------------------------------------------------------------------
   * NB TRAINING FLOW CONTROL
   *
   *
   *---------------------------------------------------------------------------------------------------
   */
  OPTION_MEM_FEATURE_NB* memNTrainFlowControl[] = {    // Training flow control
    NULL
  };
  /*---------------------------------------------------------------------------------------------------
   * DEFAULT TECHNOLOGY BLOCK
   *
   *
   *---------------------------------------------------------------------------------------------------
   */
  MEM_TECH_CONSTRUCTOR* memTechInstalled[] = {    // Types of technology installed
    NULL
  };

  /*---------------------------------------------------------------------------------------------------
   * DEFAULT TECHNOLOGY MAP
   *
   *
   *---------------------------------------------------------------------------------------------------
   */
  UINT8 MemoryTechnologyMap[MAX_SOCKETS_SUPPORTED] = {0};

  /*---------------------------------------------------------------------------------------------------
   * DEFAULT MAIN FEATURE BLOCK
   *---------------------------------------------------------------------------------------------------
   */
  MEM_FEAT_BLOCK_MAIN MemFeatMain = {
    NULL
  };

  /*---------------------------------------------------------------------------------------------------
   * DEFAULT NORTHBRIDGE SUPPORT LIST
   *
   *
   *---------------------------------------------------------------------------------------------------
   */
  #if (OPTION_MEMCTLR_CZ == TRUE)
    #undef MEM_NB_SUPPORT_CZ
    #define MEM_NB_SUPPORT_CZ { MEM_NB_SUPPORT_STRUCT_VERSION, NULL, NULL, NULL, MEM_FEATURE_S3_RESUME_CONSTRUCTOR_CZ, MEM_IDENDIMM_CZ, MEM_TRANS_SYS_ADDR_TO_CS_CZ },
  #endif
  #if (OPTION_MEMCTLR_ST == TRUE)
    #undef MEM_NB_SUPPORT_ST
    #define MEM_NB_SUPPORT_ST { MEM_NB_SUPPORT_STRUCT_VERSION, NULL, NULL, NULL, MEM_FEATURE_S3_RESUME_CONSTRUCTOR_ST, MEM_IDENDIMM_ST, MEM_TRANS_SYS_ADDR_TO_CS_ST },
  #endif
  /*---------------------------------------------------------------------------------------------------
   * DEFAULT Technology Training
   *
   *
   *---------------------------------------------------------------------------------------------------
   */
  #if OPTION_DDR2
    MEM_TECH_FEAT_BLOCK  memTechTrainingFeatDDR2 = {
      NULL
    };
    MEM_FEAT_TRAIN_SEQ memTrainSequenceDDR2[] = {
      NULL
    };
  #endif
  #if OPTION_DDR3
    MEM_TECH_FEAT_BLOCK  memTechTrainingFeatDDR3 = {
      NULL
    };
    MEM_FEAT_TRAIN_SEQ memTrainSequenceDDR3[] = {
      NULL
    };
  #endif
    /*---------------------------------------------------------------------------------------------------
     * DEFAULT Platform Specific list
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

  /*----------------------------------------------------------------------
   * EXTRACTABLE PLATFORM SPECIFIC CONFIGURATION
   *
   *----------------------------------------------------------------------
   */
  MEM_PSC_FLOW_BLOCK* memPlatSpecFlowArray[] = {
    NULL
  };

  MEM_TECH_LRDIMM memLrdimmSupported = {
    MEM_TECH_LRDIMM_STRUCT_VERSION,
    NULL
  };
#endif

/*---------------------------------------------------------------------------------------------------
 * NORTHBRIDGE SUPPORT LIST
 *
 *
 *---------------------------------------------------------------------------------------------------
 */
MEM_NB_SUPPORT memNBInstalled[] = {
  MEM_NB_SUPPORT_CZ
  MEM_NB_SUPPORT_ST
  MEM_NB_SUPPORT_END
};

UINT8 SizeOfNBInstalledTable = sizeof (memNBInstalled) / sizeof (memNBInstalled[0]);


#endif  // _OPTION_MEMORY_INSTALL_H_

