/* $NoKeywords:$ */
/**
 * @file
 *
 * Agesa structures and definitions
 *
 * Contains Definitions required for ApcbGenerator
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  ApcbcGenerator
 * @e \$Revision: 276922 $   @e \$Date: 2014-10-29 12:38:41 -0600 (Tue, 29 Oct 2013) $
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


#ifndef _MISC_MEM_DEFINES_H_
#define _MISC_MEM_DEFINES_H_

#include  <MyPorting.h>

// AGESA ADVANCED CALLOUTS, Memory
#define AGESA_READ_SPD                 0x00028140ul
/// Configuration values for memory phy voltage (VDDR)
#define  VOLT0_95   0                 ///< VDDR 0.95V
#define  VOLT1_05   1                 ///< VDDR 1.05V
#define  MAX_VDDR   2                 ///< Maxmum value for this enum definition

//
//  MEMORY-SPECIFIC DATA STRUCTURES
//
//
//
//
// AGESA MAXIMIUM VALUES
//
//   These Max values are used to define array sizes and associated loop
//   counts in the code.  They reflect the maximum values that AGESA
//   currently supports and does not necessarily reflect the hardware
//   capabilities of configuration.
//

#define MAX_SOCKETS_SUPPORTED   1   ///< Max number of sockets in system
#define MAX_CHANNELS_PER_SOCKET 2  ///< Max Channels per sockets
#define MAX_DIMMS_PER_CHANNEL   2   ///< Max DIMMs on a memory channel (independent of platform)
#define NUMBER_OF_DELAY_TABLES  9   ///< Number of tables defined in CH_DEF_STRUCT.
                                    ///< Eg: UINT16  *RcvEnDlys;
                                    ///<     UINT8   *WrDqsDlys;
                                    ///<     UINT8   *RdDqsDlys;
                                    ///<     UINT8   *WrDatDlys;
                                    ///<     UINT8   *RdDqsMinDlys;
                                    ///<     UINT8   *RdDqsMaxDlys;
                                    ///<     UINT8   *WrDatMinDlys;
                                    ///<     UINT8   *WrDatMaxDlys;
#define NUMBER_OF_FAILURE_MASK_TABLES 1 ///< Number of failure mask tables

#define MAX_PLATFORM_TYPES     16   ///< Platform types per system

#define MCT_TRNG_KEEPOUT_START  0x00004000ul    ///< base [39:8]
#define MCT_TRNG_KEEPOUT_END    0x00007FFFul    ///< base [39:8]
#define DATAEYE_VREF_RANGE     31   ///< Number of VREF steps in Data Eye Bitmap

#define UMA_ATTRIBUTE_INTERLEAVE 0x80000000ul   ///< Uma Region is interleaved
#define UMA_ATTRIBUTE_ON_DCT0    0x40000000ul   ///< UMA resides on memory that belongs to DCT0
#define UMA_ATTRIBUTE_ON_DCT1    0x20000000ul   ///< UMA resides on memory that belongs to DCT1
#define UMA_ATTRIBUTE_ON_DCT2    0x10000000ul   ///< UMA resides on memory that belongs to DCT2
#define UMA_ATTRIBUTE_ON_DCT3    0x08000000ul   ///< UMA resides on memory that belongs to DCT3

typedef UINT8 PSO_TABLE;            ///< Platform Configuration Table

//        AGESA DEFINITIONS
//
//        Many of these are derived from the platform and hardware specific definitions

/// EccSymbolSize override value
#define ECCSYMBOLSIZE_USE_BKDG      0   ///< Use BKDG Recommended Value
#define ECCSYMBOLSIZE_FORCE_X4      4   ///< Force to x4
#define ECCSYMBOLSIZE_FORCE_X8      8   ///< Force to x8
/// CPU Package Type
#define PT_L1       0                 ///< L1 Package type
#define PT_M2       1                 ///< AM Package type
#define PT_S1       2                 ///< S1 Package type

/// Build Configuration values for BLDCFG_MEMORY_BUS_FREQUENCY_LIMIT & BLDCFG_MEMORY_CLOCK_SELECT
#define DDR400_FREQUENCY  200     ///< DDR 400
#define DDR533_FREQUENCY  266     ///< DDR 533
#define DDR667_FREQUENCY  333     ///< DDR 667
#define DDR800_FREQUENCY  400     ///< DDR 800
#define DDR1066_FREQUENCY 533     ///< DDR 1066
#define DDR1333_FREQUENCY 667     ///< DDR 1333
#define DDR1600_FREQUENCY 800     ///< DDR 1600
#define DDR1866_FREQUENCY 933     ///< DDR 1866
#define DDR2100_FREQUENCY 1050    ///< DDR 2100
#define DDR2133_FREQUENCY 1067    ///< DDR 2133
#define DDR2400_FREQUENCY 1200    ///< DDR 2400
#define DDR2667_FREQUENCY 1333    ///< DDR 2667
#define DDR2800_FREQUENCY 1400    ///< DDR 2800
#define DDR2933_FREQUENCY 1467    ///< DDR 2933
#define DDR3066_FREQUENCY 1533    ///< DDR 3066
#define DDR3200_FREQUENCY 1600    ///< DDR 3200
#define DDR3333_FREQUENCY 1667    ///< DDR 3333
#define DDR3466_FREQUENCY 1733    ///< DDR 3466
#define DDR3600_FREQUENCY 1800    ///< DDR 3600
#define DDR3733_FREQUENCY 1867    ///< DDR 3733
#define DDR3866_FREQUENCY 1933    ///< DDR 3866
#define DDR4000_FREQUENCY 2000    ///< DDR 4000
#define DDR4200_FREQUENCY 2100    ///< DDR 4200
#define DDR4267_FREQUENCY 2133    ///< DDR 4267
#define DDR4333_FREQUENCY 2167    ///< DDR 4333
#define DDR4400_FREQUENCY 2200    ///< DDR 4400
#define UNSUPPORTED_DDR_FREQUENCY 2201 ///< Highest limit of DDR frequency

/// Build Configuration values for BLDCFG_TIMING_MODE_SELECT
#define TIMING_MODE_AUTO     0  ///< Use best rate possible
#define TIMING_MODE_LIMITED  1  ///< Set user top limit
#define TIMING_MODE_SPECIFIC 2  ///< Set user specified speed

/// Build Configuration values for BLDCFG_MEMORY_QUADRANK_TYPE
#define QUADRANK_REGISTERED  0  ///< Quadrank registered DIMM
#define QUADRANK_UNBUFFERED  1  ///< Quadrank unbuffered DIMM

/// Build Configuration values for BLDCFG_POWER_DOWN_MODE
#define POWER_DOWN_BY_CHANNEL      0  ///< Channel power down mode
#define POWER_DOWN_BY_CHIP_SELECT  1  ///< Chip select power down mode
#define POWER_DOWN_MODE_AUTO       2  ///< AGESA to select power down mode

/// Structures use to pass system Logical CPU-ID
typedef struct {
  IN OUT   UINT32 Family;             ///< Indicates logical ID Family
  IN OUT   UINT16 Revision;           ///< Indicates logical ID Revision
} SOC_LOGICAL_ID;

/// Structures use to report AMP status
typedef struct {
  OUT   BOOLEAN AmpVoltageValid;                 ///< Indicates if Amp voltage is valid
  OUT   BOOLEAN AmpSupportDetectedButNotEnabled; ///< Indicates if Amp support is detected but not enabled
  OUT   BOOLEAN AmpSelectedButNotEnabled;        ///< Indicates if Amp is selected but not enabled
} AMP_STATUS;

/// Normalized Critical Composite Data Eye
///  Bit 15 represents trained eye Center
///  Bit 0  represents eye center -15 delay steps
///  Bit 31 represents eye center +16 delay steps
///  Offset 0  represents +15 Vref Steps
///  Offset 31  represents -15 Vref Steps
typedef UINT32 COMPOSITE_DATAEYE[DATAEYE_VREF_RANGE];

/// Build Configuration values for BLDCFG_AMD_PLATFORM_TYPE
typedef enum {
  AMD_PLATFORM_SERVER = 0x8000,     ///< Server
  AMD_PLATFORM_DESKTOP = 0x10000,   ///< Desktop
  AMD_PLATFORM_MOBILE = 0x20000,    ///< Mobile
} AMD_PLATFORM_TYPE;
#if 0
/// Dram technology type
typedef enum {
  DDR2_TECHNOLOGY,        ///< DDR2 technology
  DDR3_TECHNOLOGY,        ///< DDR3 technology
  GDDR5_TECHNOLOGY,       ///< GDDR5 technology
  DDR4_TECHNOLOGY,        ///< DDR4 technology
  LPDDR3_TECHNOLOGY,      ///< LPDDR3 technology
  UNSUPPORTED_TECHNOLOGY, ///< Unsupported technology
} TECHNOLOGY_TYPE;

/// Dram technology type
typedef enum {
  SODIMM_PACKAGE,        ///< SODIMM package
  UDIMM_PACKAGE,         ///< UDIMM Package
  RDIMM_PACKAGE,         ///< RDIMM Package
  DRAMDOWN_PACKAGE,      ///< DRAM Down Package
  UNSUPPORTED_PACKAGE,   ///< Unsupported package
} DRAM_PACKAGE_TYPE;
#endif 
/// Low voltage support
typedef enum {
  VOLT_INITIAL,                     ///< Initial value for VDDIO
  VOLT1_5,                          ///< 1.5 Volt
  VOLT1_35,                         ///< 1.35 Volt
  VOLT1_25,                         ///< 1.25 Volt
  VOLT_DDR4_RANGE_START,            ///< Start of DDR4 Voltage Range
  VOLT1_2 = VOLT_DDR4_RANGE_START,  ///< 1.2 Volt
  VOLT1_TBD1,                       ///< TBD1 Voltage
  VOLT1_TBD2,                       ///< TBD2 Voltage
  VOLT_UNSUPPORTED = 0xFF           ///< No common voltage found
} DIMM_VOLTAGE;

/// AMP voltage support
typedef enum {
  AMP_VOLT_RSVD,             ///< Reserved
  AMP_VOLT1_5,               ///< 1.5 Volt
  AMP_VOLT1_55,              ///< 1.55 Volt
  AMP_VOLT1_6,               ///< 1.6 Volt
  AMP_VOLT1_65,              ///< 1.65 Volt
  AMP_VOLT1_7,               ///< 1.7 Volt
  AMP_VOLT1_75,              ///< 1.75 Volt
  AMP_VOLT1_8,               ///< 1.8 Volt
  AMP_VOLT1_85,              ///< 1.85 Volt
  AMP_VOLT1_9,               ///< 1.9 Volt
  AMP_VOLT1_45 = 0x10,       ///< 1.45 Volt
  AMP_VOLT1_4  = 0x20,       ///< 1.4 Volt
  AMP_VOLT1_35 = 0x30,       ///< 1.35 Volt
  AMP_VOLT1_3  = 0x40,       ///< 1.3 Volt
  AMP_VOLT1_25 = 0x50,       ///< 1.25 Volt
  AMP_VOLT1_2  = 0x60        ///< 1.2 Volt
} AMP_DIMM_VOLTAGE;

/// Build Configuration values for BLDCFG_ACP_SIZE
typedef enum {
  NO_ACP_SIZE = 0x00,        ///< NO ACP
  ACP_SIZE_2MB = 0x20,       ///< UMA 4MB aligned
  ACP_SIZE_4MB = 0x40,       ///< UMA 128MB aligned
} ACP_SIZE;

/// UMA Version
typedef enum {
  UMA_LEGACY = 0,              ///< UMA Legacy Version
  UMA_NON_LEGACY = 1           ///< UMA Non Legacy Version
} UMA_VERSION;

/// UMA Mode
typedef enum {
  UMA_NONE = 0,              ///< UMA None
  UMA_SPECIFIED = 1,         ///< UMA Specified
  UMA_AUTO = 2               ///< UMA Auto
} UMA_MODE;

/// Force Training Mode
typedef enum {
  FORCE_TRAIN_1D = 0,              ///< 1D Training only
  FORCE_TRAIN_2D = 1,              ///< 2D Training only
  FORCE_TRAIN_AUTO = 2             ///< Auto - 1D or 2D depending on configuration
} FORCE_TRAIN_MODE;

/// PMU Training Mode
typedef enum {
  PMU_TRAIN_1D = 0,                ///< PMU 1D Training only
  PMU_TRAIN_1D_2D_READ = 1,        ///< PMU 1D and 2D Training read only
  PMU_TRAIN_1D_2D_WRITE = 2,       ///< PMU 1D and 2D Training write only
  PMU_TRAIN_1D_2D = 3,             ///< PMU 1D and 2D Training
  PMU_TRAIN_AUTO = 0xFF            ///< Auto - PMU Training depend on configuration
} PMU_TRAIN_MODE;

///  The possible DRAM prefetch mode settings.
typedef enum  {
  DRAM_PREFETCHER_AUTO,                         ///< Use the recommended setting for the processor. In most cases, the recommended setting is enabled.
  DISABLE_DRAM_PREFETCH_FOR_IO,                 ///< Disable DRAM prefetching for I/O requests only.
  DISABLE_DRAM_PREFETCH_FOR_CPU,                ///< Disable DRAM prefetching for requests from processor cores only.
  DISABLE_DRAM_PREFETCHER,                      ///< Disable DRAM prefetching.
  MAX_DRAM_FREFETCH_MODE                        ///< Not a DRAM prefetch mode, use for limit checking.
} DRAM_PREFETCH_MODE;

/// Build Configuration values for BLDCFG_UMA_ALIGNMENT
typedef enum {
  NO_UMA_ALIGNED = 0x00FFFFFF,           ///< NO UMA aligned
  UMA_4MB_ALIGNED = 0x00FFFFC0,          ///< UMA 4MB aligned
  UMA_128MB_ALIGNED = 0x00FFF800,        ///< UMA 128MB aligned
  UMA_256MB_ALIGNED = 0x00FFF000,        ///< UMA 256MB aligned
  UMA_512MB_ALIGNED = 0x00FFE000,        ///< UMA 512MB aligned
} UMA_ALIGNMENT;

///
///   Global MCT Configuration Status Word (GStatus)
///
typedef enum {
  GsbMTRRshort,              ///< Ran out of MTRRs while mapping memory
  GsbAllECCDimms,            ///< All banks of all Nodes are ECC capable
  GsbDramECCDis,             ///< Dram ECC requested but not enabled.
  GsbSoftHole,               ///< A Node Base gap was created
  GsbHWHole,                 ///< A HW dram remap was created
  GsbNodeIntlv,              ///< Node Memory interleaving was enabled
  GsbSpIntRemapHole,         ///< Special condition for Node Interleave and HW remapping
  GsbEnDIMMSpareNW,          ///< Indicates that DIMM Spare can be used without a warm reset

  GsbEOL                     ///< End of list
} GLOBAL_STATUS_FIELD;

///
///   Local Error Status (DIE_STRUCT.ErrStatus[31:0])
///
typedef enum {
  EsbNoDimms,                  ///< No DIMMs
  EsbSpdChkSum,                ///< SPD Checksum fail
  EsbDimmMismatchM,            ///< dimm module type(buffer) mismatch
  EsbDimmMismatchT,            ///< dimm CL/T mismatch
  EsbDimmMismatchO,            ///< dimm organization mismatch (128-bit)
  EsbNoTrcTrfc,                ///< SPD missing Trc or Trfc info
  EsbNoCycTime,                ///< SPD missing byte 23 or 25
  EsbBkIntDis,                 ///< Bank interleave requested but not enabled
  EsbDramECCDis,               ///< Dram ECC requested but not enabled
  EsbSpareDis,                 ///< Online spare requested but not enabled
  EsbMinimumMode,              ///< Running in Minimum Mode
  EsbNoRcvrEn,                 ///< No DQS Receiver Enable pass window found
  EsbSmallRcvr,                ///< DQS Rcvr En pass window too small (far right of dynamic range)
  EsbNoDqsPos,                 ///< No DQS-DQ passing positions
  EsbSmallDqs,                 ///< DQS-DQ passing window too small
  EsbDCBKScrubDis,             ///< DCache scrub requested but not enabled

  EsbEMPNotSupported,          ///< Processor is not capable for EMP.
  EsbEMPConflict,               ///< EMP requested but cannot be enabled since
                               ///< channel interleaving, bank interleaving, or bank swizzle is enabled.
  EsbEMPDis,                   ///< EMP requested but cannot be enabled since
                               ///< memory size of each DCT is not a power of two.
  EsbDimmTechMismatchM,         ///< Technology type mismatch
  EsbEOL                       ///< End of list
} ERROR_STATUS_FIELD;

///
///  Local Configuration Status (DIE_STRUCT.Status[31:0])
///
typedef enum {
  SbRegistered,                ///< All DIMMs are Registered
  SbEccDimms,                  ///< All banks ECC capable
  SbParDimms,                  ///< All banks Addr/CMD Parity capable
  SbDiagClks,                  ///< Jedec ALL slots clock enable diag mode
  Sb128bitmode,                ///< DCT in 128-bit mode operation
  Sb64MuxedMode,               ///< DCT in 64-bit mux'ed mode.
  Sb2TMode,                    ///< 2T CMD timing mode is enabled.
  SbSWNodeHole,                ///< Remapping of Node Base on this Node to create a gap.
  SbHWHole,                    ///< Memory Hole created on this Node using HW remapping.
  SbOver400Mhz,                ///< DCT freq greater than or equal to 400MHz flag
  SbDQSPosPass2,               ///< Used for TrainDQSPos DIMM0/1, when freq greater than or equal to 400MHz
  SbDQSRcvLimit,               ///< Used for DQSRcvEnTrain to know we have reached the upper bound.
  SbExtConfig,                 ///< Indicate the default setting for extended PCI configuration support
  SbLrdimms,                   ///< All DIMMs are LRDIMMs

  SbEOL                        ///< End of list
} LOCAL_STATUS_FIELD;


///< CPU MSR Register definitions ------------------------------------------
#define SYS_CFG     0xC0010010ul
#define TOP_MEM     0xC001001Aul
#define TOP_MEM2    0xC001001Dul
#define HWCR        0xC0010015ul
#define NB_CFG      0xC001001Ful

#define FS_BASE     0xC0000100ul
#define IORR0_BASE  0xC0010016ul
#define IORR0_MASK  0xC0010017ul
#define BU_CFG      0xC0011023ul
#define BU_CFG2     0xC001102Aul
#define COFVID_STAT 0xC0010071ul
#define TSC         0x10


#if 0 //for SPD stuff
//-----------------------------------------------------------------------------
///
/// SPD Data for each DIMM.
///
typedef struct _SPD_DEF_STRUCT {
  BOOLEAN SpdValid;					///< Indicates that the SPD is valid
  BOOLEAN DimmPresent;				///< Indicates that the DIMM is present and Data is valid
  UINT8   PageAddress;				///< Indicates the 256 Byte EE Page the data belongs to
									///<      0 = Lower Page
									///<      1 = Upper Page (DDR4 Only)
  UINT32 Adderess;					/// SMBus address of the DRAM
 TECHNOLOGY_TYPE  Technology;		///< Indicates the type of Technology used in SPD
									///<   DDR3_TECHNOLOGY = Use DDR3 DIMMs
									///<   DDR4_TECHNOLOGY = Use DDR4 DIMMs
									///<   LPDDR3_TECHNOLOGY = Use LPDDR3
  DRAM_PACKAGE_TYPE  Package;		///< Indicates the package type
									///<   SODIMM_PACKAGE = SODIMM package
									///<   UDIMM_PACKAGE = UDIMM Package
									///<   RDIMM_PACKAGE = RDIMM Package
									///<   DRAMDOWN_PACKAGE = DRAM Down Package
 UINT8  SocketNumber;				///< Indicates the socket number
 //UINT8  DieId;						///< Die Info
 UINT8  ChannelNumber;				///< Indicates the channel number
 UINT8  DimmNumber;					///< Indicates the channel number
 UINT8 Data[256];					///< Buffer for 256 Bytes of SPD data from DIMM
} SPD_DEF_STRUCT;
#endif

//-----------------------------------------------------------------------------
///
/// VDDP_VDDR Voltage Info for Low Power DIMM
///
typedef struct _VDDP_VDDR_VOLTAGE {
  IN BOOLEAN IsValid;               ///< Indicates if daata is valid
  IN UINT8 Voltage;    ///< VDDP VDDR Voltage Value
} VDDP_VDDR_VOLTAGE;
#if 0
///
/// Channel Definition Structure.
/// This data structure defines entries that are specific to the channel initialization
///
typedef struct _CH_DEF_STRUCT {
  OUT UINT8   ChannelID;         ///< Physical channel ID of a socket(0 = CH A, 1 = CH B, 2 = CH C, 3 = CH D)
  OUT TECHNOLOGY_TYPE TechType;  ///< Technology type of this channel
  OUT UINT8   ChDimmPresent;     ///< For each bit n 0..7, 1 = DIMM n is present.
                                 ///<  DIMM#  Select Signal
                                 ///<  0      MA0_CS_L[0, 1]
                                 ///<  1      MB0_CS_L[0, 1]
                                 ///<  2      MA1_CS_L[0, 1]
                                 ///<  3      MB1_CS_L[0, 1]
                                 ///<  4      MA2_CS_L[0, 1]
                                 ///<  5      MB2_CS_L[0, 1]
                                 ///<  6      MA3_CS_L[0, 1]
                                 ///<  7      MB3_CS_L[0, 1]

  OUT struct _DCT_STRUCT *DCTPtr; ///< Pointer to the DCT data of this channel.
  OUT struct _DIE_STRUCT *MCTPtr; ///< Pointer to the node data of this channel.
  OUT SPD_DEF_STRUCT *SpdPtr;    ///< Pointer to the SPD data for this channel. (Setup by NB Constructor)
  OUT SPD_DEF_STRUCT *DimmSpdPtr[MAX_DIMMS_PER_CHANNEL]; ///< Array of pointers to
                                 ///<   SPD Data for each Dimm. (Setup by Tech Block Constructor)
  OUT UINT8   ChDimmValid;       ///< For each bit n 0..3, 1 = DIMM n is valid and is/will be configured where 4..7 are reserved.
                                 ///<
  OUT UINT8   RegDimmPresent;   ///< For each bit n 0..3, 1 = DIMM n is a registered DIMM where 4..7 are reserved.
  OUT UINT8   LrDimmPresent;     ///< For each bit n 0..3, 1 = DIMM n is Load Reduced DIMM where 4..7 are reserved.
  OUT UINT8   SODimmPresent;     ///< For each bit n 0..3, 1 = DIMM n is a SO-DIMM, where 4..7 are reserved.
  OUT UINT8   Loads;             ///< Number of devices loading bus
  OUT UINT8   Dimms;             ///< Number of DIMMs loading Channel
  OUT UINT8   Ranks;             ///< Number of ranks loading Channel DATA
  OUT BOOLEAN SlowMode;          ///< 1T or 2T CMD mode (slow access mode)
  OUT BOOLEAN SlowModePs1;       ///< 1T or 2T CMD mode (slow access mode) for Mem Pstate 1
                                 ///< FALSE = 1T
                                 ///< TRUE = 2T
  ///< The following pointers will be pointed to dynamically allocated buffers.
  ///< Each buffer is two dimensional (RowCount x ColumnCount) and is lay-outed as in below.
  ///< Example: If DIMM and Byte based training, then
  ///< XX is a value in Hex
  ///<                        BYTE 0, BYTE 1, BYTE 2, BYTE 3, BYTE 4, BYTE 5, BYTE 6, BYTE 7, ECC BYTE
  ///<  Row1 -  Logical DIMM0    XX      XX      XX      XX      XX      XX      XX      XX      XX
  ///<  Row2 -  Logical DIMM1    XX      XX      XX      XX      XX      XX      XX      XX      XX
  OUT UINT16  *RcvEnDlys;       ///< DQS Receiver Enable Delays
  OUT UINT8   *WrDqsDlys;       ///< Write DQS delays (only valid for DDR3)
  OUT UINT8   *RdDqsDlys;       ///< Read Dqs delays
  OUT UINT8   *WrDatDlys;       ///< Write Data delays
  OUT UINT8   *RdDqs2dDlys;     ///< 2d Read DQS data
  OUT UINT8   *RdDqsMinDlys;    ///< Minimum Window for Read DQS
  OUT UINT8   *RdDqsMaxDlys;    ///< Maximum Window for Read DQS
  OUT UINT8   *WrDatMinDlys;    ///< Minimum Window for Write data
  OUT UINT8   *WrDatMaxDlys;    ///< Maximum Window for Write data
  OUT UINT16  *RcvEnDlysMemPs1;       ///< DQS Receiver Enable Delays for Mem Pstate 1
  OUT UINT8   *WrDqsDlysMemPs1;       ///< Write DQS delays (only valid for DDR3) for Mem Pstate 1
  OUT UINT8   *RdDqsDlysMemPs1;       ///< Read Dqs delays for Memory Pstate 1
  OUT UINT8   *WrDatDlysMemPs1;       ///< Write Data delays for Memory Pstate 1
  OUT UINT8   *RdDqs2dDlysMemPs1;     ///< 2d Read DQS data for Memory Pstate 1
  OUT UINT8   *RdDqsMinDlysMemPs1;    ///< Minimum Window for Read DQS for Memory Pstate 1
  OUT UINT8   *RdDqsMaxDlysMemPs1;    ///< Maximum Window for Read DQS for Memory Pstate 1
  OUT UINT8   *WrDatMinDlysMemPs1;    ///< Minimum Window for Write data for Memory Pstate 1
  OUT UINT8   *WrDatMaxDlysMemPs1;    ///< Maximum Window for Write data for Memory Pstate 1
  OUT UINT8   RowCount;         ///< Number of rows of the allocated buffer.
  OUT UINT8   ColumnCount;      ///< Number of columns of the allocated buffer.
  OUT UINT8   *FailingBitMask;    ///< Table of masks to Track Failing bits
  OUT UINT8   *FailingBitMaskMemPs1;    ///< Table of masks to Track Failing bits for Memory Pstate 1
  OUT VOID    *RdDataEyes;        ///< Pointer to Read Data Eye Bitmaps
  OUT VOID    *WrDataEyes;        ///< Pointer to Write Data Eye Bitmaps
  OUT UINT32  DctOdcCtl;          ///< Output Driver Strength (see BKDG FN2:Offset 9Ch, index 00h)
  OUT UINT32  DctAddrTmg;         ///< Address Bus Timing (see BKDG FN2:Offset 9Ch, index 04h)
  OUT UINT32  DctAddrTmgPs1;      ///< Address Bus Timing (see BKDG FN2:Offset 9Ch, index 04h) for Mem Pstate 1
  OUT UINT32  PhyRODTCSLow;       ///< Phy Read ODT Pattern Chip Select low (see BKDG FN2:Offset 9Ch, index 180h)
  OUT UINT32  PhyRODTCSHigh;      ///< Phy Read ODT Pattern Chip Select high (see BKDG FN2:Offset 9Ch, index 181h)
  OUT UINT32  PhyWODTCSLow;       ///< Phy Write ODT Pattern Chip Select low (see BKDG FN2:Offset 9Ch, index 182h)
  OUT UINT32  PhyWODTCSHigh;      ///< Phy Write ODT Pattern Chip Select high (see BKDG FN2:Offset 9Ch, index 183)
  OUT UINT8   PhyWLODT[4];        ///< Write Levelization ODT Pattern for Dimm 0-3 or CS 0-7(see BKDG FN2:Offset 9Ch, index 0x8[11:8])
  OUT UINT16  DctEccDqsLike;      ///< DCT DQS ECC UINT8 like...
  OUT UINT8   DctEccDqsScale;     ///< DCT DQS ECC UINT8 scale
  OUT UINT16  PtrPatternBufA;     ///< Ptr on stack to aligned DQS testing pattern
  OUT UINT16  PtrPatternBufB;     ///< Ptr on stack to aligned DQS testing pattern
  OUT UINT8   ByteLane;           ///< Current UINT8 Lane (0..7)
  OUT UINT8   Direction;          ///< Current DQS-DQ training write direction (0=read, 1=write)
  OUT UINT8   Pattern;            ///< Current pattern
  OUT UINT8   DqsDelay;           ///< Current DQS delay value
  OUT UINT16  HostBiosSrvc1;      ///< UINT16 sized general purpose field for use by host BIOS.  Scratch space.
  OUT UINT32  HostBiosSrvc2;      ///< UINT32 sized general purpose field for use by host BIOS.  Scratch space.
  OUT UINT16  DctMaxRdLat[4];     ///< Max Read Latency (ns) for the DCT
                                  ///< DctMaxRdLat [i] is for NBPstate i
  OUT UINT8   DIMMValidCh;        ///< DIMM# in CH
  OUT UINT8   MaxCh;              ///< Max number of CH in system
  OUT UINT8   Dct;                ///< Dct pointer
  OUT UINT8   WrDatGrossH;        ///< Write Data Gross delay high value
  OUT UINT8   DqsRcvEnGrossL;     ///< DQS Receive Enable Gross Delay low

  OUT UINT8   TrwtWB;             ///<  Non-SPD timing value for TrwtWB
    OUT BOOLEAN Preamble2T;         ///< 2T Preamble
    OUT UINT8   CurrRcvrDctADelay;  ///< for keep current RcvrEnDly
  OUT UINT16  T1000;              ///< get the T1000 figure (cycle time (ns) * 1K)
  OUT UINT8   DqsRcvEnPass;       ///< for TrainRcvrEn UINT8 lane pass flag
  OUT UINT8   DqsRcvEnSaved;      ///< for TrainRcvrEn UINT8 lane saved flag
  OUT UINT8   SeedPass1Remainder; ///< for Phy assisted DQS receiver enable training

  OUT UINT8   ClToNbFlag;         ///< is used to restore ClLinesToNbDis bit after memory
  OUT UINT32  NodeSysBase;        ///< for channel interleave usage
  OUT UINT8   RefRawCard[MAX_DIMMS_PER_CHANNEL];   ///< Array of rawcards detected
  OUT UINT8   CtrlWrd02[MAX_DIMMS_PER_CHANNEL];    ///< Control Word 2 values per DIMM
  OUT UINT8   CtrlWrd03[MAX_DIMMS_PER_CHANNEL];    ///< Control Word 3 values per DIMM
  OUT UINT8   CtrlWrd04[MAX_DIMMS_PER_CHANNEL];    ///< Control Word 4 values per DIMM
  OUT UINT8   CtrlWrd05[MAX_DIMMS_PER_CHANNEL];    ///< Control Word 5 values per DIMM
  OUT UINT8   CtrlWrd08[MAX_DIMMS_PER_CHANNEL];    ///< Control Word 8 values per DIMM

  OUT UINT16  CsPresentDCT;       ///< For each bit n 0..7, 1 = Chip-select n is present
  OUT UINT8   DimmMirrorPresent;  ///< For each bit n 0..3, 1 = DIMM n is OnDimmMirror capable where 4..7 are reserved.
  OUT UINT8   DimmSpdCse;         ///< For each bit n 0..3, 1 = DIMM n SPD checksum error where 4..7 are reserved.
  OUT UINT8   DimmExclude;        ///< For each bit n 0..3, 1 = DIMM n gets excluded where 4..7 are reserved.
  OUT UINT8   DimmYr06;           ///< Bitmap indicating which Dimms have a manufacturer's year code <= 2006
  OUT UINT8   DimmWk2406;         ///< Bitmap indicating which Dimms have a manufacturer's week code <= 24 of 2006 (June)
  OUT UINT8   DimmPlPresent;      ///< Bitmap indicating that Planar (1) or Stacked (0) Dimms are present.
  OUT UINT8   DimmQrPresent;      ///< QuadRank DIMM present?
  OUT UINT8   DimmDrPresent;      ///< Bitmap indicating that Dual Rank Dimms are present
  OUT UINT8   DimmSRPresent;      ///< Bitmap indicating that Single Rank Dimms are present
  OUT UINT8   Dimmx4Present;      ///< For each bit n 0..3, 1 = DIMM n contains x4 data devices. where 4..7 are reserved.
  OUT UINT8   Dimmx8Present;      ///< For each bit n 0..3, 1 = DIMM n contains x8 data devices. where 4..7 are reserved.
  OUT UINT8   Dimmx16Present;     ///< For each bit n 0..3, 1 = DIMM n contains x16 data devices. where 4..7 are reserved.
  OUT UINT8   LrdimmPhysicalRanks[MAX_DIMMS_PER_CHANNEL];///< Number of Physical Ranks for LRDIMMs
  OUT UINT8   LrDimmLogicalRanks[MAX_DIMMS_PER_CHANNEL];///< Number of LRDIMM Logical ranks in this configuration
  OUT UINT8   LrDimmRankMult[MAX_DIMMS_PER_CHANNEL];///< Rank Multipication factor per dimm.
  OUT UINT8   DimmNibbleAccess;   ///< For each bit n 0..3, 1 = DIMM n will use nibble signaling. Where 4..7 are reserved.
  OUT UINT8   *MemClkDisMap;      ///<  This pointer will be set to point to an array that describes
                                  ///<  the routing of M[B,A]_CLK pins to the DIMMs' ranks. AGESA will
                                  ///<  base on this array to disable unused MemClk to save power.
                                  ///<
                                  ///<  The array must have 8 entries. Each entry, which associates with
                                  ///<  one MemClkDis bit, is a bitmap of 8 CS that that MemClk is routed to.
                                  ///<    Example:
                                  ///<    BKDG definition of Fn2x88[MemClkDis] bitmap for AM3 package
                                  ///<    is like below:
                                  ///<         Bit AM3/S1g3 pin name
                                  ///<         0   M[B,A]_CLK_H/L[0]
                                  ///<         1   M[B,A]_CLK_H/L[1]
                                  ///<         2   M[B,A]_CLK_H/L[2]
                                  ///<         3   M[B,A]_CLK_H/L[3]
                                  ///<         4   M[B,A]_CLK_H/L[4]
                                  ///<         5   M[B,A]_CLK_H/L[5]
                                  ///<         6   M[B,A]_CLK_H/L[6]
                                  ///<         7   M[B,A]_CLK_H/L[7]
                                  ///<    And platform has the following routing:
                                  ///<         CS0   M[B,A]_CLK_H/L[4]
                                  ///<         CS1   M[B,A]_CLK_H/L[2]
                                  ///<         CS2   M[B,A]_CLK_H/L[3]
                                  ///<         CS3   M[B,A]_CLK_H/L[5]
                                  ///<    Then MemClkDisMap should be pointed to the following array:
                                  ///<               CLK_2 CLK_3 CLK_4 CLK_5
                                  ///<    0x00, 0x00, 0x02, 0x04, 0x01, 0x08, 0x00, 0x00
                                  ///<  Each entry of the array is the bitmask of 8 chip selects.

  OUT UINT8   *CKETriMap;         ///<  This pointer will be set to point to an array that describes
                                  ///<  the routing of CKE pins to the DIMMs' ranks.
                                  ///<  The array must have 2 entries. Each entry, which associates with
                                  ///<  one CKE pin, is a bitmap of 8 CS that that CKE is routed to.
                                  ///<  AGESA will base on this array to disable unused CKE pins to save power.

  OUT UINT8   *ODTTriMap;         ///<  This pointer will be set to point to an array that describes
                                  ///<  the routing of ODT pins to the DIMMs' ranks.
                                  ///<  The array must have 4 entries. Each entry, which associates with
                                  ///<  one ODT pin, is a bitmap of 8 CS that that ODT is routed to.
                                  ///<  AGESA will base on this array to disable unused ODT pins to save power.

  OUT UINT8   *ChipSelTriMap;     ///<  This pointer will be set to point to an array that describes
                                  ///<  the routing of chip select pins to the DIMMs' ranks.
                                  ///<  The array must have 8 entries. Each entry is a bitmap of 8 CS.
                                  ///<  AGESA will base on this array to disable unused Chip select pins to save power.

  OUT BOOLEAN   ExtendTmp;        ///<  If extended temperature is supported on all dimms on a channel.

  OUT UINT8   DimmSRTPresent;     ///< For each bit n 0..3, 1 = DIMM n supports Extended Temperature Range where 4..7 are reserved
  OUT UINT8   DimmASRPresent;     ///< For each bit n 0..3, 1 = DIMM n supports Auto Self Refresh where 4..7 are reserved
  OUT UINT8   DimmThermSensorPresent;  ///< For each bit n 0..3, 1 = DIMM n has an On Dimm Thermal Sensor where 4..7 are reserved
  OUT UINT8   MaxVref;            ///<  Maximum Vref Value for channel

  OUT UINT8   Reserved[100];      ///< Reserved
} CH_DEF_STRUCT;

#endif

///
/// Uma Structure
///
///
typedef struct _UMA_INFO {
  OUT UINT64 UmaBase;          ///< UmaBase[63:0] = Addr[63:0]
  OUT UINT32 UmaSize;          ///< UmaSize[31:0] = Addr[31:0]
  OUT UINT32 UmaAttributes;    ///< Indicate the attribute of Uma
  OUT UINT8  UmaMode;          ///< Indicate the mode of Uma
  OUT UINT16 MemClock;         ///< Indicate memory running speed in MHz
  OUT UINT8  MemType;          ///< Indicate the DRAM technology type that is being used
  OUT UINT8  Reserved[2];      ///< Reserved for future usage
} UMA_INFO;


/// Bitfield for ID
typedef struct {
  OUT UINT16 SocketId:8;       ///< Socket ID
  OUT UINT16 ModuleId:8;       ///< Module ID
} ID_FIELD;
///
/// Union for ID of socket and module that will be passed out in call out
///
typedef union {
  OUT ID_FIELD IdField;         ///< Bitfield for ID
  OUT UINT16 IdInformation;     ///< ID information for call out
} ID_INFO;

//  AGESA MEMORY ERRORS

// AGESA_SUCCESS memory events
#define MEM_EVENT_CAPSULE_IN_EFFECT      0x04013600ul          ///< Capsule is in effect
#define MEM_EVENT_CONTEXT_RESTORE_IN_EFFECT     0x04023600ul   ///< Context restore is in effect

// AGESA_ALERT Memory Errors
#define MEM_ALERT_USER_TMG_MODE_OVERRULED   0x04010000ul       ///< TIMING_MODE_SPECIFIC is requested but
                                                               ///< cannot be applied to current configurations.
#define MEM_ALERT_ORG_MISMATCH_DIMM 0x04010100ul               ///< DIMM organization miss-match
#define MEM_ALERT_BK_INT_DIS 0x04010200ul                      ///< Bank interleaving disable for internal issue

// AGESA_ERROR Memory Errors
#define MEM_ERROR_NO_DQS_POS_RD_WINDOW 0x04010300ul            ///< No DQS Position window for RD DQS
#define MEM_ERROR_SMALL_DQS_POS_RD_WINDOW 0x04020300ul         ///< Small DQS Position window for RD DQS
#define MEM_ERROR_NO_DQS_POS_WR_WINDOW 0x04030300ul            ///< No DQS Position window for WR DQS
#define MEM_ERROR_SMALL_DQS_POS_WR_WINDOW 0x04040300ul         ///< Small DQS Position window for WR DQS
#define MEM_ERROR_DIMM_SPARING_NOT_ENABLED 0x04010500ul        ///< DIMM sparing has not been enabled for an internal issues
#define MEM_ERROR_RCVR_EN_VALUE_TOO_LARGE 0x04050300ul         ///< Receive Enable value is too large
#define MEM_ERROR_RCVR_EN_NO_PASSING_WINDOW 0x04060300ul       ///< There is no DQS receiver enable window
#define MEM_ERROR_DRAM_ENABLED_TIME_OUT 0x04010600ul           ///< Time out when polling DramEnabled bit
#define MEM_ERROR_DCT_ACCESS_DONE_TIME_OUT 0x04010700ul        ///< Time out when polling DctAccessDone bit
#define MEM_ERROR_SEND_CTRL_WORD_TIME_OUT 0x04010800ul         ///< Time out when polling SendCtrlWord bit
#define MEM_ERROR_PREF_DRAM_TRAIN_MODE_TIME_OUT 0x04010900ul   ///< Time out when polling PrefDramTrainMode bit
#define MEM_ERROR_ENTER_SELF_REF_TIME_OUT 0x04010A00ul         ///< Time out when polling EnterSelfRef bit
#define MEM_ERROR_FREQ_CHG_IN_PROG_TIME_OUT 0x04010B00ul       ///< Time out when polling FreqChgInProg bit
#define MEM_ERROR_EXIT_SELF_REF_TIME_OUT 0x04020A00ul          ///< Time out when polling ExitSelfRef bit
#define MEM_ERROR_SEND_MRS_CMD_TIME_OUT 0x04010C00ul           ///< Time out when polling SendMrsCmd bit
#define MEM_ERROR_SEND_ZQ_CMD_TIME_OUT 0x04010D00ul            ///< Time out when polling SendZQCmd bit
#define MEM_ERROR_DCT_EXTRA_ACCESS_DONE_TIME_OUT 0x04010E00ul  ///< Time out when polling DctExtraAccessDone bit
#define MEM_ERROR_MEM_CLR_BUSY_TIME_OUT 0x04010F00ul           ///< Time out when polling MemClrBusy bit
#define MEM_ERROR_MEM_CLEARED_TIME_OUT 0x04020F00ul            ///< Time out when polling MemCleared bit
#define MEM_ERROR_FLUSH_WR_TIME_OUT 0x04011000ul               ///< Time out when polling FlushWr bit
#define MEM_ERROR_NBPSTATE_TRANSITION_TIME_OUT 0x04012600ul    ///< Time out when polling CurNBPstate bit
#define MEM_ERROR_MAX_LAT_NO_WINDOW 0x04070300ul               ///< Fail to find pass during Max Rd Latency training
#define MEM_ERROR_PARALLEL_TRAINING_LAUNCH_FAIL 0x04080300ul   ///< Fail to launch training code on an AP
#define MEM_ERROR_PARALLEL_TRAINING_TIME_OUT 0x04090300ul      ///< Fail to finish parallel training
#define MEM_ERROR_NO_ADDRESS_MAPPING 0x04011100ul              ///< No address mapping found for a dimm
#define MEM_ERROR_RCVR_EN_NO_PASSING_WINDOW_EQUAL_LIMIT  0x040A0300ul ///< There is no DQS receiver enable window and the value is equal to the largest value
#define MEM_ERROR_RCVR_EN_VALUE_TOO_LARGE_LIMIT_LESS_ONE 0x040B0300ul ///< Receive Enable value is too large and is 1 less than limit
#define MEM_ERROR_CHECKSUM_NV_SPDCHK_RESTRT_ERROR  0x04011200ul       ///< SPD Checksum error for NV_SPDCHK_RESTRT
#define MEM_ERROR_NO_CHIPSELECT 0x04011300ul                   ///< No chipselects found
#define MEM_ERROR_UNSUPPORTED_333MHZ_UDIMM 0x04011500ul        ///< Unbuffered dimm is not supported at 333MHz
#define MEM_ERROR_WL_PRE_OUT_OF_RANGE 0x040C0300ul             ///< Returned PRE value during write levelizzation was out of range
#define MEM_ERROR_NO_2D_RDDQS_WINDOW 0x040D0300ul              ///< No 2D RdDqs Window
#define MEM_ERROR_NO_2D_RDDQS_HEIGHT 0x040E0300ul              ///< No 2D RdDqs Height
#define MEM_ERROR_2D_DQS_ERROR  0x040F0300ul                   ///< 2d RdDqs Error
#define MEM_ERROR_INVALID_2D_RDDQS_VALUE  0x04022400ul         ///< 2d RdDqs invalid value found
#define MEM_ERROR_2D_DQS_VREF_MARGIN_ERROR  0x04023400ul       ///< 2d RdDqs Vef Margin error found
#define MEM_ERROR_LR_IBT_NOT_FOUND  0x04013500ul               ///< No LR dimm IBT value is found
#define MEM_ERROR_MR0_NOT_FOUND  0x04023500ul                  ///< No MR0 value is found
#define MEM_ERROR_ODT_PATTERN_NOT_FOUND  0x04033500ul          ///< No odt pattern value is found
#define MEM_ERROR_RC2_IBT_NOT_FOUND  0x04043500ul              ///< No RC2 IBT value is found
#define MEM_ERROR_RC10_OP_SPEED_NOT_FOUND  0x04053500ul        ///< No RC10 op speed is found
#define MEM_ERROR_RTT_NOT_FOUND  0x04063500ul                  ///< No RTT value is found
#define MEM_ERROR_P2D_NOT_FOUND  0x04073500ul                  ///< No 2D training config value is found
#define MEM_ERROR_SAO_NOT_FOUND  0x04083500ul                  ///< No slow access mode, Address timing and Output driver compensation value is found
#define MEM_ERROR_CLK_DIS_MAP_NOT_FOUND  0x04093500ul          ///< No CLK disable map is found
#define MEM_ERROR_CKE_TRI_MAP_NOT_FOUND  0x040A3500ul          ///< No CKE tristate map is found
#define MEM_ERROR_ODT_TRI_MAP_NOT_FOUND  0x040B3500ul          ///< No ODT tristate map is found
#define MEM_ERROR_CS_TRI_MAP_NOT_FOUND  0x040C3500ul           ///< No CS tristate map is found
#define MEM_ERROR_TRAINING_SEED_NOT_FOUND  0x040D3500ul        ///< No training seed is found
#define MEM_ERROR_CAD_BUS_TMG_NOT_FOUND  0x040E3500ul          ///< No CAD Bus Timing Entries found
#define MEM_ERROR_DATA_BUS_CFG_NOT_FOUND  0x040F3500ul         ///< No Data Bus Config Entries found
#define MEM_ERROR_NO_2D_WRDAT_WINDOW 0x040D0400ul              ///< No 2D WrDat Window
#define MEM_ERROR_NO_2D_WRDAT_HEIGHT 0x040E0400ul              ///< No 2D WrDat Height
#define MEM_ERROR_2D_WRDAT_ERROR  0x040F0400ul                 ///< 2d WrDat Error
#define MEM_ERROR_INVALID_2D_WRDAT_VALUE  0x04100400ul         ///< 2d WrDat invalid value found
#define MEM_ERROR_2D_WRDAT_VREF_MARGIN_ERROR  0x04110400ul     ///< 2d WrDat Vef Margin error found
#define MEM_ERROR_PMU_TRAINING 0x04120400ul                    ///< Fail PMU training.

// AGESA_WARNING Memory Errors
#define MEM_WARNING_UNSUPPORTED_QRDIMM      0x04011600ul       ///< QR DIMMs detected but not supported
#define MEM_WARNING_UNSUPPORTED_UDIMM       0x04021600ul       ///< U DIMMs detected but not supported
#define MEM_WARNING_UNSUPPORTED_SODIMM      0x04031600ul       ///< SO-DIMMs detected but not supported
#define MEM_WARNING_UNSUPPORTED_X4DIMM      0x04041600ul       ///< x4 DIMMs detected but not supported
#define MEM_WARNING_UNSUPPORTED_RDIMM       0x04051600ul       ///< R DIMMs detected but not supported
#define MEM_WARNING_UNSUPPORTED_LRDIMM      0x04061600ul       ///< LR DIMMs detected but not supported
#define MEM_WARNING_EMP_NOT_SUPPORTED       0x04011700ul       ///< Processor is not capable for EMP
#define MEM_WARNING_EMP_CONFLICT            0x04021700ul       ///< EMP cannot be enabled if channel interleaving,
#define MEM_WARNING_EMP_NOT_ENABLED         0x04031700ul       ///< Memory size is not power of two.
#define MEM_WARNING_ECC_DIS                 0x04041700ul       ///< ECC has been disabled as a result of an internal issue
#define MEM_WARNING_PERFORMANCE_ENABLED_BATTERY_LIFE_PREFERRED 0x04011800ul  ///< Performance has been enabled, but battery life is preferred.
                                                                             ///< bank interleaving, or bank swizzle is enabled.
#define MEM_WARNING_NO_SPDTRC_FOUND               0x04011900ul ///< No Trc timing value found in SPD of a dimm.
#define MEM_WARNING_NODE_INTERLEAVING_NOT_ENABLED 0x04012000ul ///< Node Interleaveing Requested, but could not be enabled
#define MEM_WARNING_CHANNEL_INTERLEAVING_NOT_ENABLED 0x04012100ul ///< Channel Interleaveing Requested, but could not be enabled
#define MEM_WARNING_BANK_INTERLEAVING_NOT_ENABLED 0x04012200ul ///< Bank Interleaveing Requested, but could not be enabled
#define MEM_WARNING_VOLTAGE_1_35_NOT_SUPPORTED    0x04012300ul ///< Voltage 1.35 determined, but could not be supported
#define MEM_WARNING_INITIAL_DDR3VOLT_NONZERO      0x04012400ul ///< DDR3 voltage initial value is not 0
#define MEM_WARNING_NO_COMMONLY_SUPPORTED_VDDIO   0x04012500ul ///< Cannot find a commonly supported VDDIO
#define MEM_WARNING_AMP_SUPPORT_DETECTED_BUT_NOT_ENABLED 0x04012900ul ///< AMP support detected but not enabled
#define MEM_WARNING_AMP_SELECTED_BUT_NOT_ENABLED  0x04022900ul ///< AMP selected but not enabled

// AGESA_FATAL Memory Errors
#define MEM_ERROR_MINIMUM_MODE              0x04011A00ul       ///< Running in minimum mode
#define MEM_ERROR_MODULE_TYPE_MISMATCH_DIMM 0x04011B00ul       ///< DIMM modules are miss-matched
#define MEM_ERROR_NO_DIMM_FOUND_ON_SYSTEM   0x04011C00ul       ///< No DIMMs have been found
#define MEM_ERROR_MISMATCH_DIMM_CLOCKS      0x04011D00ul       ///< DIMM clocks miss-matched
#define MEM_ERROR_NO_CYC_TIME               0x04011E00ul       ///< No cycle time found
#define MEM_ERROR_TECHNOLOGY_TYPE_MISMATCH  0x04011F00ul       ///< DIMM technology type are miss-matched
#define MEM_ERROR_HEAP_ALLOCATE_DYN_STORING_OF_TRAINED_TIMINGS     0x04011F00ul  ///< Heap allocation error with dynamic storing of trained timings
#define MEM_ERROR_HEAP_ALLOCATE_FOR_DCT_STRUCT_AND_CH_DEF_STRUCTs  0x04021F00ul  ///< Heap allocation error for DCT_STRUCT and CH_DEF_STRUCT
#define MEM_ERROR_HEAP_ALLOCATE_FOR_REMOTE_TRAINING_ENV   0x04031F00ul           ///< Heap allocation error with REMOTE_TRAINING_ENV
#define MEM_ERROR_HEAP_ALLOCATE_FOR_SPD               0x04041F00ul    ///< Heap allocation error for SPD data
#define MEM_ERROR_HEAP_ALLOCATE_FOR_RECEIVED_DATA     0x04051F00ul    ///< Heap allocation error for RECEIVED_DATA during parallel training
#define MEM_ERROR_HEAP_ALLOCATE_FOR_S3_SPECIAL_CASE_REGISTERS     0x04061F00ul   ///< Heap allocation error for S3 "SPECIAL_CASE_REGISTER"
#define MEM_ERROR_HEAP_ALLOCATE_FOR_TRAINING_DATA     0x04071F00ul    ///< Heap allocation error for Training Data
#define MEM_ERROR_HEAP_ALLOCATE_FOR_IDENTIFY_DIMM_MEM_NB_BLOCK    0x04081F00ul   ///< Heap allocation error for  DIMM Identify "MEM_NB_BLOCK
#define MEM_ERROR_NO_CONSTRUCTOR_FOR_IDENTIFY_DIMM    0x04022300ul    ///< No Constructor for DIMM Identify
#define MEM_ERROR_VDDIO_UNSUPPORTED                   0x04022500ul    ///< VDDIO of the dimms on the board is not supported
#define MEM_ERROR_HEAP_ALLOCATE_FOR_2D                0x040B1F00ul    ///< Heap allocation error for 2D training data
#define MEM_ERROR_HEAP_DEALLOCATE_FOR_2D              0x040C1F00ul    ///< Heap de-allocation error for 2D training data
#define MEM_ERROR_HEAP_ALLOCATE_FOR_DATAEYE           0x040F1F00ul    ///< Heap allocation error for DATAEYE Storage
#define MEM_ERROR_HEAP_DEALLOCATE_FOR_DATAEYE         0x040E1F00ul    ///< Heap de-allocation error for DATAEYE Storage
#define MEM_ERROR_HEAP_ALLOCATE_FOR_PMU_SRAM_MSG_BLOCK            0x04101F00ul    ///< Heap allocation error for PMU SRAM Message Block Storage
#define MEM_ERROR_HEAP_DEALLOCATE_FOR_PMU_SRAM_MSG_BLOCK          0x04111F00ul    ///< Heap de-allocation error for PMU SRAM Message Block Storage
#define MEM_ERROR_HEAP_LOCATE_FOR_PMU_SRAM_MSG_BLOCK              0x04121F00ul    ///< Heap location error for PMU SRAM Message Block Storage
#define MEM_ERROR_FAILURE_TO_LOAD_OR_VERIFY_PMU_FW                0x04131F00ul    ///< The PMU FW did not load due to a verification error
#define MEM_ERROR_FAILURE_BIOS_PMU_FW_MISMATCH_AGESA_PMU_FW_VERSION       0x04141F00ul    ///< The BIOS PMU FW does not match AGESA PMU FW version
#define MEM_ERROR_FAILURE_BIOS_APCB_MISMATCH_AGESA_APCB_VERSION           0x04151F00ul    ///< The BIOS APCB does not match AGESA APCB version
#define MEM_ERROR_FAILURE_BIOS_APPB_MISMATCH_AGESA_APPB_VERSION           0x04161F00ul    ///< The BIOS APPB does not match AGESA APPB version
#define MEM_ERROR_FAILURE_HEAP_SIZE_OF_PSP_BL_TOO_SMALL           0x04171F00ul    ///< The Heap size of the AGESA BL larger than the PSP BL heap size
#define MEM_ERROR_FAILURE_PSP_TABLE_VERSION_MISSMATCH_WITH_AGESA_BL       0x04181F00ul    ///< The PSP funciton table version does not match with the AGESA BL Function table version
#define MEM_ERROR_FAILURE_PHASE_VERSION_MISSMATCH       0x04191F00ul    ///< The Current Phase Version does not match with the Previous Phase version
#define MEM_ERROR_FAILURE_PHASE_FAMILY_MISSMATCH       0x041A1F00ul    ///< The Current Phase Family does not match with the Previous Phase family
#define MEM_ERROR_FAILURE_PHASE_DDR_TYPE_MISSMATCH       0x041B1F00ul    ///< The Current Phase DDR Type does not match with the Previous Phase DDR Type
#define MEM_ERROR_FAILURE_APCB_DDR_TYPE_MISMATCH         0x041C1F00ul    ///< The APCB DDR Type missmatch with AGESA BL
#define MEM_ERROR_FAILURE_APCB_FAMILY_MISMATCH         0x041D1F00ul    ///< The APCB Family missmatch with AGESA BL
#define MEM_ERROR_FAILURE_APPB_DDR_TYPE_MISMATCH         0x041E1F00ul    ///< The APPB DDR Type missmatch with AGESA BL
#define MEM_ERROR_FAILURE_APPB_FAMILY_MISMATCH         0x041F1F00ul    ///< The APPB Family missmatch with AGESA BL

// AGESA_CRITICAL Memory Errors
#define MEM_ERROR_HEAP_ALLOCATE_FOR_DMI_TABLE_DDR3    0x04091F00ul    ///< Heap allocation error for DMI table for DDR3
#define MEM_ERROR_HEAP_ALLOCATE_FOR_DMI_TABLE_DDR4    0x040A1F00ul    ///< Heap allocation error for DMI table for DDR2
#define MEM_ERROR_UNSUPPORTED_DIMM_CONFIG             0x04011400ul    ///< Dimm population is not supported
#define MEM_ERROR_HEAP_ALLOCATE_FOR_CRAT_MEM_AFFINITY 0x040D1F00ul    ///< Heap allocation error for CRAT memory affinity info



/*----------------------------------------------------------------------------
 *
 *                END OF MEMORY-SPECIFIC DATA STRUCTURES
 *
 *----------------------------------------------------------------------------
 */




/*----------------------------------------------------------------------------
 *
 *                    CPU RELATED DEFINITIONS
 *
 *----------------------------------------------------------------------------
 */

// CPU Event definitions.

// Defines used to filter CPU events based on functional blocks
#define CPU_EVENT_PM_EVENT_MASK                         0xFF00FF00ul
#define CPU_EVENT_PM_EVENT_CLASS                        0x08000400ul

//================================================================
// CPU General events
//    Heap allocation                     (AppFunction =      01h)
#define CPU_ERROR_HEAP_BUFFER_IS_NOT_PRESENT            0x08000100ul
#define CPU_ERROR_HEAP_IS_ALREADY_INITIALIZED           0x08010100ul
#define CPU_ERROR_HEAP_IS_FULL                          0x08020100ul
#define CPU_ERROR_HEAP_BUFFER_HANDLE_IS_ALREADY_USED    0x08030100ul
#define CPU_ERROR_HEAP_BUFFER_HANDLE_IS_NOT_PRESENT     0x08040100ul
//    BrandId                             (AppFunction =      02h)
#define CPU_ERROR_BRANDID_HEAP_NOT_AVAILABLE            0x08000200ul
//    Micro code patch                    (AppFunction =      03h)
#define CPU_ERROR_MICRO_CODE_PATCH_IS_NOT_LOADED        0x08000300ul
//    Power management                    (AppFunction =      04h)
#define CPU_EVENT_PM_PSTATE_OVERCURRENT                 0x08000400ul
#define CPU_EVENT_PM_ALL_PSTATE_OVERCURRENT             0x08010400ul
#define CPU_ERROR_PSTATE_HEAP_NOT_AVAILABLE             0x08020400ul
#define CPU_ERROR_PM_NB_PSTATE_MISMATCH                 0x08030400ul
#define CPU_ERROR_PM_ALL_PSTATE_OVER_FREQUENCY_LIMIT    0x08040400ul
#define CPU_EVENT_PM_PSTATE_FREQUENCY_LIMIT             0x08050400ul
//    Other CPU events                    (AppFunction =      05h)
#define CPU_EVENT_BIST_ERROR                            0x08000500ul
#define CPU_EVENT_UNKNOWN_PROCESSOR_FAMILY              0x08010500ul
#define CPU_EVENT_STACK_REENTRY                         0x08020500ul
#define CPU_EVENT_CORE_NOT_IDENTIFIED                   0x08030500ul

//=================================================================
// CPU Feature events
//    Execution cache                     (AppFunction =      21h)
//        AGESA_CACHE_SIZE_REDUCED                            2101
//        AGESA_CACHE_REGIONS_ACROSS_1MB                      2102
//        AGESA_CACHE_REGIONS_ACROSS_4GB                      2103
//        AGESA_REGION_NOT_ALIGNED_ON_BOUNDARY                2104
//        AGESA_CACHE_START_ADDRESS_LESS_D0000                2105
//        AGESA_THREE_CACHE_REGIONS_ABOVE_1MB                 2106
//        AGESA_DEALLOCATE_CACHE_REGIONS                      2107
#define CPU_EVENT_EXECUTION_CACHE_ALLOCATION_ERROR      0x08002100ul
//    Core Leveling                       (AppFunction =      22h)
#define CPU_WARNING_ADJUSTED_LEVELING_MODE              0x08002200ul
//    SCS initialization                  (AppFunction =      24h)
//        AGESA_SCS_HEAP_ENTRY_MISSING                        2401
//        AGESA_SCS_BUFFER_EMPTY                              2402
//        AGESA_SCS_WEIGHTS_MISMATCH                          2403
#define CPU_EVENT_SCS_INITIALIZATION_ERROR              0x08002400ul

// CPU Build Configuration structures and definitions

/// Build Configuration structure for BLDCFG_AP_MTRR_SETTINGS
typedef struct {
  IN  UINT32 MsrAddr;     ///< Fixed-Sized MTRR address
  IN  UINT64 MsrData;     ///< MTRR Settings
} AP_MTRR_SETTINGS;

#define AMD_AP_MTRR_FIX64k_00000    0x00000250ul
#define AMD_AP_MTRR_FIX16k_80000    0x00000258ul
#define AMD_AP_MTRR_FIX16k_A0000    0x00000259ul
#define AMD_AP_MTRR_FIX4k_C0000     0x00000268ul
#define AMD_AP_MTRR_FIX4k_C8000     0x00000269ul
#define AMD_AP_MTRR_FIX4k_D0000     0x0000026Aul
#define AMD_AP_MTRR_FIX4k_D8000     0x0000026Bul
#define AMD_AP_MTRR_FIX4k_E0000     0x0000026Cul
#define AMD_AP_MTRR_FIX4k_E8000     0x0000026Dul
#define AMD_AP_MTRR_FIX4k_F0000     0x0000026Eul
#define AMD_AP_MTRR_FIX4k_F8000     0x0000026Ful
#define CPU_LIST_TERMINAL           0xFFFFFFFFul

/// Data structure for the Mapping Item between Unified ID for IDS Setup Option
/// and the option value.
///
typedef struct {
  IN    UINT16 IdsNvId;           ///< Unified ID for IDS Setup Option.
  OUT UINT16 IdsNvValue;        ///< The value of IDS Setup Option.
} IDS_NV_ITEM;

#define AGESA_IDS_DFT_VAL   0xFFFF                  ///<  Default value of every uninitlized NV item, the action for it will be ignored
#define AGESA_IDS_NV_END    0xFFFF                  ///< Flag specify end of option structure
/// WARNING: Don't change the comment below, it used as signature for script
/// AGESA IDS NV ID Definitions
typedef enum {
  AGESA_IDS_EXT_ID_START                   = 0x0000,///< 0x0000                                                             specify the start of external NV id

  AGESA_IDS_NV_BANK_INTERLEAVE,                     ///< 0x0004                                                               Enable or disable Bank Interleave
  AGESA_IDS_NV_CHANNEL_INTERLEAVE,                  ///< 0x0005                                                            Enable or disable Channel Interleave
  AGESA_IDS_NV_NODE_INTERLEAVE,                     ///< 0x0006                                                               Enable or disable Node Interleave
  AGESA_IDS_NV_MEMHOLE,                             ///< 0x0007                                                                  Enables or disable memory hole

  AGESA_IDS_NV_SCRUB_REDIRECTION,                   ///< 0x0008                                           Enable or disable a write to dram with corrected data
  AGESA_IDS_NV_DRAM_SCRUB,                          ///< 0x0009                                                   Set the rate of background scrubbing for DRAM
  AGESA_IDS_NV_SYNC_ON_ECC_ERROR,                   ///< 0x000E                                    Enable or disable the sync flood on un-correctable ECC error
  AGESA_IDS_NV_ECC_SYMBOL_SIZE,                     ///< 0x000F                                                                             Set ECC symbol size

  AGESA_IDS_NV_ALL_MEMCLKS,                         ///< 0x0010                                                      Enable or disable all memory clocks enable
  AGESA_IDS_NV_DCT_GANGING_MODE,                    ///< 0x0011                                                                             Set the Ganged mode
  AGESA_IDS_NV_DRAM_BURST_LENGTH32,                 ///< 0x0012                                                                    Set the DRAM Burst Length 32
  AGESA_IDS_NV_MEMORY_POWER_DOWN,                   ///< 0x0013                                                        Enable or disable Memory power down mode
  AGESA_IDS_NV_MEMORY_POWER_DOWN_MODE,              ///< 0x0014                                                                  Set the Memory power down mode
  AGESA_IDS_NV_DLL_SHUT_DOWN,                       ///< 0x0015                                                                   Enable or disable DLLShutdown
  AGESA_IDS_NV_ONLINE_SPARE,                        ///< 0x0016      Enable or disable the Dram controller to designate a DIMM bank as a spare for logical swap

  AGESA_IDS_NV_HDTOUT,                              ///< 0x0017                                                                Enable or disable HDTOUT feature
  AGESA_IDS_NV_DRAMCON,                             ///< 0x001F                                                  Specify the mode for controller initialization                                                            Enable or disable HDTOUT feature
  AGESA_IDS_EXT_ID_END,                             ///< 0x0020                                                               specify the end of external NV ID
} IDS_EX_NV_ID;


#define IDS_NUM_EXT_NV_ITEM (AGESA_IDS_EXT_ID_END - AGESA_IDS_EXT_ID_START + 1)


#endif // _AGESA_H_

