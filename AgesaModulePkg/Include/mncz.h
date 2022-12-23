/* $NoKeywords:$ */
/**
 * @file
 *
 * mncz.h
 *
 * Northbridge CZ
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/NB/CZ)
 * @e \$Revision: 320611 $ @e \$Date: 2015-06-12 15:21:43 +0800 (Fri, 12 Jun 2015) $
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

#ifndef _MNCZ_H_
#define _MNCZ_H_

/*----------------------------------------------------------------------------
 *   Mixed (DEFINITIONS AND MACROS / TYPEDEFS, STRUCTURES, ENUMS)
 *
 *----------------------------------------------------------------------------
 */
#define DRAM_TYPE_DDR3_CZ             0
#define DRAM_TYPE_DDR4_CZ             2

#define MAX_DCTS_PER_NODE_CZ          2
#define MAX_CHANNELS_PER_DCT_CZ       1
#define MAX_NODES_SUPPORTED_CZ        1
#define MAX_CS_PER_CHANNEL_CZ         4

#define MAX_MEMORY_PSTATE_CZ          2

#define DEFAULT_WR_ODT_CZ 6
#define DEFAULT_RD_ODT_CZ 6
#define DEFAULT_RD_ODT_TRNONDLY_CZ 0

#define PSP_SMCIND_INDEX_DATA   0xC00C002Cul
#define PSP_STATUS_CCP_CYPH_DIS_BIT_POS  0x00000010ul
#define PSP_STATUS_CCP_CYPH_DIS_MASK  0x00000010ul
#define PCI_CONFIG_SMU_INDIRECT_INDEX   0xB8          ///<  Gnb Offset index for SMU mbox
#define PCI_CONFIG_SMU_INDIRECT_DATA    0xBC          ///<  Gnb Offset data for SMU mbox

#define SMU_CC_PSP_FUSES_STATUS                   0xC0018000ul //0xC0018000ul    ///< offset in GNB to find PSP fusing
#define PSP_FUSES_PROTO                           0x4           ///< BIT2
#define PSP_FUSES_PLATFORM_SECURE_BOOT_EN         0x10          ///< BIT4

#define PSP_ALIGN_TO_4_BYTES
/*-----------------------------------------------------------------------------
 *                         DEFINITIONS AND MACROS
 *
 *-----------------------------------------------------------------------------
 */
#define MEMCLK_FREQ_TO_ID(Freq)  (((Freq) == DDR2400_FREQUENCY) ? 0x1F : (((Freq) / 33) - 6))

#define MEMCLK_ID_TO_FREQ(Id)  ( ((Id) == 0x1F) ? DDR2400_FREQUENCY : ((((Id) + 6) * 33) + (((Id) + 6) / 3)) )

/*----------------------------------------------------------------------------
 *                         TYPEDEFS, STRUCTURES, ENUMS
 *
 *----------------------------------------------------------------------------
 */

/// Carrizo package type
typedef enum {
  CZ_FP4,           ///< FP4 (BGA)
  CZ_AM4,           ///< AM4 (BGA)
  CZ_FM2r2,         ///< FM2r2 (uPGA)
  UNKNOWN           ///< Unknown package type
} CZ_PACKAGE_TYPE;

/// DRAM CAD Bus Configuration for all Memory Pstate.
typedef struct _DRAM_CAD_BUS_CONFIG_CZ {
  BOOLEAN SlowMode [MAX_MEMORY_PSTATE_CZ];      ///< Slow Access Mode
  UINT32  DctAddrTmg [MAX_MEMORY_PSTATE_CZ];    ///< AddrCmdSetup, CsOdtSetup, and CkeSetup
} DRAM_CAD_BUS_CONFIG_CZ;

/// The structure of one entry of a TxPrePN table
typedef struct {
  UINT16 MaxSpeed;      ///< Highest memory speed for this setting
  UINT8  DrvStrenP;     ///< Driver strength
  UINT8  TxPrePNVal[3]; ///< Tx predriver value per voltage
} TXPREPN_ENTRY;

/// The structure describes how to extract data and program TxPrePN
typedef struct {
  BIT_FIELD_NAME BfName;   ///< Bit field to set
  TXPREPN_ENTRY  *TabPtr;  ///< Pointer to TxPrePN table
  UINT16         PsOffset; ///< Offset to find DrvStrenP from PS struct
} PROG_TXPREPN_STRUCT;

/*----------------------------------------------------------------------------
 *                           FUNCTIONS PROTOTYPE
 *
 *----------------------------------------------------------------------------
 */
BOOLEAN
MemConstructNBBlockCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN OUT   MEM_DATA_STRUCT *MemPtr,
  IN       MEM_FEAT_BLOCK_NB *FeatPtr,
  IN       MEM_SHARED_DATA *SharedPtr,
  IN       UINT8 NodeID
  );

VOID
MemNInitNBDataCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

VOID
MemNInitDefaultsCZ (
  IN OUT   MEM_DATA_STRUCT *MemPtr
  );

UINT16
MemNGetMemClkFreqInCurrentContextCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

VOID
MemNProgramNbPstateDependentRegistersCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

BOOLEAN
MemNReleaseNbPstateCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN OUT   VOID *OptParam
  );

VOID
MemNSetPhyDdrModeCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8  Mode
  );

VOID
MemNSwitchMemPstateCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 MemPstate
  );

VOID
MemNSyncChannelInitCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

BOOLEAN
MemNHtMemMapCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

BOOLEAN
MemNPlatformSpecCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

VOID
MemNDisableDctCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

VOID
MemNSwitchDctCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 Dct
  );

VOID
MemNInitNBRegTableCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN OUT   TSEFO NBRegTable[]
  );

BOOLEAN
MemNIsIdSupportedCZ (
  IN       SOC_LOGICAL_ID *LogicalIdPtr
  );

BOOLEAN
MemNDctCfgSelectCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       VOID *Dct
  );

UINT32
MemNCmnGetSetFieldCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 IsSet,
  IN       UINTN FieldName,
  IN       UINT32 InputValue
  );

UINT32
MemNGetUmaSizeCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

VOID
MemNAllocateC6AndAcpEngineStorageCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

BOOLEAN
MemNAutoConfigCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

VOID
MemNPhyGenCfgCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

VOID
MemNPhyVoltageLevelCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8  Mode
  );

UINT32
MemNcmnGetSetTrainDlyCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 IsSet,
  IN       TRN_DLY_TYPE TrnDly,
  IN       DRBN DrbnVar,
  IN       UINT16 Field
  );

VOID
MemNProgramChannelFreqCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8  Mode
  );

BOOLEAN
MemNCSIntLvLowAddrAdjCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN OUT   VOID *LowBit
  );

VOID
MemNGetMaxLatParamsCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT16 MaxRcvEnDly,
  IN OUT   UINT16 *MinDlyPtr,
  IN OUT   UINT16 *MaxDlyPtr,
  IN OUT   UINT16 *DlyBiasPtr
  );

VOID
MemNResetRcvFifoCZ (
  IN OUT   struct _MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 Dummy
  );

BOOLEAN
MemNFixupUmaInfoCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN OUT   VOID *OptParam
  );

BOOLEAN
MemNFinalizeMctCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

VOID
MemNCapSpeedBatteryLifeCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

BOOLEAN
MemNForceEccSymbolSizeCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN OUT   VOID *Size
  );

VOID
MemNInitChannelIntlvAddressBitCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

VOID
MemNDramPhyPowerSavingsCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8  Mode
  );

VOID
MemNDisableScrubberCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

VOID
MemNRestoreScrubberCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

VOID
MemNAddlDramPhyPowerSavingsCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

VOID
MemNLoadPmuFirmwareCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

CZ_PACKAGE_TYPE
MemNGetPackageTypeCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

VOID
MemNConfigureDisDllShutdownSrCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

BOOLEAN
MemTTrainMaxLatencyCZ (
  IN OUT   MEM_TECH_BLOCK *TechPtr
  );

BOOLEAN
MemNDisableMemHoleMappingCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN OUT   VOID *OptParam
  );

BOOLEAN
MemNRestoreMemHoleMappingCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN OUT   VOID *OptParam
  );

VOID
MemNEnablePhyCalibrationCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

VOID
MemNPendOnPhyCalibrateCompletionCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

VOID
MemNRateOfPhyCalibrateCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

VOID
MemNDisablePmuCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

VOID
MemNClockAndPowerGateUnusedDctCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

VOID
MemNDimmExcludesCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

BOOLEAN
MemS3PspDetectionCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

BOOLEAN
MemS3PspPlatformSecureBootEnCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

BOOLEAN
MemRunningOnPspCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

BOOLEAN
MemPspDetectionMechanismCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

BOOLEAN
MemPspPlatformSecureBootEnCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

VOID
MemNPopulatePmuSramConfigCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

VOID
MemNPopulatePmuSramTimingsCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

BOOLEAN
MemNCheckPmuFirmwareImageCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

VOID
MemNLoadPmuFirmwareImageCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );


VOID
MemNDramPowerMngTimingCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

BOOLEAN
MemNDramScrubErratum792CZ (
  IN OUT   MEM_NB_BLOCK  *NBPtr,
  IN OUT   VOID *OptParam
  );

BOOLEAN
MemNGetDdrMaxRateCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       VOID *OptParam
  );

#endif  /* _MNCZ_H_ */

