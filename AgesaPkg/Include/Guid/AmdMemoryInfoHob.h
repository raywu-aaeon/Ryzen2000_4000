/* $NoKeywords:$ */
 /**
 * @file
 *
 * Amd Memory Info Hob GUID.
 *
 * Contains GUID Declaration for Memory Info Hob
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  UEFI
 * @e \$Revision: 309083 $   @e \$Date: 2014-12-09 11:28:24 -0600 (Tue, 09 Dec 2014) $
 *
 */
/*
 ****************************************************************************
 * AMD Generic Encapsulated Software Architecture
 *
 * Description: AmdMemoryInfoHob.h - Memory Info Hob GUID
 *
 *****************************************************************************
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

#ifndef _AMD_MEMORY_INFO_HOB_H_
#define _AMD_MEMORY_INFO_HOB_H_

extern EFI_GUID gAmdMemoryInfoHobGuid;
extern EFI_GUID gAmdMemCfgInfoHobGuid;

#pragma pack (push, 1)

#ifndef _MEM_STATUS_CODE_GENERAL_INFO_
#define _MEM_STATUS_CODE_GENERAL_INFO_

typedef enum {
  // General
  CfgStatusSuccess = 0xC000,                 //0xC000
  CfgStatusOptionNotEnabled,                 //0xC001
  CfgStatusDimmNotDetectedOrChannelDisabled, //0xC002
  CfgStatusCbsOptionOverride,                //0xC003
  CfgStatusOptionNotSupported,               //0xC004

  //
  // Specific status code
  //
  // Chipsel interleaving
  CfgStatusCsAddressingNotMatch = 0xC010,    //0xC010
  CfgStatusNotPowerOf2EnabledCs,             //0xC011
  // Dram Ecc
  CfgStatusNotAllDimmEccCapable,             //0xC012
  // Parity
  CfgStatusRcdParityNotEnabled,              //0xC013
  // AutoRefFineGranMode
  CfgStatusRefreshFix2XOnSelectiveODMDimms,  //0xC014
  // UserTimingMode & UserTimingValue & MemBusFreqLimit
  CfgStatusDdrRatePORLimited,                //0xC015
  CfgStatusDdrRateUserTimingLimited,         //0xC016
  CfgStatusDdrRateUserTimingSpecific,        //0xC017
  CfgStatusDdrRateEnforcedDdrRate,           //0xC018
  CfgStatusDdrRateMemoryBusFrequencyLimited, //0xC019
  // EnableBankGroupSwap
  CfgStatusBankGroupSwapAltOverride,         //0xC01A

  // Boundary check
  CfgMaxStatusCode = 0xCFFF                  //0xCFFF
} MEM_STATUS_CODE_GENERAL_INFO;

#endif

//
// Macro to get DIMM presence
//
#define GET_HOB_DIMM_PRESENCE_OF(HobStart, DimmPresentMap, Socket, Die, Channel, Dimm) \
       (UINT8) ((DimmPresentMap##[Socket * ((AMD_MEM_CFG_INFO_HOB *)HobStart)->MaxDiePerSocket +\
                      Die] >> (Channel * ((AMD_MEM_CFG_INFO_HOB *)HobStart)->MaxDimmPerChannel + Dimm)) & 1)

//
// Macro to obtain address
//
#define GET_MEM_CFG_INFO_HOB_ADDR(HobStart, Offset) \
       (VOID *) ((UINT8 *)HobStart + (UINT16) ((AMD_MEM_CFG_INFO_HOB *)HobStart)->Offset)

typedef struct _MEM_CFG_INFO_HOB {
   union {
     BOOLEAN Enabled;   // Status.Enabled - TRUE: Enabled.
     UINT16 Value;      // Status.Value - Configured value.
   } Status;
   UINT16 StatusCode;   //Status Code: MEM_STATUS_CODE_GENERAL_INFO
} MEM_CFG_INFO_HOB;

#define AMD_MEM_CFG_INFO_HOB_VER_0400 0x0400

typedef struct _AMD_MEM_CFG_INFO_HOB {
  /// Version
  UINT32 Version;

  /// Max. number of Socket/Die/Channel/Dimm supported.
  UINT8  MaxSocketSupported; ///< Indicates max. socket supported
  UINT8  MaxDiePerSocket; 	///< Indicates max. die per socket
  UINT8  MaxChannelPerDie; ///< Indicates max. channel per die
  UINT8  MaxDimmPerChannel; ///< Indicates max. dimm per channel

  /// Fixed Data
  MEM_CFG_INFO_HOB MbistTestEnable;       ///< MbistTestEnable (APCB_TOKEN_CONFIG_MEM_MBIST_TEST_ENABLE)
  MEM_CFG_INFO_HOB MbistAggressorEnable;  ///< MbistAggressorEnable (APCB_TOKEN_CONFIG_MEM_MBIST_AGGRESOR_ON)
  MEM_CFG_INFO_HOB MbistPerBitSlaveDieReport;   ///< MbistPerBitSlaveDieReport (APCB_TOKEN_CONFIG_MEM_MBIST_PER_BIT_SLAVE_DIE_REPORT)
  MEM_CFG_INFO_HOB DramTempControlledRefreshEn; ///< DramTempControlledRefreshEn (APCB_TOKEN_CONFIG_MEM_TEMP_CONTROLLED_REFRESH_EN)
  MEM_CFG_INFO_HOB UserTimingMode;	      ///< UserTimingMode (APCB_TOKEN_CONFIG_USERTIMINGMODE)
  MEM_CFG_INFO_HOB UserTimingValue;	      ///< UserTimingValue (APCB_TOKEN_CONFIG_MEMCLOCKVALUE)
  MEM_CFG_INFO_HOB MemBusFreqLimit;	      ///< MemBusFreqLimit (APCB_TOKEN_CONFIG_MEMORYBUSFREQUENCYLIMIT)
  MEM_CFG_INFO_HOB EnablePowerDown;	      ///< EnablePowerDown (APCB_TOKEN_CONFIG_ENABLEPOWERDOWN)
  MEM_CFG_INFO_HOB DramDoubleRefreshRate; ///< DramDoubleRefreshRate (APCB_TOKEN_CONFIG_DRAMDOUBLEREFRESHRATE)
  MEM_CFG_INFO_HOB PmuTrainMode;          ///< PmuTrainMode (APCB_TOKEN_CONFIG_PMUTRAINMODE)
  MEM_CFG_INFO_HOB EccSymbolSize;         ///< EccSymbolSize (APCB_TOKEN_CONFIG_ECCSYMBOLSIZE)
  MEM_CFG_INFO_HOB UEccRetry;             ///< UEccRetry (APCB_TOKEN_CONFIG_UECC_RETRY_DDR4)
  MEM_CFG_INFO_HOB IgnoreSpdChecksum;     ///< IgnoreSpdChecksum (APCB_TOKEN_CONFIG_IGNORESPDCHECKSUM)
  MEM_CFG_INFO_HOB EnableBankGroupSwapAlt;///< EnableBankGroupSwapAlt (APCB_TOKEN_CONFIG_ENABLEBANKGROUPSWAPALT)
  MEM_CFG_INFO_HOB EnableBankGroupSwap;	  ///< EnableBankGroupSwap (APCB_TOKEN_CONFIG_ENABLEBANKGROUPSWAP)
  MEM_CFG_INFO_HOB DdrRouteBalancedTee;	  ///< DdrRouteBalancedTee (APCB_TOKEN_CONFIG_DDRROUTEBALANCEDTEE)
  MEM_CFG_INFO_HOB NvdimmPowerSource;     ///< NvdimmPowerSource (APCB_TOKEN_CONFIG_MEM_NVDIMM_POWER_SOURCE)
  MEM_CFG_INFO_HOB OdtsCmdThrotEn;        ///< OdtsCmdThrotEn (APCB_TOKEN_CONFIG_ODTSCMDTHROTEN)
  MEM_CFG_INFO_HOB OdtsCmdThrotCyc;       ///< OdtsCmdThrotCyc (APCB_TOKEN_CONFIG_ODTSCMDTHROTCYC)

  /// Offset
  UINT16 DimmPresentMapOffset;
  UINT16 ChipselIntlvOffset;
  UINT16 DramEccOffset;
  UINT16 DramParityOffset;
  UINT16 AutoRefFineGranModeOffset;
  UINT16 MemCtrllerProcOdtDddr4Offset;
  UINT16 MemCtrllerRttNomDddr4Offset;
  UINT16 MemCtrllerRttWrDddr4Offset;
  UINT16 MemCtrllerRttParkDddr4Offset;
  UINT16 MemCtrllerAddrCmdSetupDddr4Offset;
  UINT16 MemCtrllerCsOdtSetupDddr4Offset;
  UINT16 MemCtrllerCkeSetupDddr4Offset;
  UINT16 MemCtrllerCadBusClkDrvStrenDddr4Offset;
  UINT16 MemCtrllerCadBusAddrCmdDrvStrenDddr4Offset;
  UINT16 MemCtrllerCsOdtCmdDrvStrenDddr4Offset;
  UINT16 MemCtrllerCkeDrvStrenDddr4Offset;

  /// Dynamic data (appended <in order> following this structure) - DO NOT UNCOMMENT BELOW
  //// Status reporting stuff
  //UINT16 DimmPresentMap[MaxSocketSupported * MaxDiePerSocket]; ///< DimmPresentMap
                                                                 ///< Bit[1:0] - Dimm[1:0] of Channel0, .. , Bit[15:14] - Dimm[1:0] of Channel7
  //MEM_CFG_INFO_HOB ChipselIntlv[MaxSocketSupported * MaxDiePerSocket * MaxChannelPerDie];  ///< ChipselIntlv (APCB_TOKEN_CONFIG_ENABLECHIPSELECTINTLV)
  //MEM_CFG_INFO_HOB DramEcc[MaxSocketSupported * MaxDiePerSocket]; ///< DramEcc (APCB_TOKEN_CONFIG_ENABLEECCFEATURE)
  //MEM_CFG_INFO_HOB DramParity[MaxSocketSupported * MaxDiePerSocket]; ///< DramParity (APCB_TOKEN_CONFIG_ENABLEPARITY)
  //MEM_CFG_INFO_HOB AutoRefFineGranMode[MaxSocketSupported * MaxDiePerSocket];  ///< AutoRefFineGranMode (APCB_TOKEN_CONFIG_AUTOREFFINEGRANMODE)

  //// Platform Tuning stuff
  //UINT8 MemCtrllerProcOdtDddr4[MaxSocketSupported * MaxDiePerSocket];  ///< MemCtrllerProcOdtDddr4
  //UINT8 MemCtrllerRttNomDddr4[MaxSocketSupported * MaxDiePerSocket];   ///< MemCtrllerRttNomDddr4
  //UINT8 MemCtrllerRttWrDddr4[MaxSocketSupported * MaxDiePerSocket];    ///< MemCtrllerRttWrDddr4
  //UINT8 MemCtrllerRttParkDddr4[MaxSocketSupported * MaxDiePerSocket];  ///< MemCtrllerRttParkDddr4
  //UINT8 MemCtrllerAddrCmdSetupDddr4[MaxSocketSupported * MaxDiePerSocket];  ///< MemCtrllerAddrCmdSetupDddr4
  //UINT8 MemCtrllerCsOdtSetupDddr4[MaxSocketSupported * MaxDiePerSocket];  ///< MemCtrllerCsOdtSetupDddr4
  //UINT8 MemCtrllerCkeSetupDddr4[MaxSocketSupported * MaxDiePerSocket];    ///< MemCtrllerCkeSetupDddr4
  //UINT8 MemCtrllerCadBusClkDrvStrenDddr4[MaxSocketSupported * MaxDiePerSocket];  ///< MemCtrllerCadBusClkDrvStrenDddr4
  //UINT8 MemCtrllerCadBusAddrCmdDrvStrenDddr4[MaxSocketSupported * MaxDiePerSocket];  ///< MemCtrllerCadBusAddrCmdDrvStrenDddr4
  //UINT8 MemCtrllerCsOdtCmdDrvStrenDddr4[MaxSocketSupported * MaxDiePerSocket];  ///< MemCtrllerCsOdtCmdDrvStrenDddr4
  //UINT8 MemCtrllerCkeDrvStrenDddr4[MaxSocketSupported * MaxDiePerSocket];  ///< MemCtrllerCkeDrvStrenDddr4
  // ...
} AMD_MEM_CFG_INFO_HOB;

/// Memory descriptor structure for each memory rang
typedef struct {
  UINT64  Base;                             ///< Base address of memory rang
  UINT64  Size;                             ///< Size of memory rang
  UINT32  Attribute;                        ///< Attribute of memory rang
  UINT32  Reserved;                         ///< For alignment purpose
} AMD_MEMORY_RANGE_DESCRIPTOR;

#define AMD_MEMORY_ATTRIBUTE_AVAILABLE      0x1
#define AMD_MEMORY_ATTRIBUTE_UMA            0x2
#define AMD_MEMORY_ATTRIBUTE_MMIO           0x3
#define AMD_MEMORY_ATTRIBUTE_RESERVED       0x4

/// Memory info HOB structure
typedef struct  {
  UINT32              Version;                          ///< Version of HOB structure
  BOOLEAN             AmdMemoryVddioValid;              ///< This field determines if Vddio is valid
  UINT16              AmdMemoryVddio;                   ///< Vddio Voltage
  BOOLEAN             AmdMemoryVddpVddrValid;           ///< This field determines if VddpVddr is valid
  UINT8               AmdMemoryVddpVddr;                ///< VddpVddr voltage
  BOOLEAN             AmdMemoryFrequencyValid;          ///< Memory Frequency Valid
  UINT32              AmdMemoryFrequency;               ///< Memory Frquency
  UINT32              AmdMemoryDdrMaxRate;              ///< Memory DdrMaxRate
  UINT32              NumberOfDescriptor;               ///< Number of memory range descriptor
  AMD_MEMORY_RANGE_DESCRIPTOR Ranges[1];                ///< Memory ranges array
} AMD_MEMORY_INFO_HOB;

#pragma pack (pop)

#define AMD_MEMORY_INFO_HOB_VERISION        0x00000110ul  // Ver: 00.00.01.10

#endif // _AMD_MEMORY_INFO_HOB_H_


