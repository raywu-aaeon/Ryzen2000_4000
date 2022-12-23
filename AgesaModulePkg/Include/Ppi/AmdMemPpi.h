/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD MEM PPI prototype definition
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  PSP
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-09 12:28:05 -0600 (Tue, 09 Dec 2014) $
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
#ifndef _AMD_MEM_PPI_H_
#define _AMD_MEM_PPI_H_

#include <Base.h>
#include "AGESA.h"
#include "PlatformMemoryConfiguration.h"
#include "Library/AmdCalloutLib.h"

//----------------------------------------------------
//
//  Amd Memory Service Functions
//
//-------------------------------------------------------

/**
  Reads Service for the Memory Above 4GB

  Parameters:
  PeiServices
    A pointer to the PEI services
  AmountOfMemory
    Return data pointer for the amount of memory

  Status Codes Returned:
  EFI_SUCCESS           - Return value is valid
  EFI_UNSUPPORTED       - This function is not supported by this version of the driver
**/
typedef EFI_STATUS (EFIAPI * PEI_AMD_SOC_GET_MEMORY_ABOVE_4GB_INTERFACE  ) (
  IN      EFI_PEI_SERVICES  **PeiServices,
     OUT  UINT32            *AmountOfMemory
  );
/**
  Read Service for the Memory Below 4GB

  Parameters:
  PeiServices
    A pointer to the PEI services
  AmountOfMemory
    Return data pointer for the amount of memory

  Status Codes Returned:
  EFI_SUCCESS           - Return value is valid
  EFI_UNSUPPORTED       - This function is not supported by this version of the driver
**/
typedef EFI_STATUS (EFIAPI * PEI_AMD_SOC_GET_MEMORY_BELOW_4GB_INTERFACE  ) (
  IN      EFI_PEI_SERVICES  **PeiServices,
     OUT  UINT32            *AmountOfMemory
  );
/**
  Read Service for the memory Below 1TB

  Parameters:
  PeiServices
    A pointer to the PEI services
  AmountOfMemory
    Return data pointer for the amount of memory

  Status Codes Returned:
  EFI_SUCCESS           - Return value is valid
  EFI_UNSUPPORTED       - This function is not supported by this version of the driver
**/
typedef EFI_STATUS (EFIAPI * PEI_AMD_SOC_GET_MEMORY_BELOW_1TB_INTERFACE  ) (
  IN      EFI_PEI_SERVICES  **PeiServices,
     OUT  UINT32            *AmountOfMemory
  );
/**
  Read Service for the total amount of memory in the system

  Parameters:
  PeiServices
    A pointer to the PEI services
  AmountOfMemory
    Return data pointer for the amount of memory

  Status Codes Returned:
  EFI_SUCCESS           - Return value is valid
  EFI_UNSUPPORTED       - This function is not supported by this version of the driver
**/
typedef EFI_STATUS (EFIAPI * PEI_AMD_SOC_GET_TOTAL_MEMORY_SIZE_INTERFACE) (
  IN      EFI_PEI_SERVICES  **PeiServices,
     OUT  UINT32            *AmountOfMemory
  );
/**
  Read Service for the Bottom of MMIO

  Parameters:
  PeiServices
    A pointer to the PEI services
  AmountOfMemory
    Return data pointer for the amount of memory

  Status Codes Returned:
  EFI_SUCCESS           - Return value is valid
  EFI_UNSUPPORTED       - This function is not supported by this version of the driver
**/
typedef EFI_STATUS (EFIAPI * PEI_AMD_SOC_GET_MEMORY_BOTTOM_IO_INTERFACE) (
  IN      EFI_PEI_SERVICES  **PeiServices,
     OUT  UINT32            *AmountOfMemory
  );
/**
  Read Service for the Memory Frequency of a channel

  Parameters:
  PeiServices
    A pointer to the PEI services
  Channel
    A pointer to the channel to read
  Frequency
    Return data pointer for a channel frequency

  Status Codes Returned:
  EFI_SUCCESS           - Return value is valid
  EFI_UNSUPPORTED       - This function is not supported by this version of the driver
**/
typedef EFI_STATUS (EFIAPI * PEI_AMD_SOC_GET_MEMORY_FREQUENCY_INTERFACE) (
  IN      EFI_PEI_SERVICES  **PeiServices,
     OUT  UINT32            Channel,
     OUT  UINT32            *Frequency
  );
/**
  Read Service for the Memory Frequency of a channel

  Parameters:
  PeiServices
    A pointer to the PEI services
  UmaInfo
    Return data pointer for the UmaInfo

  Status Codes Returned:
  EFI_SUCCESS           - Return value is valid
  EFI_UNSUPPORTED       - This function is not supported by this version of the driver
**/
typedef EFI_STATUS (EFIAPI * PEI_AMD_SOC_GET_UMA_INFO_INTERFACE) (
  IN      EFI_PEI_SERVICES  **PeiServices,
     OUT  UINT32            *UmaInfo
  );



/**
  Get the Memory Map Interface

  Parameters:
  PeiServices
    A pointer to the PEI services
  NumberOfHoles
    The number of holes in the system memory map
  TopOfSystemMemory
    Top of system memory
  MemHoleDescPtr
    Pointer to an open ended array of MEMORY_HOLE_DESCRIPTORs.

  Status Codes Returned:
  EFI_SUCCESS           - Return value is valid
  EFI_UNSUPPORTED       - This function is not supported by this version of the driver
**/
typedef EFI_STATUS (EFIAPI * PEI_GET_SYSTEM_MEMORY_MAP) (
  IN CONST EFI_PEI_SERVICES     **PeiServices,
  IN UINT32                     *NumberOfHoles,
  IN UINT64                     *TopOfSystemMemory,
  IN VOID                       **MemHoleDescPtr
 );



//----------------------------------------------------
//
//  Amd Memory Init Complete Ppi
//
//-------------------------------------------------------
extern EFI_GUID gAmdMemoryInitCompletePpiGuid;

//----------------------------------------------------
//
//  Amd Memory UMA Info
//
//-------------------------------------------------------
typedef struct _AMD_MEMORY_UMA_INFO {
  UMA_MODE UmaMode; ///<  Uma Mode
                       ///<  0 = None
                       ///<  1 = Specified
                       ///<  2 = Auto
  UINT32 UmaSize; ///<  The size of shared graphics dram (16-bits)
                     ///<  NV_UMA_Size[31:0]=Addr[47:16]
                     ///<
  UINT32 UmaBase;
} AMD_MEMORY_UMA_INFO;

//-----------------------------------------------------------------------------
///
/// APOB SPD Data for each DIMM.
///
typedef struct _AMD_MEM_SPD_STRUCT {
  UINT8  SocketNumber;          ///< Indicates the socket number
  UINT8  ChannelNumber;          ///< Indicates the channel number
  UINT8  DimmNumber;          ///< Indicates the channel number
  UINT8  PageAddress;
  BOOLEAN DimmPresent;   //< Indicates if the DIMM is present
  UINT8  MuxPresent;      ///< SpdMux Present or not. if 1, then yes otherwise no
  UINT8  MuxI2CAddress;      ///< MuxI2cAddress
  UINT8  MuxChannel;         ///< MuxChannel no.
  UINT32 Address;         ///< SMBus address of the DRAM
  UINT32 SerialNumber;   ///< DIMM Serial Number
  UINT8 Data[512];      ///< Buffer for 512 Bytes of SPD data from DIMM
} AMD_MEM_SPD_STRUCT;

/// AMD_MEM_DIMM_SPD_DATA_STRUCT_V2
typedef struct {
  LIST_ENTRY Link;
  AMD_MEM_SPD_STRUCT DimmSpdInfo;  ///< SPD Data
} AMD_MEM_DIMM_SPD_DATA_STRUCT_V2;

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

//
// Macro to get DIMM presence
//
#define GET_DIMM_PRESENCE_OF(This, DimmPresentMap, Socket, Die, Channel, Dimm) \
       (UINT8) ((DimmPresentMap##[Socket * ((AMD_MEMORY_INIT_COMPLETE_PPI  *)This)->MaxDiePerSocket +\
                      Die] >> (Channel *  ((AMD_MEMORY_INIT_COMPLETE_PPI  *)This)->MaxDimmPerChannel + Dimm)) & 1)
#endif

typedef struct _MEM_CFG_INFO {
   union {
     BOOLEAN Enabled;    // Status.Enabled - TRUE: Enabled.
     UINT16 Value;       // Status.Value - Configured value.
   } Status;
   UINT16 StatusCode;    //Status Code: MEM_STATUS_CODE_GENERAL_INFO
} MEM_CFG_INFO;
//----------------------------------------------------
//
//  Amd Memory Init Complete Ppi
//
//-------------------------------------------------------
typedef struct _AMD_MEMORY_INIT_COMPLETE_PPI {
  UINT32                 Revision;                                              ///< revision
  UINT16                 AmdBottomIo;                                           ///< Bottom IO
  UINT32                 AmdMemoryBelow4gb;                                     ///< Memory below 4G
  UINT32                 AmdMemoryAbove4gb;                                     ///< Memory above 4G
  UINT32                 AmdMemoryBelow1Tb;                                     ///< Memory below 1T
  UINT32                 AmdTotalMemorySize;                                    ///< Total Memory Size
  UINT32                 AmdMemoryFrequency;                                    ///< Memory Frequency
  DIMM_VOLTAGE           AmdMemoryVddIo;                                        ///< Memory Vddio
  VDDP_VDDR_VOLTAGE      AmdMemoryVddpVddr;                                     ///< Memory Vddp Vddr
  AMD_MEMORY_UMA_INFO    AmdGetUmaInfo;                                         ///< AMD UMA Info
  UINT32                 DdrMaxRate;                                            ///< DdrMaxRate
  PEI_GET_SYSTEM_MEMORY_MAP        GetSystemMemoryMap;                          ///< System Memory Map

  LIST_ENTRY SpdDataListHead;

  ///
  /// Use below info. to be aware of max. number of Socket/Die/Channel/Dimm supported.
  /// Those are filled in by specific memory PEIMs.
  /// 
  UINT8  MaxSocketSupported;          ///< Indicates max. socket supported
  UINT8  MaxDiePerSocket;             ///< Indicates max. die per socket
  UINT8  MaxChannelPerDie;            ///< Indicates max. channel per die
  UINT8  MaxDimmPerChannel;           ///< Indicates max. dimm per channel

  /// Dynamic data
  // Status reporting stuff
  UINT16 *DimmPresentMap;             ///< DimmPresentMap[MaxSocketSupported * MaxDiePerSocket]
                                      ///< Bit[1:0] - Dimm[1:0] of Channel0, .. , Bit[15:14] - Dimm[1:0] of Channel7
  MEM_CFG_INFO *ChipselIntlv;         ///< ChipselIntlv[MaxSocketSupported * MaxDiePerSocket * MaxChannelPerDie] (APCB_TOKEN_CONFIG_ENABLECHIPSELECTINTLV)
  MEM_CFG_INFO *DramEcc;              ///< DramEcc[MaxSocketSupported * MaxDiePerSocket] (APCB_TOKEN_CONFIG_ENABLEECCFEATURE)
  MEM_CFG_INFO *DramParity;           ///< DramParity[MaxSocketSupported * MaxDiePerSocket] (APCB_TOKEN_CONFIG_ENABLEPARITY)
  MEM_CFG_INFO *AutoRefFineGranMode;  ///< AutoRefFineGranMode[MaxSocketSupported * MaxDiePerSocket] (APCB_TOKEN_CONFIG_AUTOREFFINEGRANMODE)
  // Platform Tuning stuff
  UINT8 *MemCtrllerProcOdtDddr4;      ///< MemCtrllerProcOdtDddr4[MaxSocketSupported * MaxDiePerSocket]
  UINT8 *MemCtrllerRttNomDddr4;       ///< MemCtrllerRttNomDddr4[MaxSocketSupported * MaxDiePerSocket]
  UINT8 *MemCtrllerRttWrDddr4;        ///< MemCtrllerRttWrDddr4[MaxSocketSupported * MaxDiePerSocket]
  UINT8 *MemCtrllerRttParkDddr4;      ///< MemCtrllerRttParkDddr4[MaxSocketSupported * MaxDiePerSocket]
  UINT8 *MemCtrllerAddrCmdSetupDddr4; ///< MemCtrllerAddrCmdSetupDddr4[MaxSocketSupported * MaxDiePerSocket]
  UINT8 *MemCtrllerCsOdtSetupDddr4;   ///< MemCtrllerCsOdtSetupDddr4[MaxSocketSupported * MaxDiePerSocket]
  UINT8 *MemCtrllerCkeSetupDddr4;     ///< MemCtrllerCkeSetupDddr4[MaxSocketSupported * MaxDiePerSocket]
  UINT8 *MemCtrllerCadBusClkDrvStrenDddr4; ///< MemCtrllerCadBusClkDrvStrenDddr4[MaxSocketSupported * MaxDiePerSocket]
  UINT8 *MemCtrllerCadBusAddrCmdDrvStrenDddr4; ///< MemCtrllerCadBusAddrCmdDrvStrenDddr4[MaxSocketSupported * MaxDiePerSocket]
  UINT8 *MemCtrllerCsOdtCmdDrvStrenDddr4; ///< MemCtrllerCsOdtCmdDrvStrenDddr4[MaxSocketSupported * MaxDiePerSocket]
  UINT8 *MemCtrllerCkeDrvStrenDddr4;      ///< MemCtrllerCkeDrvStrenDddr4[MaxSocketSupported * MaxDiePerSocket]

  /// Fixed data
  // Status reporting stuff
  MEM_CFG_INFO MbistTestEnable;       ///< MbistTestEnable (APCB_TOKEN_CONFIG_MEM_MBIST_TEST_ENABLE)
  MEM_CFG_INFO MbistAggressorEnable;  ///< MbistAggressorEnable (APCB_TOKEN_CONFIG_MEM_MBIST_AGGRESOR_ON)
  MEM_CFG_INFO MbistPerBitSlaveDieReport;   ///< MbistPerBitSlaveDieReport (APCB_TOKEN_CONFIG_MEM_MBIST_PER_BIT_SLAVE_DIE_REPORT)
  MEM_CFG_INFO DramTempControlledRefreshEn; ///< DramTempControlledRefreshEn (APCB_TOKEN_CONFIG_MEM_TEMP_CONTROLLED_REFRESH_EN)
  MEM_CFG_INFO UserTimingMode;        ///< UserTimingMode (APCB_TOKEN_CONFIG_USERTIMINGMODE)
  MEM_CFG_INFO UserTimingValue;       ///< UserTimingValue (APCB_TOKEN_CONFIG_MEMCLOCKVALUE)
  MEM_CFG_INFO MemBusFreqLimit;       ///< MemBusFreqLimit (APCB_TOKEN_CONFIG_MEMORYBUSFREQUENCYLIMIT)
  MEM_CFG_INFO EnablePowerDown;       ///< EnablePowerDown (APCB_TOKEN_CONFIG_ENABLEPOWERDOWN)
  MEM_CFG_INFO DramDoubleRefreshRate; ///< DramDoubleRefreshRate (APCB_TOKEN_CONFIG_DRAMDOUBLEREFRESHRATE)
  MEM_CFG_INFO PmuTrainMode;          ///< PmuTrainMode (APCB_TOKEN_CONFIG_PMUTRAINMODE)
  MEM_CFG_INFO EccSymbolSize;         ///< EccSymbolSize (APCB_TOKEN_CONFIG_ECCSYMBOLSIZE)
  MEM_CFG_INFO UEccRetry;             ///< UEccRetry (APCB_TOKEN_CONFIG_UECC_RETRY_DDR4)
  MEM_CFG_INFO IgnoreSpdChecksum;     ///< IgnoreSpdChecksum (APCB_TOKEN_CONFIG_IGNORESPDCHECKSUM)
  MEM_CFG_INFO EnableBankGroupSwapAlt;///< EnableBankGroupSwapAlt (APCB_TOKEN_CONFIG_ENABLEBANKGROUPSWAPALT)
  MEM_CFG_INFO EnableBankGroupSwap;   ///< EnableBankGroupSwap (APCB_TOKEN_CONFIG_ENABLEBANKGROUPSWAP)
  MEM_CFG_INFO DdrRouteBalancedTee;   ///< DdrRouteBalancedTee (APCB_TOKEN_CONFIG_DDRROUTEBALANCEDTEE)
  MEM_CFG_INFO NvdimmPowerSource;     ///< NvdimmPowerSource (APCB_TOKEN_CONFIG_MEM_NVDIMM_POWER_SOURCE)
  MEM_CFG_INFO OdtsCmdThrotEn;        ///< OdtsCmdThrotEn (APCB_TOKEN_CONFIG_ODTSCMDTHROTEN)
  MEM_CFG_INFO OdtsCmdThrotCyc;       ///< OdtsCmdThrotCyc (APCB_TOKEN_CONFIG_ODTSCMDTHROTCYC)
} AMD_MEMORY_INIT_COMPLETE_PPI;

#define AMD_MEMORY_INIT_COMPLETE_REVISION   0x0001  /// F17 Model00
#define AMD_MEMORY_INIT_COMPLETE_REV_0002   0x0002  /// F17 Model10&20
#define AMD_MEMORY_INIT_COMPLETE_REV_0003   0x0003  /// F17 Model00 w/ PPR support
#define AMD_MEMORY_INIT_COMPLETE_REV_0400   0x0400  /// F17 Model30 and back compatible w/ F17 Model00

//----------------------------------------------------
//
//  Amd Memory Channel Translation Table Ppi
//
//-------------------------------------------------------
typedef struct _AMD_MEMORY_CHANNEL_XLAT_PPI {
  UINT32                          Revision;                                              ///< revision
  VOID                            *XLatTab;                                              ///< Translation Table
} AMD_MEMORY_CHANNEL_XLAT_PPI;

#define AMD_MEMORY_CHANNEL_XLAT_REVISION   0x01

//----------------------------------------------------
//
//  Amd Memory Platform Configuration Ppi
//
//-------------------------------------------------------
typedef struct _AMD_AGESA_MEM_PLATFORM_CONFIGURATION_PPI {
  UINT32                          Revision;                                              ///< revision
  PSO_ENTRY                       *PlatformMemoryConfiguration;                          ///< Platform Memory Configurattion
} AMD_AGESA_MEM_PLATFORM_CONFIGURATION_PPI;

//----------------------------------------------------
//
// PEI_AMD_PLATFORM_DIMM_SPD_PPI data structure definition.
//
//-------------------------------------------------------
typedef struct _PEI_AMD_PLATFORM_DIMM_SPD_PPI PEI_AMD_PLATFORM_DIMM_SPD_PPI;

//----------------------------------------------------
//
// Defines function prototype for PlatformDimmSpdRead
//
//-------------------------------------------------------
typedef
EFI_STATUS
(EFIAPI *PEI_AMD_DIMM_SPD_READ) (
  IN      EFI_PEI_SERVICES                    **PeiServices,  ///< Pointer to PeiServices
  IN struct _PEI_AMD_PLATFORM_DIMM_SPD_PPI    *This,          ///< Pointer to the PPI structure
  IN OUT  AGESA_READ_SPD_PARAMS               *SpdData        ///< SPD Data Buffer
  );

//----------------------------------------------------
//
// PEI_AMD_PLATFORM_DIMM_SPD_PPI data structure definition.
//
//-------------------------------------------------------
struct _PEI_AMD_PLATFORM_DIMM_SPD_PPI {          // See the Forward Declaration above
  UINT8                                       TotalNumberOfSocket;    ///< Total Number of Physical Socket.
  UINT8                                       TotalNumberOfDimms;     ///< Total Number of DIMMS
  PEI_AMD_DIMM_SPD_READ                       PlatformDimmSpdRead;    ///< Function to be called
};

extern EFI_GUID gAmdMemoryBeforeDramInitPpiGuid;

/**
  Memory Before DRAM Init Interface

  Parameters:
  PeiServices

  Status Codes Returned:
  EFI_SUCCESS           - Return value is valid
  EFI_UNSUPPORTED       - This function is not supported by this version of the driver
**/
typedef EFI_STATUS (EFIAPI * PEI_AMD_MEMORY_BEFORE_DRAM_INIT_INTERFACE  ) (
  IN      EFI_PEI_SERVICES  **PeiServices
  );

//----------------------------------------------------
//
//  Amd Memory Before Dram Init Ppi
//
//-------------------------------------------------------
typedef struct _PEI_AMD_MEMORY_BEFORE_DRAM_INIT_PPI {
  UINT32                          Revision;                                              ///< revision
} PEI_BEFORE_DRAM_INIT_COMPLETE_PPI;

#define AMD_MEMORY_BEFORE_DRAM_INIT_REVISION   0x00

extern EFI_GUID gAmdMemoryAfterDramInitPpiGuid;

//----------------------------------------------------
//
//  Amd Memory After Dram Init Ppi
//
//-------------------------------------------------------
typedef struct _PEI_AMD_MEMORY_AFTER_DRAM_INIT_PPI {
  UINT32                          Revision;                                              ///< revision
} PEI_AFTER_DRAM_INIT_COMPLETE_PPI;

#define AMD_MEMORY_AFTER_DRAM_INIT_REVISION   0x00

extern EFI_GUID gAmdMemoryInitializeAgesaMemoryPpiGuid;

//----------------------------------------------------
//
//  Amd Memory Init Ppi
//
//-------------------------------------------------------
typedef struct _PEI_INITIALIZE_AGESA_MEMORY_PPI {
  UINT32                          Revision;                                              ///< revision
} PEI_INITIALIZE_AGESA_MEMORY_PPI;

#define AMD_MEMORY_INITIALIZE_AGESA_MEMORY_REVISION   0x00

extern EFI_GUID gAmdMemoryFamilyServicesPpiGuid;

//----------------------------------------------------
//
//  Amd Memory Family Services PPI
//
//-------------------------------------------------------
typedef struct _PEI_MEMORY_FAMILY_SERVICE_PPI {
  UINT32                          Revision;                                              ///< revision
  PEI_AMD_SOC_GET_MEMORY_ABOVE_4GB_INTERFACE   AmdGetMemoryAbove4gbFamilyService;        ///< Service to get memory above 4G
  PEI_AMD_SOC_GET_MEMORY_BELOW_4GB_INTERFACE   AmdGetMemoryBelow4gbFamilyService;        ///< Service to get memory below 4G
  PEI_AMD_SOC_GET_MEMORY_BELOW_1TB_INTERFACE    AmdGetMemoryBelow1TbFamilyService;       ///< Service to get memory below 1T
  PEI_AMD_SOC_GET_MEMORY_BOTTOM_IO_INTERFACE    AmdGetBottomIo1TbFamilyService;          ///< Service to get BottomIo
  PEI_AMD_SOC_GET_TOTAL_MEMORY_SIZE_INTERFACE   AmdGetTotalMemorySize4gbFamilyService;   ///< Service to get total memory
} PEI_MEMORY_FAMILY_SERVICE_PPI;

#define AMD_MEMORY_FAMILY_SERVICE_REVISION   0x00

//
// GUID definition
//

extern EFI_GUID gAmdMemoryPoolPointerTablePpiGuid;

//----------------------------------------------------
//
//  Definition for AGESA Buffer Handles
//
//-------------------------------------------------------
typedef enum {
  AMD_INIT_HANDLE = 0,                        ///< First Handle pointer
  AMD_CRAT_STRUCTURE_POOL_PTR,                ///< Pointer to CRAT Table structure
  AMD_DATA_EYES_POOL_PTR,                     ///< Pointer to Data eyes table
  AMD_DATA_EYE_WORK_AREA_POOL_PTR,            ///< Pointer to Data eye work area
  AMD_DMI_DEV_INFO_STRUCTURE_POOL_PTR,        ///< Pointer to Dmi Dev Info Struncture
  AMD_DMI_DEV_INFO_DDR4_STRUCTURE_POOL_PTR,   ///< Pointer to Dmi Dev Info Struncture for DDR4
  AMD_NB_STRUCTURE_POOL_PTR,                  ///< Pointer to NB Structure
  AMD_2D_RD_WR_RIM_HANDLES_POOL_PTR,          ///< Pointer to 2D RD WR RIM Handle
  AMD_2D_RD_WR_POOL_PTR,                      ///< Pointer to 2D RD WR structure
  AMD_DEVICE_BLOCK_HEADER_POOL_PTR,           ///< Pointer to Device Block Header
  AMD_SPECIAL_CASE_REG_HEADER_POOL_PTR,       ///< Pointer to Special Case Register Heater
  AMD_MEM_DATA_STRUCT_POOL_PTR,               ///< Pointer to Mem Data Struct
  AMD_NB_BLOCK_POOL_PTR,                      ///< Pointer to NB Block
  AMD_S3_MEM_NB_BLOCK_POOL_PTR,               ///< Pointer to S3 Mem NB Block
  AMD_MEM_DIE_STRUCT_POOL_PTR,                ///< Pointer to Mem die struct
  AMD_S3_DATA_HANDLE_STRUCT_POOL_PTR,         ///< Pointer to S3 Data handle struct
  AMD_S3_SAVE_HANDLE_STRUCT_POOL_PTR,         ///< Pointer to S3 Save handle struct
  AMD_SKIP_MEM_S3_SAVE_STRUCT_POOL_PTR,       ///< Pointer to S3 Save struct
  AMD_SKIP_MEM_S3_NB_HANDLE_POOL_PTR,         ///< Pointer to S3 NB Handle
  AMD_SPD_DAT_STRUCTURE_POOL_PTR,             ///< Pointer to SPD Dat structure
  AMD_UMA_INFO_HANDLE_POOL_PTR,               ///< Pointer to UMA Info Handle
  AMD_MEM_TRAIN_BUFFER_POOL_PTR,              ///< Pointer to Mem train buffer
  AMD_NB_REG_TABLE_POOL_PTR,                  ///< Pointer to NB reg table
  AMD_UMA_INFO_POOL_PTR,                      ///< Pointer to UMC Info
  AMD_GNB_ACP_ENGINE_POOL_PTR,                ///< Pointer to GNB ACP Engine
  AMD_MEM_PMU_SRAM_MSG_BLOCK_POOL_PTR,        ///< Pointer to PMU SRAM MSG Block
  AMD_TRN_DATA_POOL_PTR,                      ///< Pointer to TRN Data
  AMD_MEM_2D_RDDQS_RIM_POOL_PTR,              ///< Pointer to  2D RDDQS RIM
  AMD_MEM_AUTO_HANDLER_POOL_PTR,              ///< Pointer to Mem Auto Handler
  AMD_FINAL_POOL_PTR                          ///< Last Handle Pointer
} AGESA_BUFFER_HANDLE;

//----------------------------------------------------
//
//  Pool Pointer Table PPI
//
//-------------------------------------------------------
typedef struct _AMD_MEM_POOL_PTR_TABLE_PPI {
  UINTN               Revision;               ///< Revision Number
  UINT32              *PtrTable[AMD_FINAL_POOL_PTR];             ///< The Point of Pointer Table List
} AMD_MEM_POOL_PTR_TABLE_PPI;

// Current PPI revision
#define AMD_MEM_POOL_PTR_TABLE_REVISION   0x00

extern EFI_GUID gAmdMemoryTechServicesPpiGuid;

//----------------------------------------------------
//
//  AMD memory tech Services PPI
//
//-------------------------------------------------------
typedef EFI_STATUS (EFIAPI * PEI_AMD_MEM_TECH_SERVICES_INTERFACE  ) (
  );
typedef struct _AMD_MEM_TECH_SERVICES_PPI {
  UINTN               Revision;                                   ///< Revision Number
  PEI_AMD_MEM_TECH_SERVICES_INTERFACE   AmdDimmPresenceService;   ///< Service to detect DIMM presence
} AMD_MEM_TECH_SERVICES_PPI;

// Current PPI revision
#define AMD_MEM_TECH_SERVICES_REVISION   0x00

extern EFI_GUID gAmdMemoryTecnologyPpiGuid;

//----------------------------------------------------
//
//  AMD memory tech PPI
//
//-------------------------------------------------------
typedef struct _PEI_MEMORY_TECHNOLOGY_PPI {
  UINTN               Revision;               ///< Revision Number
} PEI_MEMORY_TECHNOLOGY_PPI;

// Current PPI revision
#define AMD_MEMORY_TECHNOLOGY_REVISION   0x00

extern EFI_GUID gAmdMemoryAgesaReadSpdPpiGuid;

typedef EFI_STATUS (EFIAPI * PEI_AMD_MEMORY_AGESA_READ_SPD_INTERFACE  ) (
  );
//----------------------------------------------------
//
//  AMD memory Read SPD PPI
//
//-------------------------------------------------------
typedef struct _PEI_MEMORY_AGESA_READ_SPD_PPI {
  UINTN               Revision;                             ///< Revision Number
  PEI_AMD_MEMORY_AGESA_READ_SPD_INTERFACE   AgesaReadSpd;   ///< Service to read SPD
} PEI_MEMORY_AGESA_READ_SPD_PPI;

// Current PPI revision
#define AMD_MEMORY_AGESA_READ_SPD_REVISION   0x00

//----------------------------------------------------
//
// Defines function prototype to install Memory feature block
//
//-------------------------------------------------------
typedef
EFI_STATUS (*AMD_MEM_FEAT_ISNTALL_INTERFACE) (
  IN OUT     VOID*      MemFeatBlock                      ///< Memory feature block
  );
//----------------------------------------------------
//
//  AMD memory Install Feature PPI
//
//-------------------------------------------------------
typedef struct _AMD_AGESA_MEM_FEAT_INSTALL_PPI {
  UINT32                                Revision;                   ///< revision
  AMD_MEM_FEAT_ISNTALL_INTERFACE        Install;                    ///< Service to install memory feature block
} AMD_AGESA_MEM_FEAT_INSTALL_PPI;

// Current PPI revision
#define AMD_MEMORY_FEAT_INSTALL_REVISION   0x00

#endif

