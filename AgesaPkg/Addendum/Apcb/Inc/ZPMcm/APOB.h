/* $NoKeywords:$ */
/**
 * @file
 *
 * APCB.h
 *
 * AGESA PSP Output Block
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem)
 * @e \$Revision: 192403 $ @e \$Date: 2012-12-12 15:46:25 -0600 (Wed, 12 Dec 2012) $
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

#ifndef _APOB_H_
#define _APOB_H_

//#include "PlatformMemoryConfiguration.h"
//#include "mnreg.h"
//#include "mempmu.h"
//#include "AGESA.h"
#include "APOBCMN.h"
/*----------------------------------------------------------------------------
 *   Mixed (DEFINITIONS AND MACROS / TYPEDEFS, STRUCTURES, ENUMS)
 *
 *----------------------------------------------------------------------------
 */

/*-----------------------------------------------------------------------------
 *                         DEFINITIONS AND MACROS
 *
 *-----------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------
 *                         TYPEDEFS, STRUCTURES, ENUMS
 *
 *----------------------------------------------------------------------------
 */
#define APOB_SIGNATURE        0x424F5041  //!!APOB
#define APOB_VERSION          0x0011      ///< AP0B Version
#define APOB_HEADER_OFFSET    0           ///< APOB Header Offset

#define ABL_APOB_MAX_SOCKETS_SUPPORTED   2   ///< Max number of sockets in system
#define ABL_APOB_MAX_DIES_PER_SOCKET     4   ///< Max dies per socket
#define ABL_APOB_MAX_CHANNELS_PER_SOCKET 8   ///< Max Channels per sockets
#define ABL_APOB_MAX_CHANNELS_PER_DIE    2   ///< Max channels per die
#define ABL_APOB_MAX_DIMMS_PER_CHANNEL   2   ///< Max dimms per die
#define ABL_APOB_MAX_CS_PER_CHANNEL      4   ///< Max CS per channel
#define MAX_PMU_SMB_SIZE  0x400   ///< Max PMU SMB size

#define MAX_APOB_ERROR_ENTRIES  64
#define MAX_DDR_PHY_ENTRY_SIZE  4

#define MAX_SIZE_PHY_REPLAY_BUFFER MAX_S3_DDR_PHY_REG_LIST*8
#define MAX_SIZE_GEN_REPLAY_BUFFER 0xE20

// Agesa APOB Defintions
  #define ABL_APOB_HEADER_SIZE sizeof (APOB_HEADER)
  #define ABL_S3_RESTORE_DATA_HEADER_SIZE  sizeof (APOB_TYPE_HEADER)
  #define ABL_S3_RESTORE_DATA_REPLAY_BUFFER_SIZE  sizeof (REPLAY_BUFFER)
  #define ABL_S3_RESTORE_DATA_SIZE ABL_S3_RESTORE_DATA_HEADER_SIZE + ABL_S3_RESTORE_DATA_REPLAY_BUFFER_SIZE
  #define ABL_S3_PHY_RESTORE_DATA_SIZE (ABL_S3_RESTORE_DATA_HEADER_SIZE + ABL_S3_RESTORE_DATA_REPLAY_BUFFER_SIZE)*5
  #define ABL_MEM_GEN_ERROR_SIZE sizeof (APOB_MEM_GENERAL_ERRORS_TYPE_STRUCT)
  #define ABL_MEM_GEN_CONFIG_SIZE sizeof (APOB_MEM_GENERAL_CONFIGURATION_INFO_TYPE_STRUCT)
  #define ABL_GEN_INFO_SIZE sizeof (APOB_GEN_INFO_TYPE_STRUCT)
  #define ABL_MEM_PMU_SMB_SIZE sizeof (APOB_PMU_SMB_TYPE_STRUCT)
  #define ABL_MEM_MBIST_RESULT_SIZE sizeof (APOB_MBIST_STATUS_TYPE_STRUCT)
  #define ABL_SYS_MAP_SIZE APOB_SYS_MAP_STRUCT_SIZE + sizeof (APOB_TYPE_HEADER)
  #define ABL_CCX_LOGICAL_TO_PHYSICAL_MAP_SIZE (sizeof (APOB_CCX_LOGICAL_TO_PHYSICAL_MAP_TYPE_STRUCT))
  #define ABL_EVENT_LOG_SIZE  (sizeof (EVENT_LOG_STRUCT))
  #define ABL_DIMM_SMBUS_INFO_SIZE  (sizeof (APOB_MEM_DIMM_SMBUS_INFO_TYPE_STRUCT))
  #define ABL_MAX_DIMMS (ABL_APOB_MAX_SOCKETS_SUPPORTED * ABL_APOB_MAX_DIES_PER_SOCKET * ABL_APOB_MAX_CHANNELS_PER_DIE * ABL_APOB_MAX_DIMMS_PER_CHANNEL)
  #define ABL_MEM_SMBIOS_INFO_SIZE  (sizeof (APOB_MEM_DMI_HEADER) + ABL_MAX_DIMMS * (sizeof (APOB_MEM_DMI_PHYSICAL_DIMM) + sizeof (APOB_MEM_DMI_LOGICAL_DIMM)))
  #define ABL_MEM_NVDIMM_INFO_SIZE (sizeof (APOB_MEM_NVDIMM_INFO_STRUCT))
  #define ABL_APOB_APCB_BOOT_INFO_SIZE (sizeof (APOB_APCB_BOOT_INFO_STRUCT))
  #define MAX_MASTER_APOB_SIZE ABL_APOB_HEADER_SIZE + ABL_MEM_GEN_ERROR_SIZE + ABL_MEM_GEN_CONFIG_SIZE + ABL_GEN_INFO_SIZE + ABL_S3_RESTORE_DATA_SIZE + ABL_MEM_PMU_SMB_SIZE + ABL_CCX_LOGICAL_TO_PHYSICAL_MAP_SIZE + ABL_EVENT_LOG_SIZE + ABL_MEM_SMBIOS_INFO_SIZE + ABL_S3_PHY_RESTORE_DATA_SIZE + ABL_MEM_NVDIMM_INFO_SIZE
  #define MAX_SLAVE_APOB_SIZE (MAX_MASTER_APOB_SIZE - ABL_APOB_HEADER_SIZE)
  #define MAX_APOB_SIZE MAX_MASTER_APOB_SIZE + MAX_SLAVE_APOB_SIZE*ABL_APOB_MAX_SOCKETS_SUPPORTED*ABL_APOB_MAX_DIES_PER_SOCKET
  #define COMMON_INFO_ARRAY_OFFSET  ABL_APOB_HEADER_SIZE + ABL_SYS_MAP_SIZE


// APOB Group Definitons
#define APOB_MEM      1
#define APOB_DF       2
#define APOB_CCX      3
#define APOB_GNB      4
#define APOB_FCH      5
#define APOB_PSP      6
#define APOB_GEN      7
#define APOB_SMBIOS   8
#define APOB_FABRIC   9

// APOB Type Definitons
#define APOB_MEM_GENERAL_ERRORS_TYPE   1
#define APOB_MEM_GENERAL_CONFIGURATION_INFO_TYPE   2
#define APOB_GEN_CONFIGURATION_INFO_TYPE   3
#define APOB_GEN_S3_REPLAY_BUFFER_INFO_TYPE   4
#define APOB_MEM_PMU_SMB_TYPE   5
#define APOB_GEN_EVENT_LOG_TYPE   6
#define APOB_MEM_DIMM_SMBUS_INFO_TYPE   7
#define APOB_MEM_SMBIOS_TYPE  8
#define APOB_SYS_MAP_INFO_TYPE   9
#define APOB_MEM_S3_DDR_PHY_REPLAY_PHASE1_BUFFER_INFO_TYPE   10
#define APOB_MEM_S3_DDR_PHY_REPLAY_PHASE2_BUFFER_INFO_TYPE   11
#define APOB_MEM_S3_DDR_PHY_REPLAY_PHASE3_BUFFER_INFO_TYPE   12
#define APOB_MEM_S3_DDR_PHY_REPLAY_PHASE4_BUFFER_INFO_TYPE   13
#define APOB_MEM_S3_DDR_PHY_REPLAY_PHASE5_BUFFER_INFO_TYPE   14
#define APOB_MEM_NVDIMM_INFO_TYPE   15
#define APOB_APCB_BOOT_INFO_TYPE    16
#define APOB_MEM_DIMM_SPD_DATA_TYPE     17
#define APOB_MEM_MBIST_RESULT_INFO_TYPE 18

// APOB CCX Type Definitons
#define APOB_CCX_LOGICAL_TO_PHYSICAL_MAP_TYPE  1
#define APOB_CCX_EDC_THROTTLE_THRESH_TYPE      2



#define APOB_SYS_MAP_STRUCT_SIZE sizeof (SYSTEM_MEMORY_MAP) + (9 * sizeof (MEMORY_HOLE_DESCRIPTOR))


/// AMD APOB_HEADER Header
typedef struct {
  APOB_BASE_HEADER  Header;
  UINT32   SysMapOffset;              ///< System Map Info [Master Only]
  UINT32   MemSmbiosOffset;           ///< Memory SMBIOS Buffer Type Offset [Master Only]
  UINT32   NvdimmInfoOffset;
  UINT32   ApobApcbBootInfoOffset;    ///< APOB Boot Info to report RecoveryFlag and ActiveInstance
  UINT32   MemConfigOffset[ABL_APOB_MAX_SOCKETS_SUPPORTED*ABL_APOB_MAX_DIES_PER_SOCKET];    ///< Memory Configuration Buffer Type Offset
  UINT32   MemErrorOffset[ABL_APOB_MAX_SOCKETS_SUPPORTED*ABL_APOB_MAX_DIES_PER_SOCKET];    ///< Memory Error Buffer Type Offset
  UINT32   GenConfigOffset[ABL_APOB_MAX_SOCKETS_SUPPORTED*ABL_APOB_MAX_DIES_PER_SOCKET];    ///< General Configuration Buffer Type Offset
  UINT32   ReplayBuffOffset[ABL_APOB_MAX_SOCKETS_SUPPORTED*ABL_APOB_MAX_DIES_PER_SOCKET];    ///< Replay Buffer Offset
  UINT32   MemPmuSmbOffset[ABL_APOB_MAX_SOCKETS_SUPPORTED*ABL_APOB_MAX_DIES_PER_SOCKET];    ///< Memroy PMU SMB Offset
  UINT32   CcxLogToPhysMapOffset[ABL_APOB_MAX_SOCKETS_SUPPORTED*ABL_APOB_MAX_DIES_PER_SOCKET];    ///< CCX Map Offset
  UINT32   CcxEdcThrottleThreshOffset[ABL_APOB_MAX_SOCKETS_SUPPORTED*ABL_APOB_MAX_DIES_PER_SOCKET];    ///< CCX EDC Threshold Offset
  UINT32   EventLogOffset[ABL_APOB_MAX_SOCKETS_SUPPORTED*ABL_APOB_MAX_DIES_PER_SOCKET];    ///< Event log Offset
  UINT32   MemSpdDataOffset[ABL_APOB_MAX_SOCKETS_SUPPORTED*ABL_APOB_MAX_DIES_PER_SOCKET];           ///< Memory SPD data Buffer Type Offset
  UINT32   DdrPhyReplayBuffPhase1Offset[ABL_APOB_MAX_SOCKETS_SUPPORTED*ABL_APOB_MAX_DIES_PER_SOCKET];    ///< DDR Phy Replay Buffer Offset
  UINT32   DdrPhyReplayBuffPhase2Offset[ABL_APOB_MAX_SOCKETS_SUPPORTED*ABL_APOB_MAX_DIES_PER_SOCKET];    ///< DDR Phy Replay Buffer Offset
  UINT32   DdrPhyReplayBuffPhase3Offset[ABL_APOB_MAX_SOCKETS_SUPPORTED*ABL_APOB_MAX_DIES_PER_SOCKET];    ///< DDR Phy Replay Buffer Offset
  UINT32   DdrPhyReplayBuffPhase4Offset[ABL_APOB_MAX_SOCKETS_SUPPORTED*ABL_APOB_MAX_DIES_PER_SOCKET];    ///< DDR Phy Replay Buffer Offset
  UINT32   DdrPhyReplayBuffPhase5Offset[ABL_APOB_MAX_SOCKETS_SUPPORTED*ABL_APOB_MAX_DIES_PER_SOCKET];    ///< DDR Phy Replay Buffer Offset
  UINT32   ApobMbistTestResultsOffset[ABL_APOB_MAX_SOCKETS_SUPPORTED*ABL_APOB_MAX_DIES_PER_SOCKET];      ///< MBIST Test Results
  APOB_HMAC ApobHeaderHmac;                    ///< Hmac location for type
} APOB_HEADER;

/// LOCAL APOB Data
typedef struct {
  UINT32   LocalApobSize;                              ///< APOB Size
  UINT32   ApobStart;                     ///< Start of the APOB Data (Includes Header for Master, but not for slave)
  UINT32   MemConfigOffset;    ///< Memory Configuration Buffer Type Offset
  UINT32   MemErrorOffset;    ///< Memory Error Buffer Type Offset
  UINT32   GenConfigOffset;    ///< General Configuration Buffer Type Offset
  UINT32   ReplayBuffOffset;    ///< Replay Buffer Type Offset
  UINT32   MemPmuSmbOffset;    ///< Memroy PMU SMB Offset
  UINT32   ApobMbistTestResultsOffset;   ///< APOB MBIST test results
  UINT32   CcxLogToPhysMapOffset; ///< CCX Map Offset
  UINT32   CcxEdcThrottleThreshOffset; ///< CCX EDC Throttle Threshold Info Offset
  UINT32   EventLogOffset;    ///< Event log Offset
  UINT32   MemSmbiosOffset;    ///< Memory SMBIOS Buffer Type Offset
  UINT32   SysMapOffset;      ///< System Map Offset
  UINT32   MemSpdDataOffset;   ///<  Memory SPD Data OFfset
  UINT32   DdrPhyReplayBuffPhase1Offset; ///< DDR Phy Replay Buffer Type Offset
  UINT32   DdrPhyReplayBuffPhase2Offset; ///< DDR Phy Replay Buffer Type Offset
  UINT32   DdrPhyReplayBuffPhase3Offset; ///< DDR Phy Replay Buffer Type Offset
  UINT32   DdrPhyReplayBuffPhase4Offset; ///< DDR Phy Replay Buffer Type Offset
  UINT32   DdrPhyReplayBuffPhase5Offset; ///< DDR Phy Replay Buffer Type Offset
  UINT32   NvdimmInfoOffset;   ///< Nvdimm Info offset  
  UINT32   ApobApcbBootInfoOffset;       ///< ApobApcbBootInfo Offset
} LOCAL_APOB_DATA;


/// AMD APOB_TYPE ENTRY
typedef struct {
  APOB_TYPE_HEADER typeHeader;              ///< APOB Type header
  UINT32  *Source;                          ///< Enyry Source
  UINT32  Destination;                      ///< Entry Destination
} APOB_TYPE_ENTRY;

/// AMD APOB_MEM_GENERAL_ERRORS Header
typedef struct {
  APOB_TYPE_HEADER  ApobTypeHeader;    ///< APOB Type Header
	BOOLEAN GsbMTRRshort;             ///< Ran out of MTRRs while mapping memory
  BOOLEAN GsbAllECCDimms;            ///< All banks of all Nodes are ECC capable
  BOOLEAN GsbDramECCDis;             ///< Dram ECC requested but not enabled.
  BOOLEAN GsbSoftHole;               ///< A Node Base gap was created
  BOOLEAN GsbHWHole;                 ///< A HW dram remap was created
  BOOLEAN GsbNodeIntlv;              ///< Node Memory interleaving was enabled
  BOOLEAN GsbSpIntRemapHole;         ///< Special condition for Node Interleave and HW remapping
  BOOLEAN GsbEnDIMMSpareNW;          ///< Indicates that DIMM Spare can be used without a warm reset
} APOB_MEM_GENERAL_ERRORS_TYPE_STRUCT;

typedef struct _APOB_MBIST_MARGIN {
  UINT8  PositiveEdge;
  UINT8  NegativeEdge;
} APOB_MBIST_MARGIN;

typedef struct _APOB_MBIST_DATA_EYE_MARGIN {
  APOB_MBIST_MARGIN  ReadDqDelay;    ///< Smallest Positive and Negative Read Dq Delay margin
  APOB_MBIST_MARGIN  ReadVref;       ///< Smallest Positive and Negative Read Vref delay
  APOB_MBIST_MARGIN  WriteDqDelay;   ///< Smallest Positive and Negative Write Dq Delay margin
  APOB_MBIST_MARGIN  WriteVref;      ///< Smallest Positive and Negative Write Vref delay
} APOB_MBIST_DATA_EYE_MARGIN;

typedef struct _APOB_MBIST_DATA_EYE_RECORD {
  BOOLEAN                      DataEyeValid;
  APOB_MBIST_DATA_EYE_MARGIN   DataEyeRecord;
} APOB_MBIST_DATA_EYE_RECORD;

#define APOB_MBIST_SUBTESTS 5

/// AMD MBIST STATUS STRUCTURE Header
typedef struct {
  APOB_TYPE_HEADER  ApobTypeHeader;                                   ///< APOB Type Header
  UINT8           ResultValid [APOB_MBIST_SUBTESTS][ABL_APOB_MAX_CHANNELS_PER_DIE];   ///< ErrorStatus valid per Chip Select
                                                                                      ///<    For Each Bit, 0...3
                                                                                      ///<      0 = Chip select was not tested
                                                                                      ///<      1 = Chip select was tested
                                                                                      ///<    Bits 7:4 Reserved
  UINT8           ErrorStatus [APOB_MBIST_SUBTESTS][ABL_APOB_MAX_CHANNELS_PER_DIE];   ///< Error Status per Chip Select
                                                                                      ///<    For Each Bit, 0...3
                                                                                      ///<      0 = Chip select Passed
                                                                                      ///<      1 = Chip Select Failed
                                                                                      ///<    Bits 7:4 Reserved
  APOB_MBIST_DATA_EYE_RECORD  ApobDataEyeRecord[ABL_APOB_MAX_CHANNELS_PER_DIE][ABL_APOB_MAX_CS_PER_CHANNEL];
} APOB_MBIST_STATUS_TYPE_STRUCT;

/// AMD APOB_GEN_CONFIGURATION_INFO Header

//-----------------------------------------------------------------------------
///
/// DDR Post Package Repair
///
#define APOB_STATUS_REPAIR_FAIL 0                      ///< Repair failed
#define APOB_STATUS_REPAIR_PASS 1                      ///< Repair was successful
#define APOB_STATUS_REPAIR_RANK_MISS_MATCH_ERROR 2     ///< Repair Error, Rank is valid, but did not match an installed rank
#define APOB_STATUS_REPAIR_RANK_INVALID_ERROR 4        ///< Repair Error, Rank is not valid
#define APOB_STATUS_REPAIR_BANK_INVALID_ERROR  8       ///< Repair Error, Bank is not valid
#define APOB_STATUS_REPAIR_SOCKET_INVALID_ERROR   0x10 ///< Repair Error, Socket is not valid
#define APOB_STATUS_REPAIR_CHANNEL_INVALID_ERROR  0x20 ///< Repair Error, Channel is not valid
#define APOB_STATUS_REPAIR_DEVICE_INVALID_ERROR   0x40 ///< Repair Error, Device is not valid
#define APOB_STATUS_REPAIR_DEVICE_MISSMATCH_ERROR 0x80 ///< Repair Error, Device missmatch
#define APOB_DPPR_VALID_REPAIR 1
#define APOB_DPPR_INVALID_REPAIR 0
#define APOB_DPPR_SOFT_REPAIR 0
#define APOB_DPPR_HARD_REPAIR 1
#define APOB_DPPR_RESULTS_VALID 1
#define APOB_DPPR_RESULTS_INVALID 0
#define APOB_MAX_DPPRCL_ENTRY 32
#define APOB_MAX_DPPRCL_SOCKETS 1
#define APOB_MAX_DPPRCL_CHANNELS 1
#define APOB_MAX_DPPRCL_ENTRIES APOB_MAX_DPPRCL_SOCKETS*APOB_MAX_DPPRCL_CHANNELS


typedef struct DPPRCL_REPAIR_REPORT_ENTRY {
  UINT32 Valid:1;                       ///< [0:0] Valid entry
  UINT32 Status:8;                      ///< [8:1] Status
  UINT32 Type:1;                        ///< [8:1] Repair Type
  UINT32 DpprPresent:1;                 ///< DPPR Present
  UINT32 SpprPresent:1;                 ///< SPPR Present
  UINT32 Reserved:20;                   ///< Reserved
} DPPRCL_REPAIR_REPORT_ENTRY;

typedef struct _APOB_DPPRCL_STRUCT{
  DPPRCL_REPAIR_REPORT_ENTRY DppRclReportEntry[APOB_MAX_DPPRCL_ENTRY];
} APOB_DPPRCL_STRUCT;

typedef struct _APOB_DPPR_STRUCT {
  BOOLEAN  PprResultsValid;          /// Indicates that the PPR results are valid
  UINT8    Reserved;
  UINT16    Reserved1;
  APOB_DPPRCL_STRUCT Channel[APOB_MAX_DPPRCL_ENTRIES];
} APOB_DPPR_STRUCT;

typedef union {
  /// Bitfields of Configuration Address Control Register
  struct {
    UINT32 ChannelIntlv:8;              ///< Bit map for channel interleave setting
    UINT32 DieIntlv:2;                  ///< Bit map for die interleave setting
    UINT32 SocketIntlv:1;               ///< Socket interleave setting
    UINT32 :21;                         ///< Reserved
  } Field;
  UINT32  Value;
} INTLV_SETTING;

typedef struct {
  APOB_TYPE_HEADER  ApobTypeHeader;                     ///< APOB Type Header
  UINT32 BootMediaTypeInfo;                             ///< BootMediaTypeInfo
  UINT16 MemClkFreq;                                    ///< Data from MemClkFreq: 667/800/933/1067/1200/1333/1467/1600 Mhz
  UINT16 DdrMaxRate;                                    ///< UMC DdrMaxRate
  BOOLEAN EccEnable [ABL_APOB_MAX_CHANNELS_PER_DIE];    ///< ECC enabled or Disabled per channel. ie. Channel 0 or Channel 1
  BOOLEAN NvDimmInstalled[ABL_APOB_MAX_CHANNELS_PER_DIE]; ///< NVDIMM presence per channel. ie. Channel 0 or Channel 1
  BOOLEAN ChannelIntlvEn;                               ///< DIMM channel interleave status
  UINT8  Reserved1[7];
  APOB_DPPR_STRUCT DdrPostPackageRepair;  ///< DDR Post package repaair
  OUT
  UINT32 MemCtrllerProcOdtDddr4Current;    ///< Proc ODT current value set by APCB
  OUT
  UINT32 MemCtrllerRttNomDddr4Current;    ///< RTT NOM current value set by APCB
  OUT
  UINT32 MemCtrllerRttWrDddr4Current;    ///< RTT WR current value set by APCB
  OUT
  UINT32 MemCtrllerRttParkDddr4Current;    ///< RTT PARK current value set by APCB
  OUT
  UINT32 MemCtrllerAddrCmdSetupDddr4Current;    ///< Addr Cmd Setup current value set by APCB
  OUT
  UINT32 MemCtrllerCsOdtSetupDddr4Current;    ///< Cs ODT Setup current value set by APCB
  OUT
  UINT32 MemCtrllerCkeSetupDddr4Current;    ///< Cke Setup current value set by APCB
  OUT
  UINT32 MemCtrllerCadBusClkDrvStrenDddr4Current;    ///< CAD Bus Clk Drv Strength current value set by APCB
  OUT
  UINT32 MemCtrllerCadBusAddrCmdDrvStrenDddr4Current;    ///< CAD Bus Addr Cmd Drv Strength current value set by APCB
  OUT
  UINT32 MemCtrllerCsOdtCmdDrvStrenDddr4Current;    ///< Cs Odt Drv Strength current value set by APCB
  OUT
  UINT32 MemCtrllerCkeDrvStrenDddr4Current;        ///< Cke Drv Strength current value set by APCB    
  OUT
  INTLV_SETTING InterLeaveCurrentMode;   ///< Current interleave mode
  OUT
  INTLV_SETTING InterLeaveCapability;    ///< Capability of interleave
  OUT
  UINT32 InterLeaveSize;
} APOB_MEM_GENERAL_CONFIGURATION_INFO_TYPE_STRUCT;

/// DDR4 DIMM ID information
typedef struct {
  UINT16 DimmManId;     ///< DIMM manufacturer ID
  UINT16 DimmModId;       ///< DIMM Module ID
  UINT16 Page1SpdChecksumLow;       ///< DIMM checksum for lower 128 bytes
  UINT16 Page1SpdChecksumHigh;       ///< DIMM checksum for upper 128 bytes
  BOOLEAN DimmPresentInConfig;  ///< Indicates that the DIMM config is present
  UINT8  Reserved[3];
} DIMM_APOB_OPT_ID;
/// AMD APOB_GEN_INFO_PARAMETER_INFO_STRUCT
/// This structure passes parameter information from ABL cold to ABL Warm/Resume
typedef struct {
  IN
  UINT32  ApobUniqueApcbInstance; ///< UniuweApcbInstance to ensure
                                  ///< (ABL internal use for warm reset data xfer)
                                  ///< compatibitly for giveen flshed BIOS lifecycle
  IN
  BOOLEAN ApobAblRestoreControl;     ///< This field indicates if ABL should perform a restore
  IN
  UINT8 Reserved; ///< Reserved for alignment
  UINT32 Reserved1; ///< Reserved for alignment
} APOB_GEN_INFO_PARAMETER_INFO_STRUCT;

/// AMD APOB_GEN_INFO_ERROR_INFO_STRUCT
/// This structure passes Error information from ABL cold to ABL Warm/Resume
typedef struct {
  BOOLEAN ApobErrorReportPortReportingEnable;  ///< Indicates if ABL will report errors via a port
                                               ///< (ABL internal use for resume/warm reset data xfer)
                                               ///< TRUE - Error logging will be reported via a port
                                               ///< FALSE - Error logging will not be reported via a port
  IN
  BOOLEAN  ApobErrorReportUsingHandshakeEnable;  ///< This flag indicates if the ABL will use an handshake for the Error Log
                                                 ///< (ABL internal use for resume/warm reset data xfer)
                                                 ///< TRUE - Error log reported using a handshake with the "ErrorLogOutputPort" and "ErrorLogInputPort"
                                                 ///< FALSE - Error log reported using "ErrorLogOutputPort" only with each DWORD in log delayed by
                                                 ///<         ErrorLogOutputDwordDelay
  OUT
  UINT16 Reserved1; ///< Reserved for alignment
  IN
  UINT32  ApobErrorReportInputPort;              ///< Input Port to receive ABL Error information
                                                 ///< (ABL internal use for resume/warm reset data xfer)
                                                 ///< (only valid if ReportErrorLogUsingHandshakeEnable = TRUE)
  IN
  UINT32  ApobErrorReportOutputDwordDelay;       ///< Number of "10ns" to wait before sending the next Log Dword informaiton via "ErrorLogOutputPort"
                                                 ///< (ABL internal use for resume/warm reset data xfer)
                                                 ///< (only valid if ReportErrorLogUsingHandshakeEnable = FALSE)
  IN
  UINT32  ApobErrorReportOutputPort;             ///< Output Port for ABL Error information
                                                 ///< (ABL internal use for resume/warm reset data xfer)
  IN
  BOOLEAN ApobErrorReportStopOnFirstFatalErrorEnable; ///< Indicates that ABL will stop on the first fatal error
                                                      ///< (ABL internal use for resume/warm reset data xfer)
                                                      ///< TRUE - Stop and report the first FATAL error
                                                      ///< FALSE - Report all errors
  OUT
  UINT8 Reserved2; ///< Reserved for alignment
  OUT
  UINT16 Reserved3; ///< Reserved for alignment
  IN
  UINT32  ApobErrorReportInputPortSize;         ///< Indicates the size of the input and outut port
                                                ///< (ABL internal use for resume/warm reset data xfer)
                                                ///< 1 - 8 bit port
                                                ///< 2 - 16 bit port
                                                ///< 4 - 32 bit port
  IN
  UINT32  ApobErrorReportOutputPortSize;        ///< Indicates the size of the input and outut port
                                                ///< (ABL internal use for resume/warm reset data xfer)                                              ///< 1 - 8 bit port
                                                ///< 2 - 16 bit port
                                                ///< 4 - 32 bit port
  IN
  UINT32  ApobErrorReportInputPortType;         ///< Indicates the type of Input Port or location of the port
                                                ///< 0 - PCIE HT0
	                                              ///< 2 - PCIE HT1
	                                              ///< 5 - PCIE MMIO
	                                              ///< 6 - FCH_HT_IO (Default)
	                                              ///< 7 - FCH_MMIO
  IN
  UINT32  ApobErrorReportOutputPortType;        ///< Indicates the type of Output Port or location of the port
                                                ///< 0 - PCIE HT0
	                                              ///< 2 - PCIE HT1
	                                              ///< 5 - PCIE MMIO
	                                              ///< 6 - FCH_HT_IO (Default)
	                                              ///< 7 - FCH_MMIO
  IN
  BOOLEAN  ApobErrorReportClearAcknowledgement;   ///< Indicates if the ABL will clear acknolgements during protocol
                                                  ///< (ABL internal use for resume/warm reset data xfer)
                                                  ///< TRUE - Clear acknowledgemetns
                                                  ///< FALSE - Do not clear acknologements
  IN
  BOOLEAN ApobErrorLogHeartBeatEnable;             ///< Indicates if ABL will provide periodic status to a port as a heart beat
                                                   ///< TRUE - Heartbeat Error log will be reported via a port
                                                   ///< FALSE - Heartbeat Error log will not be reported via a port
                                                   ///<
                                                   ///< Notes:
                                                   ///<   1) This feature is only valid if ErrorLogPortReportingEnable
                                                   ///<   2) This is can be mono-directional or bi-directional based on "ErrorLogReportUsingHandshakeEnable"
                                                   ///<        "ErrorLogReportUsingHandshakeEnable" = TRUE - bi-directional
                                                   ///<        "ErrorLogReportUsingHandshakeEnable" = FALSE - mono-directional
                                                   ///<   3) Requires the following to be defined:
                                                   ///<    - "ErrorLogReportInputPortType", "ErrorLogInputPort, "ErrorLogReportInputPortSize" 
                                                   ///<    - "ErrorLogReportInputPortType", "ErrorLogInputPort, "ErrorLogReportInputPortSize"                                                    
} APOB_GEN_INFO_ERROR_INFO_STRUCT;

/// Memory DMI Type 17 - for memory use
typedef struct {
  OUT UINT8                     Socket:2;               ///< Socket ID
  OUT UINT8                     Channel:3;              ///< Channel ID
  OUT UINT8                     Dimm:2;                 ///< DIMM ID
  OUT UINT8                     DimmPresent:1;          ///< Dimm Present
  OUT UINT8                     SpdAddr;                ///< SPD Address
  OUT UINT16                    Handle;                 ///< The temporary handle, or instance number, associated with the structure
  OUT UINT16                    ConfigSpeed;            ///< Configured memory clock speed
  OUT UINT16                    ConfigVoltage;          ///< Configured voltage for this device, in millivolt
} APOB_MEM_DMI_PHYSICAL_DIMM;

/// Memory DMI Type 20 - for memory use
typedef struct {
  OUT UINT8                     Socket:2;               ///< Socket ID
  OUT UINT8                     Channel:3;              ///< Channel ID
  OUT UINT8                     Dimm:2;                 ///< DIMM ID
  OUT UINT8                     DimmPresent:1;          ///< Dimm Present
  OUT UINT8                     Interleaved:1;          ///< Interleaving enabled
  OUT UINT8                     Reserved:7;
  OUT UINT16                    MemoryDeviceHandle;     ///< The handle, or instance number, associated with
                                                        ///< the Memory Device structure to which this address
                                                        ///< range is mapped.
  OUT UINT32                    StartingAddr;           ///< The physical address, in kilobytes, of a range
                                                        ///< of memory mapped to the referenced Memory Device.
  OUT UINT32                    EndingAddr;             ///< The handle, or instance number, associated with
                                                        ///< the Memory Device structure to which this address
                                                        ///< range is mapped.
  union {
    OUT UINT64                  ExtStartingAddr;        ///< The physical address, in bytes, of a range of
                                                        ///< memory mapped to the referenced Memory Device.
    struct {
      OUT UINT32                ExtStartingAddrLow;
      OUT UINT32                ExtStartingAddrHigh;
    } ExtStartingAddrForPsp;
  } UnifiedExtStartingAddr;
  union {
    OUT UINT64                  ExtEndingAddr;          ///< The physical ending address, in bytes, of the last of
                                                        ///< a range of addresses mapped to the referenced Memory Device.
    struct {
      OUT UINT32                ExtEndingAddrLow;
      OUT UINT32                ExtEndingAddrHigh;
    } ExtEndingAddrForPsp;
  } UnifiedExtEndingAddr;
} APOB_MEM_DMI_LOGICAL_DIMM;

/// APOB Memory DMI entry header
typedef struct {
  APOB_TYPE_HEADER ApobTypeHeader;                     ///< APOB Type header
  UINT8            MemoryType:7;                       ///< Memory Type
  UINT8            EccCapable:1;                       ///< ECC Capable
  UINT8            MaxPhysicalDimms;                   ///< Maximum physical DIMMs
  UINT8            MaxLogicalDimms;                    ///< Maximum logical DIMMs
  UINT8            Reserved;
} APOB_MEM_DMI_HEADER;

/// APOB Memory DMI entry
typedef union {
  struct {
    APOB_MEM_DMI_HEADER Header;                          ///< APOB Type header
    APOB_MEM_DMI_PHYSICAL_DIMM  PhysDimm[1];             ///< Memory Type
    APOB_MEM_DMI_LOGICAL_DIMM   LogDimm[1];              ///< Memory Type
  } Fields;
  UINT8             WorstCase[ABL_MEM_SMBIOS_INFO_SIZE];
} APOB_MEM_DMI_INFO_STRUCT;

/// Event log entry
typedef struct {
  UINT32    EventClass;   ///< The severity of the event, its associated AGESA_STATUS.
  UINT32    EventInfo;        ///< Uniquely identifies the event.
  UINT32    DataA;
  UINT32    DataB;
} APOB_ERROR_LOG;

typedef struct {
  APOB_ERROR_LOG AgesaEvent[MAX_APOB_ERROR_ENTRIES];    ///< The entry itself.
} AGESA_EVENT_STRUCT;

typedef struct {
  APOB_TYPE_HEADER  ApobTypeHeader;    ///< APOB Type Header
  UINT16        Count;           ///< The total number of active entries.
  AGESA_EVENT_STRUCT ApobEventStruct;   ///< The entries.
} EVENT_LOG_STRUCT;

#define MAX_APOB_MEM_NB_BLOCK_SIZE 1500
#define MAX_APOB_MEM_DCT_BLOCK_SIZE  150
#define MAX_APOB_MEM_TIMINGS_BLOCK_SIZE 130
#define MAX_APOB_MEM_CHANNEL_BLOCK_SIZE  450
#define MAX_APOB_MEM_DIE_BLOCK_SIZE 150
/// AMD APOB_GEN_CONFIGURATION_INFO Header
typedef struct {
  APOB_TYPE_HEADER  ApobTypeHeader;    ///< APOB Type Header
  OUT
	UINT32 Bootmode; ///< Bootmode detected by ABL.
  OUT
  BOOLEAN EmulationEnv; ///< Emulation Environment detected by ABL.
  OUT
  BOOLEAN SimulationEnv; ///< Simulation Environment detected by ABL.
  OUT
  UINT16 Reserved; ///< Reserved for alignment
  IN
  APOB_GEN_INFO_ERROR_INFO_STRUCT ApobErrorInfo; ///< APOB error information
  APOB_GEN_INFO_PARAMETER_INFO_STRUCT ApobParamInfo; ///< APOB parameter information
  EVENT_LOG_STRUCT   ApobEventLog;     ///< APOB event log
  UINT8 MemNbBlock[MAX_APOB_MEM_NB_BLOCK_SIZE];    ///> Memory NB block buffer
  UINT8 MemDct0Block[MAX_APOB_MEM_DCT_BLOCK_SIZE];    ///> Memory DCT0 block buffer
  UINT8 MemDct1Block[MAX_APOB_MEM_DCT_BLOCK_SIZE];    ///> Memory DCT1 block buffer
  UINT8 MemTimings0Block[MAX_APOB_MEM_TIMINGS_BLOCK_SIZE];    ///> Memory Timings0 block buffer
  UINT8 MemTimings1Block[MAX_APOB_MEM_TIMINGS_BLOCK_SIZE];    ///> Memory Timings1 block buffer
  UINT8 MemChannel0Block[MAX_APOB_MEM_CHANNEL_BLOCK_SIZE];    ///> Memory Channel0 block buffer
  UINT8 MemChannel1Block[MAX_APOB_MEM_CHANNEL_BLOCK_SIZE];    ///> Memory Channel1 block buffer
  UINT8 MemDieBlock[MAX_APOB_MEM_DIE_BLOCK_SIZE];    ///> Memory Die block buffer
} APOB_GEN_INFO_TYPE_STRUCT;

/// AMD APOB_PMU_SMB_STRUCT Header
typedef struct {
  IN
  UINT8 ApobPmuSmb[MAX_PMU_SMB_SIZE]; ///< APOB PMU SMB
} APOB_PMU_SMB_STRUCT;


/// AMD APOB_PMU_SMB_TYPE_STRUCT Header
typedef struct {
  APOB_TYPE_HEADER  ApobTypeHeader;    ///< APOB Type Header
  IN
  APOB_PMU_SMB_STRUCT ApobPmuSmb; ///< APOB PMU SMB
} APOB_PMU_SMB_TYPE_STRUCT;

#define CCX_MAX_SOCKETS            ABL_APOB_MAX_SOCKETS_SUPPORTED
#define CCX_MAX_DIES_PER_SOCKET    ABL_APOB_MAX_DIES_PER_SOCKET
#define CCX_MAX_COMPLEXES_PER_DIE  2  // Program dependent
#define CCX_MAX_CORES_PER_COMPLEX  4  // Fixed for Zen
#define CCX_MAX_THREADS_PER_CORE   2  // Fixed for Zen

typedef struct {
  UINT8    PhysCoreNumber;
  BOOLEAN  IsThreadEnabled[CCX_MAX_THREADS_PER_CORE];
} LOGICAL_CORE_INFO;

typedef struct {
  UINT8              PhysComplexNumber;
  LOGICAL_CORE_INFO  CoreInfo[CCX_MAX_CORES_PER_COMPLEX];
} LOGICAL_COMPLEX_INFO;

/// AMD APOB_CCX_LOGICAL_TO_PHYSICAL_MAP_TYPE Header
typedef struct {
  APOB_TYPE_HEADER      ApobTypeHeader;    ///< APOB Type Header
  LOGICAL_COMPLEX_INFO  ComplexMap[CCX_MAX_COMPLEXES_PER_DIE];
} APOB_CCX_LOGICAL_TO_PHYSICAL_MAP_TYPE_STRUCT;

/// AMD SYSTEM_MEMORY_MAP Header
typedef enum {
  UMA,                        ///< UC DRAM cycles.  I don't think this is needed in SoC15 since HBM is not part of the system map
  MMIO,                       ///< Cycles are sent out to IO.  Only expect the 1 below 4GB
  PrivilegedDRAM,             ///< Read-only zero.  No special cache considerations are needed.  Map out of E820
  MaxMemoryHoleTypes,         ///< Not a valid type.  Used for validating the others.
} MEMORY_HOLE_TYPES;

typedef struct {
  UINT64             Base;    ///< Full 64 bit base address of the hole
  UINT64             Size;    ///< Size in bytes of the hole
  MEMORY_HOLE_TYPES  Type;    ///< Hole type
} MEMORY_HOLE_DESCRIPTOR;

typedef struct {
  UINT64                  TopOfSystemMemory;  ///< Final DRAM byte address in the system + 1
  UINT32                  NumberOfHoles;      ///< SoC15 systems will always have at least one
  MEMORY_HOLE_DESCRIPTOR  HoleInfo[1];        ///< Open ended array of descriptors
} SYSTEM_MEMORY_MAP;

/// AMD APOB_SYSTEM_MEMORY_MAP_TYPE_STRUCT Header
typedef struct {
  APOB_TYPE_HEADER  ApobTypeHeader;    ///< APOB Type Header
  OUT
  SYSTEM_MEMORY_MAP   ApobSystemMap;     ///< APOB event log
  MEMORY_HOLE_DESCRIPTOR  AdditionalHoleInfo[9];
} APOB_SYSTEM_MEMORY_MAP_TYPE_STRUCT;

/// S3 Support

//#define MAX_REPLAY_BUFFER_ENTRIES 0x400ul
#define MAX_REPLAY_BUFFER_ENTRIES 0x659ul
//#define MAX_S3_DDR_PHY_REG_LIST 0x250ul
#define MAX_S3_DDR_PHY_REG_LIST 0x3A0ul

/// Entry for the S3 replay buffer.
typedef struct {
  _4BYTE_ALIGN UINT32 Address; ///< Register address 
  _4BYTE_ALIGN UINT32 Value; ///< Register value
} REPLAY_BUFFER_ENTRY;

/// Entry for the S3 DDR Phy Buffer
typedef struct {
  _2BYTE_ALIGN UINT16 Value; ///< Register value
} DDR_PHY_BUFFER_ENTRY;


/// Entry for the S3 DDR Phy Buffer
typedef struct {
  UINT32 CurrEntryNum;  ///< Current DDR Phy Entry Number
  BOOLEAN LogEn; ///< Enables or disables logging for DDR Phy Entries
  BOOLEAN ChannelEnable[ABL_APOB_MAX_CHANNELS_PER_DIE]; ///< Channels enabled
  UINT16 Reserved; ///< Reserved
  DDR_PHY_BUFFER_ENTRY Entry[MAX_S3_DDR_PHY_REG_LIST]; ///< DDR Phy Buffer
} DDR_PHY_BUFFER;

/// General replay for the S3 DDR Phy Buffer
typedef struct {
  BOOLEAN LogEn;  ///< Enables or dislables logging to replay buffer
  UINT8 Reserved0; ///< Reserved
  UINT16 Reserved1; ///< Reserved
  UINT32 CurrPhyEntryNum; ///< Current Phy entry number
  UINT32 CurrEntryNum; ///< Current Entry Number 
  UINT32 StartEntryNum; //< Start Entry 
  UINT32 StopFlag; //< Stop Flag
  BOOLEAN ChannelEnable[ABL_APOB_MAX_CHANNELS_PER_DIE]; ///< Channels enabled
  UINT16 Reserved2; ///< Reserved
  REPLAY_BUFFER_ENTRY Entry[MAX_REPLAY_BUFFER_ENTRIES];  ///< Replay Buffer
} GEN_REPLAY_BUFFER;

/* Device related definitions */

/// Replay buffer.
typedef struct {
  _4BYTE_ALIGN UINT32 Version; ///< Version of header
  UINT32 StopValue;          ///< Stop Value
  GEN_REPLAY_BUFFER ReplayBuff; ///< General Replay Buffer
} REPLAY_BUFFER;

typedef struct {
  APOB_TYPE_HEADER  ApobTypeHeader;    ///< APOB Type Header
  REPLAY_BUFFER   ReplayData;
} APOB_REPLAY_BUFFER_TYPE_STRUCT;

typedef struct {
  APOB_TYPE_HEADER  ApobTypeHeader;    ///< APOB Type Header
  UINT8  PhyReplayData[MAX_SIZE_PHY_REPLAY_BUFFER];
} APOB_REPLAY_BUFFER_PHY_TYPE_STRUCT;

//-----------------------------------------------------------------------------
/// APOB_MEM_DIMM_SPD_DATA_STRUCT
typedef struct {
  APOB_TYPE_HEADER  ApobTypeHeader;
  UINT8 MaxDimmsPerChannel;
  UINT8 MaxChannelsPerSocket;
  APOB_SPD_STRUCT   DimmSmbusInfo[ABL_APOB_MAX_CHANNELS_PER_DIE * ABL_APOB_MAX_DIMMS_PER_CHANNEL];     ///<
} APOB_MEM_DIMM_SPD_DATA_STRUCT;

// Definition for APOB EDC throttle thresholds
typedef struct {
  APOB_TYPE_HEADER        ApobTypeHeader;
  UINT32                  NumberOfValidThresholds;
  EDC_THROTTLE_THRESHOLD  Thresholds[MAX_NUMBER_OF_THROTTLERS];
} APOB_EDC_THROTTLE_THRESHOLD_INFO_STRUCT;

typedef struct {
  APOB_MEM_GENERAL_CONFIGURATION_INFO_TYPE_STRUCT  MemGeneralCfg;
  APOB_MEM_GENERAL_ERRORS_TYPE_STRUCT              MemGeneralErrors;
  APOB_GEN_INFO_TYPE_STRUCT                        GeneralInfo;
  APOB_REPLAY_BUFFER_TYPE_STRUCT                   S3ReplayData;
  APOB_PMU_SMB_TYPE_STRUCT                         PmuSmb;
  APOB_MBIST_STATUS_TYPE_STRUCT                    MbistTestResults;
  APOB_CCX_LOGICAL_TO_PHYSICAL_MAP_TYPE_STRUCT     CcxMap;
  APOB_EDC_THROTTLE_THRESHOLD_INFO_STRUCT          CcxEdcThrottleThreshInfo;
  EVENT_LOG_STRUCT                                 EventLog;
  APOB_MEM_DIMM_SPD_DATA_STRUCT                    SpdData;
  APOB_REPLAY_BUFFER_PHY_TYPE_STRUCT               S3ReplayPhy1Data;
  APOB_REPLAY_BUFFER_PHY_TYPE_STRUCT               S3ReplayPhy2Data;
  APOB_REPLAY_BUFFER_PHY_TYPE_STRUCT               S3ReplayPhy3Data;
  APOB_REPLAY_BUFFER_PHY_TYPE_STRUCT               S3ReplayPhy4Data;
  APOB_REPLAY_BUFFER_PHY_TYPE_STRUCT               S3ReplayPhy5Data;
} APOB_COMMON_DIE_DATA;

typedef struct {
  APOB_TYPE_HEADER  ApobTypeHeader;
  UINT32    NvdimmInfo[ABL_APOB_MAX_SOCKETS_SUPPORTED * ABL_APOB_MAX_CHANNELS_PER_SOCKET * ABL_APOB_MAX_DIMMS_PER_CHANNEL][2];
  BOOLEAN   NvdimmPresentInSystem;
  UINT8     Reserved[7];
} APOB_MEM_NVDIMM_INFO_STRUCT;

// Defintion for APOB Boot Info to pass RecoveryFlag and ApcbInstance
typedef struct {
  APOB_TYPE_HEADER  ApobTypeHeader;
  UINT32    ApcbActiveInstance;          ///< APCB Active Insatnce of the boot
  DIMM_APOB_OPT_ID CurrentBootDimmIdInfo[ABL_APOB_MAX_SOCKETS_SUPPORTED][ABL_APOB_MAX_CHANNELS_PER_SOCKET][ABL_APOB_MAX_DIMMS_PER_CHANNEL];           ///< DIMM Identification informaion for the current boot
  BOOLEAN DimmConfigurationUpdated;       //< FALSE - DIMM Configuration not updated, 
                                         //< TRUE - DIMM Configuration updated
  UINT8     ApcbRecoveryFlag;            ///< APCB Recovery Flag
  UINT8     Reserved [2];                ///< Reserved for alignment
} APOB_APCB_BOOT_INFO_STRUCT;

typedef struct {
  APOB_SYSTEM_MEMORY_MAP_TYPE_STRUCT  SystemMemoryMap;
  APOB_MEM_DMI_INFO_STRUCT            SystemDmiInfo;
  APOB_MEM_NVDIMM_INFO_STRUCT         NvdimmInfo;
  APOB_APCB_BOOT_INFO_STRUCT          ApobApcbBootInfo;
} APOB_GLOBAL_DATA;

typedef struct {
  APOB_HEADER           Header;
  APOB_GLOBAL_DATA      GlobalData;
  APOB_COMMON_DIE_DATA  CommonDieData[(ABL_APOB_MAX_SOCKETS_SUPPORTED * ABL_APOB_MAX_DIES_PER_SOCKET)];
} APOB_DATA;

//-----------------------------------------------------------------------------
///
/// SPD Data for each DIMM.
///
typedef struct _APOB_DIMM_INFO_SMBUS {
  UINT8  MemoryLayoutType;    ///< Memory Layout Type, if 0 = SpdLayout  1= Onboard Layout
  UINT8  DimmSlotPresent;     ///< Indicates that the DIMM is present and Data is valid
  UINT8  SocketId;            ///< Indicates the socket number
  UINT8  ChannelId;           ///< Indicates the channel number
  UINT8  DimmId;              ///< Indicates the channel number
  UINT8  DimmSmbusAdderess;   ///< SMBus address of the DRAM
  UINT8  I2CMuxAddress;       ///< I2C Mux Address
  UINT8  MuxChannel;          ///< I2C Mux Channel assocaited iwth this SPD
} APOB_DIMM_INFO_SMBUS;
/// APOB_MEM_DIMM_SMBUS_INFO_TYPE
typedef struct {
  APOB_TYPE_HEADER  ApobTypeHeader;
  UINT32            totalEntry;
  APOB_DIMM_INFO_SMBUS   DimmSmbusInfo[ABL_APOB_MAX_SOCKETS_SUPPORTED * ABL_APOB_MAX_CHANNELS_PER_SOCKET * ABL_APOB_MAX_DIMMS_PER_CHANNEL];     ///<
} APOB_MEM_DIMM_SMBUS_INFO_TYPE_STRUCT;

#endif  /* _APOB_H_ */

