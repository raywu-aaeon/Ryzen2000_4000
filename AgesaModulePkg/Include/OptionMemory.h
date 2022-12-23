/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD Memory option API.
 *
 * Contains structures and values used to control the Memory option code.
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  OPTION
 * @e \$Revision: 311790 $   @e \$Date: 2015-01-27 13:03:49 +0800 (Tue, 27 Jan 2015) $
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

#ifndef _OPTION_MEMORY_H_
#define _OPTION_MEMORY_H_

/* Memory Includes */
#include "mm.h"
#include "mn.h"
#include "mt.h"
#include "ma.h"
#include "mp.h"
/*----------------------------------------------------------------------------------------
 *          M I X E D   (Definitions And Macros / Typedefs, Structures, Enums)
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                 D E F I N I T I O N S     A N D     M A C R O S
 *----------------------------------------------------------------------------------------
 */

#define MAX_FF_TYPES      6   ///< Maximum number of DDR Form factors (UDIMMs, RDIMMMs, SODIMMS) supported

/*----------------------------------------------------------------------------------------
 *               T Y P E D E F S,   S T R U C T U R E S,    E N U M S
 *----------------------------------------------------------------------------------------
 */

/*
* STANDARD MEMORY FEATURE FUNCTION POINTER
*/

typedef BOOLEAN OPTION_MEM_FEATURE_NB (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

typedef BOOLEAN MEM_TECH_FEAT (
  IN OUT   MEM_TECH_BLOCK *TechPtr
  );

typedef UINT8 MEM_TABLE_FEAT (
  IN OUT   MEM_TABLE_ALIAS **MTPtr
  );

#define MEM_FEAT_BLOCK_NB_STRUCT_VERSION  0x01

/**
 *  MEMORY FEATURE BLOCK - This structure serves as a vector table for standard
 *  memory feature implementation functions.  It contains vectors for all of the
 *  features that are supported by the various Northbridge devices supported by
 *  AGESA.
 */
typedef struct _MEM_FEAT_BLOCK_NB {
  UINT16              OptMemFeatVersion;          ///< Version of memory feature block.
  OPTION_MEM_FEATURE_NB  *OnlineSpare;            ///< Online spare support.
  OPTION_MEM_FEATURE_NB  *InterleaveBanks;        ///< Bank (Chip select) interleaving support.
  OPTION_MEM_FEATURE_NB  *UndoInterleaveBanks;    ///< Undo Bank (Chip Select) interleaving.
  OPTION_MEM_FEATURE_NB  *CheckInterleaveNodes;   ///< Check for Node interleaving support.
  OPTION_MEM_FEATURE_NB  *InterleaveNodes;        ///< Node interleaving support.
  OPTION_MEM_FEATURE_NB  *InterleaveChannels;     ///< Channel interleaving support.
  OPTION_MEM_FEATURE_NB  *InterleaveRegion;       ///< Interleave Region support.
  OPTION_MEM_FEATURE_NB  *CheckEcc;               ///< Check for ECC support.
  OPTION_MEM_FEATURE_NB  *InitEcc;                ///< ECC support.
  OPTION_MEM_FEATURE_NB  *Training;               ///< Choose the type of training (Parallel, standard or hardcoded).
  OPTION_MEM_FEATURE_NB  *LvDdr3;                 ///< Low voltage DDR3 dimm support
  OPTION_MEM_FEATURE_NB  *OnDimmThermal;          ///< On-Dimm thermal management
  MEM_TECH_FEAT          *DramInit;               ///< Choose the type of Dram init (hardware based or software based).
  OPTION_MEM_FEATURE_NB  *ExcludeDIMM;            ///< Exclude a dimm.
  OPTION_MEM_FEATURE_NB  *InitEarlySampleSupport; ///< Initialize early sample support.
  OPTION_MEM_FEATURE_NB  *InitCPG;                ///< Continuous pattern generation.
  OPTION_MEM_FEATURE_NB  *InitHwRxEn;             ///< Hardware Receiver Enable Training Initilization.
  OPTION_MEM_FEATURE_NB  *InitAMP;                ///< AMP initialization.
  OPTION_MEM_FEATURE_NB  *DataEye;                ///< Get 2D training data eye.
  OPTION_MEM_FEATURE_NB  *InitRdWr2DTraining;     ///< Initialize Read and/or Write 2D Training Feature.
  OPTION_MEM_FEATURE_NB  *InitDllPDBypass;        ///< Initialize DllPDBypass Feature.
  OPTION_MEM_FEATURE_NB  *AggressorInit;          ///< Aggressor initialization.
  OPTION_MEM_FEATURE_NB  *LoadPmuFirmware;        ///< Load PMU firmware.
  OPTION_MEM_FEATURE_NB  *LvDdr4;                 ///< Low voltage DDR4 dimm support
} MEM_FEAT_BLOCK_NB;

typedef AGESA_STATUS MEM_MAIN_FLOW_CONTROL (
  IN OUT   MEM_MAIN_DATA_BLOCK *MemMainPtr
  );

typedef BOOLEAN OPTION_MEM_FEATURE_MAIN (
  IN MEM_MAIN_DATA_BLOCK *MMPtr
  );

typedef BOOLEAN MEM_NB_CONSTRUCTOR (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN OUT   MEM_DATA_STRUCT *MemPtr,
  IN       MEM_FEAT_BLOCK_NB *FeatPtr,
  IN       MEM_SHARED_DATA *mmSharedPtr,     ///< Pointer to Memory scratchpad
  IN       UINT8 NodeID
  );

typedef BOOLEAN MEM_TECH_CONSTRUCTOR (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN OUT   MEM_NB_BLOCK   *NBPtr
  );

typedef VOID MEM_INITIALIZER (
  IN OUT   MEM_DATA_STRUCT *MemPtr
 );

typedef AGESA_STATUS MEM_PLATFORM_CFG (
  IN struct _MEM_DATA_STRUCT *MemData,
  IN UINT8 SocketID,
  IN CH_DEF_STRUCT *CurrentChannel
  );

typedef BOOLEAN MEM_IDENDIMM_CONSTRUCTOR (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN OUT   MEM_DATA_STRUCT *MemPtr,
  IN       UINT8 NodeID
  );

typedef AGESA_STATUS MEM_TRANS_SYS_ADDR_TO_CS (
  IN OUT   AMD_IDENTIFY_DIMM *AmdDimmIdentify,
  IN       MEM_MAIN_DATA_BLOCK *mmPtr
  );

typedef VOID MEM_TECH_TRAINING_FEAT (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 Pass
  );

typedef BOOLEAN MEM_RESUME_CONSTRUCTOR (
  IN OUT   VOID *S3NBPtr,
  IN OUT   MEM_DATA_STRUCT *MemPtr,
  IN       UINT8 NodeID
  );

typedef AGESA_STATUS MEM_PLAT_SPEC_CFG (
  IN struct _MEM_DATA_STRUCT *MemData,
  IN OUT   CH_DEF_STRUCT *CurrentChannel,
  IN OUT   MEM_PS_BLOCK *PsPtr
  );

typedef AGESA_STATUS MEM_FLOW_CFG (
  IN OUT   MEM_MAIN_DATA_BLOCK *MemData
  );

#define MEM_FEAT_BLOCK_MAIN_STRUCT_VERSION  0x01

/**
 * MAIN FEATURE BLOCK - This structure serves as vector table for memory features
 * that shared between all northbridge devices.
 */
typedef struct _MEM_FEAT_BLOCK_MAIN {
  UINT16              OptMemFeatVersion; ///< Version of main feature block.
  OPTION_MEM_FEATURE_MAIN *Training; ///< Training features.
  OPTION_MEM_FEATURE_MAIN *ExcludeDIMM; ///< Exclude a dimm.
  OPTION_MEM_FEATURE_MAIN *OnlineSpare; ///< On-line spare.
  OPTION_MEM_FEATURE_MAIN *InterleaveNodes; ///< Node interleave.
  OPTION_MEM_FEATURE_MAIN *InitEcc; ///< Initialize ECC on all nodes if they all support it.
  OPTION_MEM_FEATURE_MAIN *MemClr; ///< Memory Clear.
  OPTION_MEM_FEATURE_MAIN *MemDmi; ///< Memory DMI Support.
  OPTION_MEM_FEATURE_MAIN *MemCrat; ///< Memory CRAT Support.
  OPTION_MEM_FEATURE_MAIN *LvDDR3; ///< Low voltage DDR3 support.
  OPTION_MEM_FEATURE_MAIN *UmaAllocation; ///< Uma Allocation.
  OPTION_MEM_FEATURE_MAIN *MemSave; ///< Memory Context Save
  OPTION_MEM_FEATURE_MAIN *MemRestore; ///< Memory Context Restore
  OPTION_MEM_FEATURE_MAIN *MemS3Save; ///< Memory S3 Save
  OPTION_MEM_FEATURE_MAIN *AggressorDetermination; ///< Aggressor Chipselects for all DCTs on all nodes.
  OPTION_MEM_FEATURE_MAIN *LvDDR4; ///< Low voltage DDR4 support.
} MEM_FEAT_BLOCK_MAIN;

#define OPTION_MEM_INSTALL_VERSION 0x01
#define MEM_NB_SUPPORT_STRUCT_VERSION  0x01
#define MEM_TECH_FEAT_BLOCK_STRUCT_VERSION  0x01
#define MEM_TECH_TRAIN_SEQUENCE_STRUCT_VERSION  0x01
#define MEM_TECH_LRDIMM_STRUCT_VERSION 0x01
/**
 *  MEMORY TECHNOLOGY FEATURE BLOCK - This structure serves as a vector table for standard
 *  memory feature implementation functions.  It contains vectors for all of the
 *  features that are supported by the various Technology features supported by
 *  AGESA.
 */
typedef struct _MEM_TECH_FEAT_BLOCK {
  UINT16  OptMemTechFeatVersion; ///< Version of memory Tech feature block.
  MEM_TECH_FEAT *EnterHardwareTraining; ///<Enter HW WL Training
  MEM_TECH_FEAT *SwWLTraining; ///<SW Write Levelization training
  MEM_TECH_FEAT *HwBasedWLTrainingPart1; ///<HW based write levelization Training Part 1
  MEM_TECH_FEAT *HwBasedDQSReceiverEnableTrainingPart1; ///<HW based DQS receiver Enabled Training Part 1
  MEM_TECH_FEAT *HwBasedWLTrainingPart2; ///<HW based write levelization Training Part 2
  MEM_TECH_FEAT *HwBasedDQSReceiverEnableTrainingPart2; ///<HW based DQS receiver Enabled Training Part 2
  MEM_TECH_FEAT *TrainExitHwTrn; ///<Exit HW WL Training
  MEM_TECH_FEAT *NonOptimizedSWDQSRecEnTrainingPart1; ///< Non-Optimized Software based receiver Enable Training part 1
  MEM_TECH_FEAT *OptimizedSwDqsRecEnTrainingPart1; ///< Optimized Software based receiver Enable Training part 1
  MEM_TECH_FEAT *NonOptimizedSRdWrPosTraining; ///< Non-Optimized Rd Wr Position training
  MEM_TECH_FEAT *OptimizedSRdWrPosTraining; ///< Optimized Rd Wr Position training
  MEM_TECH_FEAT *MaxRdLatencyTraining; ///< MaxReadLatency Training
  MEM_TECH_FEAT *RdPosTraining; ///< HW Rx En Seed Training
  MEM_TECH_FEAT *RdDqs2DTraining; ///< 2D Rd DQS Training
} MEM_TECH_FEAT_BLOCK;

/**
 *  MEMORY TECHNOLOGY LRDIMM BLOCK - This structure serves as a vector table for standard
 *  memory feature implementation functions.  It contains vectors for all of the
 *  features that are supported by the various LRDIMM features supported by
 *  AGESA.
 */
typedef struct _MEM_TECH_LRDIMM {
  UINT16  OptMemTechLrdimmVersion; ///< Version of memory Tech feature block.
  MEM_TECH_FEAT *MemTInitializeLrdimm; ///< LRDIMM initialization
} MEM_TECH_LRDIMM;

/**
 * MEMORY NORTHBRIDGE SUPPORT STRUCT - This structure groups the Northbridge dependent
 * options together in a list to provide a single access point for all code to use
 * and to ensure that everything corresponding to the same NB type is grouped together.
 *
 * The Technology Block pointers are not included in this structure because DRAM technology
 * needs to be decoupled from the northbridge type.
 *
 */
typedef struct _MEM_NB_SUPPORT {
  UINT16              MemNBSupportVersion; ///< Version of northbridge support.
  MEM_NB_CONSTRUCTOR  *MemConstructNBBlock; ///< NorthBridge block constructor.
  MEM_INITIALIZER     *MemNInitDefaults; ///< Default value initialization for MEM_DATA_STRUCT.
  MEM_RESUME_CONSTRUCTOR *MemS3ResumeConstructNBBlock; ///< S3 memory initialization northbridge block constructor.
  MEM_IDENDIMM_CONSTRUCTOR *MemIdentifyDimmConstruct; ///< Constructor for address to dimm identification.
  MEM_TRANS_SYS_ADDR_TO_CS *MemTransSysAddrToCs; ///< Translator for system address to chip select.
} MEM_NB_SUPPORT;

/*
 *  MEMORY Non-Training FEATURES - This structure serves as a vector table for standard
 *  memory non-training feature implementation functions.  It contains vectors for all of the
 *  features that are supported by the various Technology devices supported by
 *  AGESA.
 */

/**
 * MAIN TRAINING SEQUENCE LIST - This structure serves as vector table for memory features
 * that shared between all northbridge devices.
 */
typedef struct _MEM_FEAT_TRAIN_SEQ {
  UINT16              OptMemTrainingSequenceListVersion; ///< Version of main feature block.
  OPTION_MEM_FEATURE_NB *TrainingSequence;               ///< Training Sequence function.
  OPTION_MEM_FEATURE_NB *TrainingSequenceEnabled;        ///< Enable function.
  MEM_TECH_FEAT_BLOCK      *MemTechFeatBlock;            ///< Memory feature block.
} MEM_FEAT_TRAIN_SEQ;

/**
 * PLATFORM SPECIFIC CONFIGURATION BLOCK - This structure groups various PSC table
 * entries which are used by PSC engine
 */
typedef struct _MEM_PSC_TABLE_BLOCK {
  PSC_TBL_ENTRY **TblEntryOfMaxFreq;     ///< Table entry of MaxFreq.
  PSC_TBL_ENTRY **TblEntryOfDramTerm;    ///< Table entry of Dram Term.
  PSC_TBL_ENTRY **TblEntryOfODTPattern;   ///< Table entry of ODT Pattern.
  PSC_TBL_ENTRY **TblEntryOfSAO;         ///< Table entry of Slow access mode, AddrTmg and ODC..
  PSC_TBL_ENTRY **TblEntryOfMR0WR;       ///< Table entry of MR0[WR].
  PSC_TBL_ENTRY **TblEntryOfMR0CL;       ///< Table entry of MR0[CL].
  PSC_TBL_ENTRY **TblEntryOfRC2IBT;      ///< Table entry of RC2 IBT.
  PSC_TBL_ENTRY **TblEntryOfRC10OpSpeed; ///< Table entry of RC10[operating speed].
  PSC_TBL_ENTRY **TblEntryOfLRIBT;       ///< Table entry of LRDIMM IBT
  PSC_TBL_ENTRY **TblEntryOfLRNPR;       ///< Table entry of LRDIMM F0RC13[NumPhysicalRanks].
  PSC_TBL_ENTRY **TblEntryOfLRNLR;       ///< Table entry of LRDIMM F0RC13[NumLogicalRanks].
  PSC_TBL_ENTRY **TblEntryOfGen;         ///< Table entry of CLKDis map and CKE, ODT as well as ChipSel tri-state map.
  PSC_TBL_ENTRY **TblEntryOfS2D;         ///< Table entry of 2D training configs
  PSC_TBL_ENTRY **TblEntryOfWLSeed;      ///< Table entry of WL seed
  PSC_TBL_ENTRY **TblEntryOfHWRxENSeed;  ///< Table entry of HW RxEN seed
} MEM_PSC_TABLE_BLOCK;

typedef BOOLEAN MEM_PSC_FLOW (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       MEM_PSC_TABLE_BLOCK *EntryOfTables
  );

/**
 * PLATFORM SPECIFIC CONFIGURATION FLOW BLOCK - Pointers to the sub-engines of platform
 * specific configuration.
 */
typedef struct _MEM_PSC_FLOW_BLOCK {
  MEM_PSC_TABLE_BLOCK *EntryOfTables; ///<Entry of NB specific MEM_PSC_TABLE_BLOCK
  MEM_PSC_FLOW *MaxFrequency;         ///< Sub-engine which performs "Max Frequency" value extraction.
  MEM_PSC_FLOW *DramTerm;             ///< Sub-engine which performs "Dram Term" value extraction.
  MEM_PSC_FLOW *ODTPattern;           ///< Sub-engine which performs "ODT Pattern" value extraction.
  MEM_PSC_FLOW *SAO;                  ///< Sub-engine which performs "Slow access mode, AddrTmg and ODC" value extraction.
  MEM_PSC_FLOW *MR0WrCL;              ///< Sub-engine which performs "MR0[WR] and MR0[CL]" value extraction.
  MEM_PSC_FLOW *RC2IBT;               ///< Sub-engine "RC2 IBT" value extraction.
  MEM_PSC_FLOW *RC10OpSpeed;          ///< Sub-engine "RC10[operating speed]" value extraction.
  MEM_PSC_FLOW *LRIBT;                ///< Sub-engine "LRDIMM IBT" value extraction.
  MEM_PSC_FLOW *LRNPR;                ///< Sub-engine "LRDIMM F0RC13[NumPhysicalRanks]" value extraction.
  MEM_PSC_FLOW *LRNLR;                ///< Sub-engine "LRDIMM F0RC13[NumLogicalRanks]" value extraction.
  MEM_PSC_FLOW *S2D;                  ///< Sub-engine which performs 2D training configuration  checking
  MEM_PSC_FLOW *TrainingSeedVal;      ///< Sub-engine for WL and HW RxEn pass1 seed value extraction
} MEM_PSC_FLOW_BLOCK;


/**
 * Option Memory Install sStructure
 *
 */
typedef struct _MEM_OPTION_INSTALL_STRUCT {
  UINT16                 Revision;                  ///< revision
  MEM_PLATFORM_CFG**     memPlatformTypeInstalled;  ///< Memory platform type installed
  MEM_PSC_FLOW_BLOCK**   memPlatSpecFlowArray;      ///< Memory platform specific flow array
  MEM_TECH_CONSTRUCTOR** memTechInstalled;          ///< Memory Installed Tech block
  MEM_FLOW_CFG*          memFlowControlInstalled;   ///< Memory Installed Flow Control
  MEM_NB_SUPPORT         memNBInstalled;            ///< Memory Installed NB block
  MEM_FEAT_BLOCK_MAIN    MemFeatMain;               ///< Memory feature Main.
  MEM_FEAT_BLOCK_NB      MemFeatBlock;              ///< Memory feature block.
} MEM_OPTION_INSTALL_STRUCT;

/*----------------------------------------------------------------------------------------
 *                        F U N C T I O N    P R O T O T Y P E
 *----------------------------------------------------------------------------------------
 */
/* Feature Default Return */
BOOLEAN MemFDefRet (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

BOOLEAN MemMDefRet (
  IN MEM_MAIN_DATA_BLOCK *MMPtr
  );

BOOLEAN MemMDefRetFalse (
  IN   MEM_MAIN_DATA_BLOCK *MMPtr
  );

AGESA_STATUS MemNTransSysAddrToCsRetDef (
  IN OUT   AMD_IDENTIFY_DIMM *AmdDimmIdentify,
  IN       MEM_MAIN_DATA_BLOCK *mmPtr
  );

/* Table Feature Default Return */
UINT8 MemFTableDefRet (
  IN OUT   MEM_TABLE_ALIAS **MTPtr
  );
/* S3 Feature Default Return */
BOOLEAN MemFS3DefConstructorRet (
  IN OUT   VOID *S3NBPtr,
  IN OUT   MEM_DATA_STRUCT *MemPtr,
  IN       UINT8 NodeID
  );

BOOLEAN MemNIdentifyDimmConstructorRetDef (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN OUT   MEM_DATA_STRUCT *MemPtr,
  IN       UINT8 NodeID
  );

BOOLEAN
MemProcessConditionalOverrides (
  IN       PSO_TABLE *PlatformMemoryConfiguration,
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 PsoAction,
  IN       UINT8 Dimm
   );

BOOLEAN
MemPLookupCadBusCfgTabs (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       MEM_PSC_TABLE_BLOCK *EntryOfTables
  );

BOOLEAN
MemPLookupDataBusCfgTabs3 (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       MEM_PSC_TABLE_BLOCK *EntryOfTables
  );

BOOLEAN
MemPLookupDataBusCfgTabs4 (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       MEM_PSC_TABLE_BLOCK *EntryOfTables
  );
#endif  // _OPTION_MEMORY_H_

