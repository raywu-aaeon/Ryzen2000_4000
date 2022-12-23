
/* $NoKeywords:$ */
/**
 * @file
 *
 * @e \$Revision:$   @e \$Date:$
 */
/*****************************************************************************
 *
 * Copyright 2015 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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

#include "MyPorting.h"
#include <RV/APCB.h>
#include <ApcbCustomizedDefinitions.h>
#include <ApcbDefaults.h>

CHAR8 mDummyBuf;

APCB_TYPE_DATA_START_SIGNATURE();
APCB_TYPE_HEADER       ApcbTypeHeader = {
  APCB_GROUP_MEMORY,
  APCB_MEM_TYPE_CONFIG_DEFAULT_PARAMETERS,
  (
    sizeof (APCB_TYPE_HEADER)
  ),
  0,
  0,
  0
};  // SizeOfType will be fixed up by tool

APCB_PARAM_ATTRIBUTE  ParameterListDefaultsAttribute[] = {
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_LIMITMEMORYTOBELOW1TB, sizeof (BOOLEAN) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_USERTIMINGMODE, sizeof (UINT32) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_MEMCLOCKVALUE, sizeof (UINT32) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_ENABLEBANKINTLV, sizeof (BOOLEAN) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_ENABLEECCFEATURE, sizeof (BOOLEAN) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_ENABLEPOWERDOWN, sizeof (BOOLEAN) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_ENABLEPARITY, sizeof (BOOLEAN) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_ENABLEBANKSWIZZLE, sizeof (BOOLEAN) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_ENABLEMEMCLR, sizeof (BOOLEAN) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_UMAMODE, sizeof (UINT8) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_UMASIZE, sizeof (UINT32) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_MEMRESTORECTL, sizeof (BOOLEAN) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_FORCETRAINMODE, sizeof (UINT8) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_DIMMTYPEUSEDINMIXEDCONFIG, sizeof (UINT8) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_DRAMDOUBLEREFRESHRATE, sizeof (BOOLEAN) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_PMUTRAINMODE, sizeof (UINT8) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_ECCREDIRECTION, sizeof (BOOLEAN) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_ECCSYNCFLOOD, sizeof (BOOLEAN) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_ECCSYMBOLSIZE, sizeof (UINT16) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_UMAABOVE4G, sizeof (BOOLEAN) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_UMAALIGNMENT, sizeof (UINT32) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_MEMORYALLCLOCKSON, sizeof (BOOLEAN) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_MEMORYBUSFREQUENCYLIMIT, sizeof (UINT32) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_POWERDOWNMODE, sizeof (UINT32) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_IGNORESPDCHECKSUM, sizeof (BOOLEAN) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_MEMORYQUADRANKCAPABLE, sizeof (BOOLEAN) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_MEMORYRDIMMCAPABLE, sizeof (BOOLEAN) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_MEMORYLRDIMMCAPABLE, sizeof (BOOLEAN) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_MEMORYUDIMMCAPABLE, sizeof (BOOLEAN) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_MEMORYSODIMMCAPABLE, sizeof (BOOLEAN) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_DRAMDOUBLEREFRESHRATEEN, sizeof (BOOLEAN) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_DIMMTYPEDDDR4CAPABLE, sizeof (BOOLEAN) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_DIMMTYPEDDDR3CAPABLE, sizeof (BOOLEAN) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_DIMMTYPELPDDDR3CAPABLE, sizeof (BOOLEAN) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_ENABLEBANKGROUPSWAP, sizeof (BOOLEAN) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_ODTSCMDTHROTEN, sizeof (BOOLEAN) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_SWCMDTHROTEN, sizeof (BOOLEAN) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_FORCEPWRDOWNTHROTEN, sizeof (BOOLEAN) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_ODTSCMDTHROTCYC, sizeof (UINT8) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_SWCMDTHROTCYC, sizeof (UINT8) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_DIMMSENSORCONF, sizeof (UINT16) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_DIMMSENSORUPPER, sizeof (UINT16) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_DIMMSENSORLOWER, sizeof (UINT16) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_DIMMSENSORCRITICAL, sizeof (UINT16) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_DIMMSENSORRESOLUTION, sizeof (UINT8) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_AUTOREFFINEGRANMODE, sizeof (UINT8) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_ENABLEMEMPSTATE, sizeof (BOOLEAN) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_SOLDERDOWNDRAM, sizeof (UINT8) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_DDRROUTEBALANCEDTEE, sizeof (BOOLEAN) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_MEM_PS_ERROR_HANDLING, sizeof (UINT8) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_MEM_TEMP_CONTROLLED_REFRESH_EN, sizeof (BOOLEAN) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_MEMRESTOREVALIDDAYS, sizeof (UINT32) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_DDR_ROUTE_BALANCED_TEE, sizeof (UINT8) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_MEM_TSME_ENABLE, sizeof (BOOLEAN) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_MEM_FORCE_DATA_MASK_DISABLE, sizeof (BOOLEAN) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_MEM_MBIST_TEST_ENABLE, sizeof (BOOLEAN) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_MEM_MBIST_SUBTEST_TYPE, sizeof (UINT8) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_MEM_MBIST_HALT_ON_ERROR, sizeof (BOOLEAN) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_MEM_MBIST_AGGRESOR_ON, sizeof (BOOLEAN) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_MEM_MBIST_PER_BIT_SLAVE_DIE_REPORT, sizeof (UINT8) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_MEM_CPU_VREF_RANGE, sizeof (UINT8) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_MEM_DRAM_VREF_RANGE, sizeof (UINT8) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_PMU_TRAIN_ERROR_RECOVERY, sizeof (BOOLEAN) - 1, 0},
  {0, APCB_TOKEN_CONFIG_LIMIT, 0, 0},
};

_1BYTE_ALIGN UINT8  ParameterListDefaultsValue[] = {
  BSBLN (BLDCFG_MEM_LIMIT_1TB),                 //< Limit memory address space to below 1 TB
  BSU32 (BLDCFG_TIMING_MODE_SELECT),            //< UserTimingMode - User Memclock Mode.
  BSU32 (BLDCFG_MEMORY_CLOCK_SELECT),           //< MemClockValue -  Memory Clock Value.
  BSBLN (BLDCFG_MEMORY_ENABLE_BANK_INTERLEAVING), //< EnableBankIntlv - Dram Bank (chip-select) Interleaving (1-bit).
  BSBLN (BLDCFG_ENABLE_ECC_FEATURE),            //< EnableEccFeature - enable ECC error to go into MCE.
  BSBLN (BLDCFG_MEMORY_POWER_DOWN),             //< EnablePowerDown - CKE based power down mode (1-bit).
  BSBLN (BLDCFG_PARITY_CONTROL),                //< EnableParity - Parity control.
  BSBLN (BLDCFG_BANK_SWIZZLE),                  //< EnableBankSwizzle - BankSwizzle control.
  BSBLN (BLDCFG_ENABLE_MEM_CLR),                //< EnableMemClr - Memory Clear functionality control.
  BSU08 (BLDCFG_UMA_MODE),                      //< UmaMode - Uma Mode
  BSU32 (BLDCFG_UMA_SIZE),                      //< UmaSize - The size of shared graphics dram (16-bits)
  BSBLN (BLDCFG_MEMORY_RESTORE_CONTROL),        //< MemRestoreCtl - Memory context restore control
  BSU08 (BLDCFG_FORCE_TRAIN_MODE),              //< ForceTrainMode - Training Mode
  BSU08 (BLDCFG_DIMM_TYPE_TECHNOLGY),           //< DimmTypeUsedInMixedConfig - Select the preferred technology type that AGESA will enable
  BSBLN (BLDCFG_DRAM_DOUBLE_REFRESH_RATE),      //< DramDoubleRefreshRate - PMU Training Mode
  BSU08 (BLDCFG_PMU_TRAINING_MODE),             //< PmuTrainMode - PMU Training Mode
  BSBLN (BLDCFG_ECC_REDIRECTION),               //< CfgEccRedirection; ///< ECC Redirection.
  BSBLN (BLDCFG_ECC_SYNC_FLOOD),                //< CfgEccSyncFlood -  ECC Sync Flood.
  BSU16 (BLDCFG_ECC_SYMBOL_SIZE),               //< CfgEccSymbolSize -  ECC Symbol Size.
  BSBLN (BLDCFG_UMA_ABOVE_4GB),                 //< CfgUmaAbove4G -  Uma Above 4G Support
  BSU32 (BLDCFG_UMA_BUFFER_ALIGNMENT),          //< CfgUmaAlignment -  Uma alignment
  BSBLN (BLDCFG_MEMORY_ALL_CLOCKS_ON),          //< CfgMemoryAllClocksOn -  Memory All Clocks On.
  BSU32 (BLDCFG_MEMORY_BUS_FREQUENCY_LIMIT),    //< CfgMemoryBusFrequencyLimit -  Memory Bus Frequency Limit.
  BSU32 (BLDCFG_POWER_DOWN_MODE),               //< CfgPowerDownMode -  Power Down Mode.
  BSBLN (BLDCFG_IGNORE_SPD_CHECKSUM),           //< CfgIgnoreSpdChecksum -  Ignore Spd Checksum.
  BSBLN (BLDCFG_MEMORY_QUAD_RANK_CAPABLE),      //< CfgMemoryQuadRankCapable -  Memory Quad Rank Capable.
  BSBLN (BLDCFG_MEMORY_RDIMM_CAPABLE),          //< CfgMemoryRDimmCapable -  Memory RDIMM Capable.
  BSBLN (BLDCFG_MEMORY_LRDIMM_CAPABLE),         //< CfgMemoryLRDimmCapable -  Memory LRDIMM Capable.
  BSBLN (BLDCFG_MEMORY_UDIMM_CAPABLE),          //< CfgMemoryUDimmCapable -  Memory UDIMM Capable
  BSBLN (BLDCFG_MEMORY_SODIMM_CAPABLE),         //< CfgMemorySODimmCapable - Memory SODimm Capable.
  BSBLN (BLDCFG_DRAM_DOUBLE_REFRESH_RATE_ENABLE), //< CfgDramDoubleRefreshRateEn - Double DRAM refresh rate
  BSBLN (BLDCFG_MEMORY_DDR4_CAPABLE),           //< DimmTypeDddr4Capable -  Indicates that the system is DDR4 Capable
  BSBLN (BLDCFG_MEMORY_DDR3_CAPABLE),           //< DimmTypeDddr3Capable -  Indicates that the system is DDR3 Capable
  BSBLN (BLDCFG_MEMORY_LPDDR3_CAPABLE),         //< DimmTypeLpDddr3Capable -  Indicates that the system is LPDDR3 Capable
  BSBLN (BLDCFG_BANK_GROUP_SWAP_MODE),          //< EnableBankGroupSwap - Indicates that Bank Group Swap is enabled
  BSBLN (BLDCFG_ODT_CMD_THROT_ENABLE),          //< UMC::CH::ThrottleCtrl[OdtsCmdThrotEn]
  BSBLN (BLDCFG_SW_CMD_THROT_ENABLE),           //< UMC::CH::ThrottleCtrl[SwCmdThrotEn]
  BSBLN (BLDCFG_FORCE_POWER_DOWN_THROT_ENABLE), //< UMC::CH::ThrottleCtrl[ForcePwrDownThrotEn]
  BSU08 (BLDCFG_ODT_CMD_THROT_CYCLE),           //< UMC::CH::ThrottleCtrl[OdtsCmdThrotCyc]
  BSU08 (BLDCFG_SW_CMD_THROT_CYCLE),            //< UMC::CH::ThrottleCtrl[SwCmdThrotCyc]
  BSU16 (BLDCFG_DIMM_SENSOR_CONFIGURATION),     //< DIMM temperature sensor register index BSU16 (1), Configuration
  BSU16 (BLDCFG_DIMM_SENSOR_UPPER),             //< DIMM temperature sensor register index BSU16 (2), Alarm temperature upper boundary
  BSU16 (BLDCFG_DIMM_SENSOR_LOWER),             //< DIMM temperature sensor register index BSU16 (3), Alarm temperature lower boundary
  BSU16 (BLDCFG_DIMM_SENSOR_CRITICAL),          //< DIMM temperature sensor register index BSU16 (4), Critical temperature
  BSU08 (BLDCFG_DIMM_SENSOR_RESOLUTION),        //< DIMM temperature sensor register index BSU16 (8), Temperature resolution register
  BSU08 (BLDCFG_AUTO_REF_FINE_GRAN_MODE),       //< UMC::CH::SpazCtrl_AutoRefFineGranMode
  BSBLN (BLDCFG_ENABLE_MEMPSTATE),              //< Memory Pstate Enable
  BSU08 (BLDCFG_SOLDERDOWN_DRAM),               //< Solderdown DRAM
  BSBLN (BLDCFG_ENABLE_DDRROUTEBALANCEDTEE),    //< CfgDdrRouteBalancedTee - Motherboard DDR Routing control.
  BSU08 (BLDCFG_MEM_PS_ERROR_HANDLING),         //< Platform specific error handling
  BSBLN (BLDCFG_TEMP_CONTROLLED_REFRESH_EN),    //< Temperature Controlled Refresh Mode
  BSU32 (BLDCFG_MEMRESTORE_VALID_DAYS),         //< Days over which memory restore context is valid
  BSBLN (BLDCFG_DDR_ROUTE_BALANCED_TEE),        //< DQS Routing type to be balanced TEE routing
  BSU08 (BLDCFG_MEM_TSME_ENABLE),               //< TSME enable  
  BSBLN (BLDCFG_MEM_FORCE_DATA_MASK_DISABLE),   //< Force Data Mask Disable
  BSBLN (BLDCFG_MEM_MBIST_TEST_ENABLE),         //< MBIST Test Enable
  BSU08 (BLDCFG_MEM_MBIST_SUBTEST_TYPE),        //< MBIST Test Type
  BSBLN (BLDCFG_MEM_MBIST_HALT_ON_ERROR),       //< Halt on MBIST error
  BSBLN (BLDCFG_MEM_MBIST_AGGRESOR_ON),         //< MBIST Aggressor on
  BSU08 (BLDCFG_MEM_MBIST_PER_BIT_SLAVE_DIE_REPORT), //< MBIST Per Bit Slave Die Report
  BSU08 (BLDCFG_MEM_CPU_VREF_RANGE),            //< MBIST CPU Vref Range
  BSU08 (BLDCFG_MEM_DRAM_VREF_RANGE),           //< MBIST DRAM Vref Range
  BSBLN (BLDCFG_PMU_TRAIN_ERROR_RECOVERY),      //< Pmu train error recovery
  BSU08 (0xFF)
};

APCB_TYPE_DATA_END_SIGNATURE();


int main (IN int argc, IN char * argv [ ])
{
  return 0;
}





