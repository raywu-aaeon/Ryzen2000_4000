/* $NoKeywords:$ */
/**
 * @file
 *
 * mp.h
 *
 * Platform Specific common header file
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem)
 * @e \$Revision: 311790 $ @e \$Date: 2015-01-27 13:03:49 +0800 (Tue, 27 Jan 2015) $
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

#ifndef _MP_H_
#define _MP_H_

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
/// Type of an entry for Dram Term table
typedef struct {
  UINT32 Speed; ///< BitMap for the supported speed
  UINT8  Dimms; ///< BitMap for supported number of dimm
  UINT8  QR_Dimms; ///< BitMap for supported number of QR dimm
  UINT8  DramTerm; ///< DramTerm value
  UINT8  QR_DramTerm; ///< DramTerm value for QR
  UINT8  DynamicDramTerm; ///< Dynamic DramTerm
} DRAM_TERM_ENTRY;

/// Type of an entry for POR speed limit table
typedef struct {
  UINT16   DIMMRankType;  ///< Bitmap of Ranks
  UINT8    Dimms;  ///< Number of dimm
  UINT16    SpeedLimit_1_5V; ///< POR speed limit for 1.5V
  UINT16    SpeedLimit_1_35V; ///< POR speed limit for 1.35V
  UINT16    SpeedLimit_1_25V; ///< POR speed limit for 1.25V
} POR_SPEED_LIMIT;

/// UDIMM&RDIMM Max. Frequency
typedef union {
  struct {                       ///< PSCFG_MAXFREQ_ENTRY
    UINT8 DimmPerCh;             ///< Dimm slot per chanel
    UINT16 Dimms:4;              ///< Number of Dimms on a channel
    UINT16 SR:4;                 ///< Number of single-rank Dimm
    UINT16 DR:4;                 ///< Number of dual-rank Dimm
    UINT16 QR:4;                 ///< Number of quad-rank Dimm
    UINT16 Speed1_5V;            ///< Speed limit with voltage 1.5V
    UINT16 Speed1_35V;           ///< Speed limit with voltage 1.35V
    UINT16 Speed1_25V;           ///< Speed limit with voltage 1.25V
  } _MAXFREQ_ENTRY;
  struct {                       ///< PSCFG_MAXFREQ_ENTRY
    UINT8 DimmPerCh;             ///< Dimm slot per chanel
    UINT16 Dimms:4;              ///< Number of Dimms on a channel
    UINT16 SR:4;                 ///< Number of single-rank Dimm
    UINT16 DR:4;                 ///< Number of dual-rank Dimm
    UINT16 QR:4;                 ///< Number of quad-rank Dimm
    UINT16 Speed1_2V;            ///< Speed limit with voltage 1.2V
    UINT16 Speed1_TBD1;          ///< Speed limit with future voltage TBD1
    UINT16 Speed1_TBD2;          ///< Speed limit with future voltage TBD2
  } _MAXFREQ_ENTRY_D4;
  struct {
    UINT8 DimmSlotPerCh;
    UINT16 CDN;                  ///< Condition
    UINT16 Speed[3];             ///< Speed limit
  } MAXFREQ_ENTRY;
} PSCFG_MAXFREQ_ENTRY;

///  LRDIMM Max. Frequency
typedef union {
  struct {                       ///< PSCFG_LR_MAXFREQ_ENTRY
    UINT8 DimmPerCh;             ///< Dimm slot per chanel
    UINT16 Dimms:4;              ///< Number of Dimms on a channel
    UINT16 LR:12;                ///< Number of LR-DIMM
    UINT16 Speed1_5V;            ///< Speed limit with voltage 1.5V
    UINT16 Speed1_35V;           ///< Speed limit with voltage 1.35V
    UINT16 Speed1_25V;           ///< Speed limit with voltage 1.25V
  } _LR_MAXFREQ_ENTRY;
  struct {
    UINT8 DimmSlotPerCh;
    UINT16 CDN;
    UINT16 Speed[3];
  } LR_MAXFREQ_ENTRY;
} PSCFG_LR_MAXFREQ_ENTRY;

/// UDIMM&RDIMM RttNom and RttWr
typedef struct {
  UINT64 DimmPerCh:8;          ///< Dimm slot per chanel
  UINT64 DDRrate:32;           ///< Bitmap of DDR rate
  UINT64 VDDIO:4;              ///< Bitmap of VDDIO
  UINT64 Dimm0:4;              ///< Bitmap of rank type of Dimm0
  UINT64 Dimm1:4;              ///< Bitmap of rank type of Dimm1
  UINT64 Dimm2:4;              ///< Bitmap of rank type of Dimm2
  UINT64 Dimm:4;               ///< Bitmap of rank type of Dimm
  UINT64 Rank:4;               ///< Bitmap of rank
  UINT8 RttNom:3;              ///< Dram term
  UINT8 RttWr:5;               ///< Dynamic dram term
} PSCFG_RTT_ENTRY;

/// LRDIMM RttNom and RttWr
typedef struct {
  UINT64 DimmPerCh:8;          ///< Dimm slot per chanel
  UINT64 DDRrate:32;           ///< Bitmap of DDR rate
  UINT64 VDDIO:4;              ///< Bitmap of VDDIO
  UINT64 Dimm0:4;              ///< Dimm0 population
  UINT64 Dimm1:4;              ///< Dimm1 population
  UINT64 Dimm2:12;             ///< Dimm2 population
  UINT8 RttNom:3;              ///< Dram term
  UINT8 RttWr:5;               ///< Dynamic dram term
} PSCFG_LR_RTT_ENTRY;

/// UDIMM&RDIMM&LRDIMM ODT pattern OF 1 DPC
typedef struct {
  UINT16 Dimm0;                ///< Bitmap of dimm0 rank type or dimm0 population of LRDIMM
  UINT32 RdODTCSHigh;          ///< RdODTCSHigh
  UINT32 RdODTCSLow;           ///< RdODTCSLow
  UINT32 WrODTCSHigh;          ///< WrODTCSHigh
  UINT32 WrODTCSLow;           ///< WrODTCSLow
} PSCFG_1D_ODTPAT_ENTRY;

/// UDIMM&RDIMM&LRDIMM ODT pattern OF 2 DPC
typedef struct {
  UINT16 Dimm0:4;              ///< Bitmap of dimm0 rank type or dimm0 population of LRDIMM
  UINT16 Dimm1:12;             ///< Bitmap of dimm1 rank type or dimm1 population of LRDIMM
  UINT32 RdODTCSHigh;          ///< RdODTCSHigh
  UINT32 RdODTCSLow;           ///< RdODTCSLow
  UINT32 WrODTCSHigh;          ///< WrODTCSHigh
  UINT32 WrODTCSLow;           ///< WrODTCSLow
} PSCFG_2D_ODTPAT_ENTRY;

/// UDIMM&RDIMM&LRDIMM ODT pattern OF 3 DPC
typedef struct {
  UINT16 Dimm0:4;              ///< Bitmap of dimm0 rank type or dimm0 population of LRDIMM
  UINT16 Dimm1:4;              ///< Bitmap of dimm1 rank type or dimm1 population of LRDIMM
  UINT16 Dimm2:8;              ///< Bitmap of dimm2 rank type or dimm2 population of LRDIMM
  UINT32 RdODTCSHigh;          ///< RdODTCSHigh
  UINT32 RdODTCSLow;           ///< RdODTCSLow
  UINT32 WrODTCSHigh;          ///< WrODTCSHigh
  UINT32 WrODTCSLow;           ///< WrODTCSLow
} PSCFG_3D_ODTPAT_ENTRY;

/// UDIMM&RDIMM&LRDIMM SlowMode, AddrTmgCtl and ODC
typedef struct {
  UINT64 DimmPerCh:8;          ///< Dimm slot per channel
  UINT64 DDRrate:32;           ///< Bitmap of DDR rate
  UINT64 VDDIO:4;              ///< Bitmap of VDDIO
  UINT64 Dimm0:4;              ///< Bitmap of dimm0 rank type or dimm0 population of LRDIMM
  UINT64 Dimm1:4;              ///< Bitmap of dimm1 rank type or dimm1 population of LRDIMM
  UINT64 Dimm2:11;             ///< Bitmap of dimm2 rank type or dimm2 population of LRDIMM
  UINT64 SlowMode:1;           ///< SlowMode
  UINT32 AddTmgCtl;            ///< AddTmgCtl
  UINT32 ODC;                  ///< ODC
  UINT8 POdtOff;               ///< POdtOff
} PSCFG_SAO_ENTRY;

/// UDIMM&RDIMM&LRDIMM 2D training config entry
typedef struct {
  UINT64 DimmPerCh:8;          ///< Dimm per channel
  UINT64 DDRrate:32;           ///< Bitmap of DDR rate
  UINT64 VDDIO:4;              ///< Bitmap of VDDIO
  UINT64 Dimm0:4;              ///< Bitmap of dimm0 rank type or dimm0 population of LRDIMM
  UINT64 Dimm1:4;              ///< Bitmap of dimm1 rank type or dimm1 population of LRDIMM
  UINT64 Dimm2:11;             ///< Bitmap of dimm2 rank type or dimm2 population of LRDIMM
  UINT64 Enable2D:1;           ///< SlowMode
} PSCFG_S2D_ENTRY;

/// UDIMM&RDIMM MR0[WR]
typedef struct {
  UINT8 Timing;                ///< Fn2_22C_dct[1:0][Twr]
  UINT8 Value;                 ///< MR0[WR] : bit0 - bit2 available
} PSCFG_MR0WR_ENTRY;

/// UDIMM&RDIMM MR0[CL]
typedef struct {
  UINT8 Timing;                ///< Fn2_200_dct[1:0][Tcl]
  UINT8 Value:3;               ///< MR0[CL] : bit0 - bit2 CL[3:1]
  UINT8 Value1:5;              ///< MR0[CL] : bit3 CL[0]
} PSCFG_MR0CL_ENTRY;

/// UDIMM&RDIMM MR2[IBT]
typedef struct {
  UINT64 DimmPerCh:4;          ///< Dimm per channel
  UINT64 DDRrate:32;           ///< Bitmap of DDR rate
  UINT64 VDDIO:4;              ///< Bitmap of VDDIO
  UINT64 Dimm0:4;              ///< Bitmap of dimm0 rank type
  UINT64 Dimm1:4;              ///< Bitmap of dimm1 rank type
  UINT64 Dimm2:4;              ///< Bitmap of dimm2 rank type
  UINT64 Dimm:4;               ///< Bitmap of rank type of Dimm
  UINT64 NumOfReg:4;           ///< Number of registers
  UINT64 IBT:4;                 ///< MR2[IBT] value
} PSCFG_MR2IBT_ENTRY;

/// UDIMM&RDIMM&LRDIMM Operating Speed
typedef struct {
  UINT32 DDRrate;              ///< Bitmap of DDR rate
  UINT8 OPSPD;                 ///< RC10[OperatingSpeed]
} PSCFG_OPSPD_ENTRY;

/// LRDIMM IBT
typedef struct {
  UINT64 DimmPerCh:4;          ///< Dimm per channel
  UINT64 DDRrate:32;           ///< Bitmap of DDR rate
  UINT64 VDDIO:4;              ///< Bitmap of VDDIO
  UINT64 Dimm0:4;              ///< Dimm0 population
  UINT64 Dimm1:4;              ///< Dimm1 population
  UINT64 Dimm2:4;              ///< Dimm2 population
  UINT64 F0RC8:3;              ///< F0RC8
  UINT64 F1RC0:3;              ///< F1RC0
  UINT64 F1RC1:3;              ///< F1RC1
  UINT64 F1RC2:3;              ///< F1RC2
} PSCFG_L_IBT_ENTRY;

/// LRDIMM F0RC13[NumPhysicalRanks]
typedef struct {
  UINT8 NumRanks:3;            ///< NumRanks
  UINT8 NumPhyRanks:5;         ///< NumPhyRanks
} PSCFG_L_NPR_ENTRY;

/// LRDIMM F0RC13[NumLogicalRanks]
typedef struct {
  UINT16 NumPhyRanks:3;        ///< NumPhyRanks
  UINT16 DramCap:4;            ///< DramCap
  UINT16 NumDimmSlot:9;        ///< NumDimmSlot
  UINT8 NumLogRanks;           ///< NumLogRanks
} PSCFG_L_NLR_ENTRY;

/// UDIMM&RDIMM&LRDIMM pass1 seed entry
typedef struct {
  UINT8 DimmPerCh;             ///< Dimm per channel
  UINT8 Channel;               ///< Channel#
  UINT16 SeedVal;              ///< Seed value
} PSCFG_SEED_ENTRY;

/// Platform specific configuration types
typedef enum {
  PSCFG_MAXFREQ,               ///< PSCFG_MAXFREQ
  PSCFG_LR_MAXFREQ,            ///< PSCFG_LR_MAXFREQ
  PSCFG_RTT,                   ///< PSCFG_RTT
  PSCFG_LR_RTT,                ///< PSCFG_LR_RTT
  PSCFG_ODT_PAT_1D,            ///< PSCFG_ODT_PAT_1D
  PSCFG_ODT_PAT_2D,            ///< PSCFG_ODT_PAT_2D
  PSCFG_ODT_PAT_3D,            ///< PSCFG_ODT_PAT_3D
  PSCFG_LR_ODT_PAT_1D,         ///< PSCFG_LR_ODT_PAT_1D
  PSCFG_LR_ODT_PAT_2D,         ///< PSCFG_LR_ODT_PAT_2D
  PSCFG_LR_ODT_PAT_3D,         ///< PSCFG_LR_ODT_PAT_3D
  PSCFG_SAO,                   ///< PSCFG_SAO
  PSCFG_LR_SAO,                ///< PSCFG_LR_SAO
  PSCFG_MR0WR,                 ///< PSCFG_MR0WR
  PSCFG_MR0CL,                 ///< PSCFG_MR0CL
  PSCFG_RC2IBT,                ///< PSCFG_RC2IBT
  PSCFG_RC10OPSPD,             ///< PSCFG_RC10OPSPD
  PSCFG_LR_IBT,                ///< PSCFG_LR_IBT
  PSCFG_LR_NPR,                ///< PSCFG_LR_NPR
  PSCFG_LR_NLR,                ///< PSCFG_LR_NLR
  PSCFG_S2D,                   ///< PSCFG_S2D
  PSCFG_WL_PASS1_SEED,         ///< PSCFG_WL_PASS1_SEED
  PSCFG_HWRXEN_PASS1_SEED,     ///< PSCFG_HWRXEN_SEED
  PSCFG_CADBUS,                ///< PSCFG_CADBUS
  PSCFG_DATABUS,               ///< PSCFG_DATABUS

  // The type of general table entries could be added between
  // PSCFG_GEN_START and PSCFG_GEN_END so that the PSCGen routine
  // is able to look for the entries per the PSCType.
  PSCFG_GEN_START,             ///< PSCFG_GEN_START
  PSCFG_CLKDIS,                ///< PSCFG_CLKDIS
  PSCFG_CKETRI,                ///< PSCFG_CKETRI
  PSCFG_ODTTRI,                ///< PSCFG_ODTTRI
  PSCFG_CSTRI,                 ///< PSCFG_CSTRI
  PSCFG_GEN_END                ///< PSCFG_GEN_END
} PSCFG_TYPE;

/// Dimm types
typedef enum {
  UDIMM_TYPE = 0x01,           ///< UDIMM_TYPE
  RDIMM_TYPE = 0x02,           ///< RDIMM_TYPE
  SODIMM_TYPE = 0x04,          ///< SODIMM_TYPE
  LRDIMM_TYPE = 0x08,          ///< LRDIMM_TYPE
  SODWN_SODIMM_TYPE = 0x10,    ///< SODWN_SODIMM_TYPE
  DT_DONT_CARE = 0xFF          ///< DT_DONT_CARE
} DIMM_TYPE;

/// Number of DRAM devices or DIMM slots
typedef enum {
  _1DIMM = 0x01,               ///< _1DIMM
  _2DIMM = 0x02,               ///< _2DIMM
  _3DIMM = 0x04,               ///< _3DIMM
  _4DIMM = 0x08,               ///< _4DIMM
  _DIMM_NONE = 0xF0,           ///< _DIMM_NONE (no DIMM slot)
  NOD_DONT_CARE = 0xFF         ///< NOD_DONT_CARE
} NOD_SUPPORTED;

/// Motherboard layer type
typedef enum {
  _4LAYERS = 0x01,             ///< 4 Layers
  _6LAYERS = 0x02,             ///< 6 Layers
  MBL_DONT_CARE = 0xFF         ///< MBL_DONT_CARE
} MB_LAYER_TYPE;

/// Motherboard power type
typedef enum {
  LPM = 0x01,                  ///< Low power motherboard
  HPM = 0x02,                  ///< High power motherboard
  MBP_DONT_CARE = 0xFF         ///< MBP_DONT_CARE
} MB_POWER_TYPE;

/// DQS Routing type
typedef enum {
  DQS_TREE = 0x01,             ///< Tree topology is applied to DQS routing
  DQS_DAISY_CHAIN = 0x02,      ///< Daisy chain topology is applied to DQS routing
  DQS_ROUTING_ANY = 0xFF       ///< Any routing type
} DQS_ROUTING_TYPE;

/// Table header related definitions
typedef struct {
  PSCFG_TYPE PSCType;           ///< PSC Type
  DIMM_TYPE DimmType;           ///< Dimm Type
  NOD_SUPPORTED NumOfDimm;      ///< Numbef of dimm
  SOC_LOGICAL_ID LogicalCpuid;  ///< Logical Cpuid
  UINT8 PackageType;            ///< Package Type
  TECHNOLOGY_TYPE TechType;     ///< Technology type
  MB_LAYER_TYPE MotherboardLayer; ///< Motherboard layer type
  MB_POWER_TYPE MotherboardPower; ///< Motherboard power type
  DQS_ROUTING_TYPE DqsRoutingType;  ///< DQS Routing type
} PSC_TBL_HEADER;

/// Table entry
typedef struct {
  PSC_TBL_HEADER Header;        ///< PSC_TBL_HEADER
  UINT8 TableSize;              ///< Table size
  VOID *TBLPtr;                 ///< Pointer of the table
} PSC_TBL_ENTRY;

#define PT_DONT_CARE 0xFF
#define NP     1
#define V1_5   1
#define V1_35  2
#define V1_25  4
#define V1_2   1
#define V_TBD1 2
#define V_TBD2 4

#define VOLT_ALL (7)
#define DIMM_SR 2
#define DIMM_DR 4
#define DIMM_QR 8
#define DIMM_LR 2
#define R0 1
#define R1 2
#define R2 4
#define R3 8
#define CH_A 0x01
#define CH_B 0x02
#define CH_C 0x04
#define CH_D 0x08
#define CH_ALL 0x0F

/// CAD Bus configuration
typedef struct {
  UINT8  DimmPerCh;       ///< Number of Dimm slots per chanel
  UINT32 DDRrate;         ///< Bitmap of DDR rate
  UINT8  VDDIO;           ///< Bitmap of VDDIO
  UINT8  Dimm0;           ///< Bitmap of rank type of Dimm0
  UINT8  Dimm1;           ///< Bitmap of rank type of Dimm1

  UINT32 SlowMode   :8;   ///< SlowMode
  UINT32 AddrCmdCtl :24;  ///< AddrCmdCtl

  UINT8  CkeStrength;     ///< CKE drive strength
  UINT8  CsOdtStrength;   ///< CS ODT drive strength
  UINT8  AddrCmdStrength; ///< Addr Cmd drive strength
  UINT8  ClkStrength;     ///< CLK drive strength
} PSCFG_CADBUS_ENTRY;

/// On die termination encoding
typedef enum {
  ODT_OFF = 0,     ///<  0 On die termination disabled
  ODT_60  = 1,     ///<  1 60 ohms
  ODT_120 = 2,     ///<  2 120 ohms
  ODT_40  = 3,     ///<  3 40 ohms
  ODT_20  = 4,     ///<  4 20 ohms
  ODT_30  = 5,     ///<  5 30 ohms
} ODT_ENC;

/// DDR4 Rtt_Nom termination encoding
typedef enum {
  RTTNOM_OFF  = 0, ///<  0 Rtt_Nom Disabled
  RTTNOM_60   = 1, ///<  1 60 ohms
  RTTNOM_120  = 2, ///<  2 120 ohms
  RTTNOM_40   = 3, ///<  3 40 ohms
  RTTNOM_240  = 4, ///<  4 240 ohms
  RTTNOM_48   = 5, ///<  5 48 ohms
  RTTNOM_80   = 6, ///<  5 80 ohms
  RTTNOM_34   = 7, ///<  5 34 ohms
} D4_RTT_NOM_ENC;

/// DDR4 Rtt_Wr termination encoding
typedef enum {
  RTTWR_OFF  = 0, ///<  0 Rtt_Nom Disabled
  RTTWR_120  = 1, ///< 1 120 ohms
  RTTWR_240  = 2, ///<  2 24 ohms
  RTTWR_HIZ  = 3, ///<  3 Hi-Z
  RTTWR_80   = 4, ///<  4 80 ohms
} D4_RTT_WR_ENC;

/// DDR4 Rtt_Park termination encoding
typedef enum {
  RTTPRK_OFF  = 0, ///<  0 Rtt_Park Disabled
  RTTPRK_60   = 1, ///<  1 60 ohms
  RTTPRK_120  = 2, ///<  2 120 ohms
  RTTPRK_40   = 3, ///<  3 40 ohms
  RTTPRK_240  = 4, ///<  4 240 ohms
  RTTPRK_48   = 5, ///<  5 48 ohms
  RTTPRK_80   = 6, ///<  5 80 ohms
  RTTPRK_34   = 7, ///<  5 34 ohms
} D4_RTT_PRK_ENC;

/// DataBus Entry Operator
typedef enum {
  OP_AUTO = 0,       ///< 0 Auto
  OP_ADD = 1,        ///< 1 Add
  OP_SUB = 2,        ///< 2 Sub
  OP_OVERRIDE = 3,   ///< 3 Override
} DATABUS_ENTRY_OP;

/// DDR3 Data Bus configuration
typedef struct {
  UINT32 DimmPerCh:2;   ///< Bitmap of Dimm slot per chanel
  UINT32 DDRrate:18;    ///< Bitmap of DDR rate
  UINT32 VDDIO:4;       ///< Bitmap of VDDIO
  UINT32 Dimm0:4;       ///< Bitmap of rank type of Dimm0
  UINT32 Dimm1:4;       ///< Bitmap of rank type of Dimm1

  UINT32 RttNom:4;      ///< Rtt_Nom
  UINT32 RttWr:4;       ///< Rtt_Wr
  UINT32 DqStrength:8;  ///< Data drive strength
  UINT32 DqsStrength:8; ///< DQS drive strength
  UINT32 OdtStrength:8; ///< ODT drive strength
} PSCFG_DATABUS_ENTRY_D3;

/// DDR4 Data Bus configuration
typedef struct {
  UINT8 DimmPerCh;     ///< Bitmap of Dimm slot per chanel
  UINT32 DDRrate;      ///< Bitmap of DDR rate
  UINT8 VDDIO;         ///< Bitmap of VDDIO
  UINT8 Dimm0;         ///< Bitmap of rank type of Dimm0
  UINT8 Dimm1;         ///< Bitmap of rank type of Dimm1
  UINT8 RttNom;        ///< Rtt_Nom
  UINT8 RttWr;         ///< Rtt_Wr
  UINT8 RttPark;       ///< Rtt_Park
  UINT8 DqStrength;    ///< Data drive strength
  UINT8 DqsStrength;   ///< DQS drive strength
  UINT8 OdtStrength;   ///< ODT drive strength
  UINT8 RxDlyOp:1;     ///< RxDly Operator
  UINT8 RxDlyOffset:7; ///< RxDly Offset
  UINT8 TxDlyOp:1;     ///< TxDly Operator
  UINT8 TxDlyOffset:7; ///< TxDly Offset
  UINT8 VrefOp:1;      ///< Vref Operator
  UINT8 VrefOffset:7;  ///< Vref Offset
} PSCFG_DATABUS_ENTRY_D4;

/*----------------------------------------------------------------------------
 *                           FUNCTIONS PROTOTYPE
 *
 *----------------------------------------------------------------------------
 */

AGESA_STATUS
MemPConstructPsUDef (
  IN OUT   MEM_DATA_STRUCT *MemPtr,
  IN OUT   CH_DEF_STRUCT *ChannelPtr,
  IN OUT   MEM_PS_BLOCK *PsPtr
  );

BOOLEAN
MemPGetDramTerm (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 ArraySize,
  IN       CONST DRAM_TERM_ENTRY *DramTermPtr
  );

UINT16
MemPGetPorFreqLimit (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 FreqLimitSize,
  IN       CONST POR_SPEED_LIMIT *FreqLimitPtr
  );

VOID
MemPGetPORFreqLimitDef (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

BOOLEAN
MemPPSCFlow (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

VOID
MemPConstructRankTypeMap (
  IN          UINT16 Dimm0,
  IN          UINT16 Dimm1,
  IN          UINT16 Dimm2,
  IN OUT   UINT16 *RankTypeInTable
 );

BOOLEAN
MemPIsIdSupported (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       SOC_LOGICAL_ID LogicalId,
  IN       UINT8 PackageType
 );

UINT16
MemPGetPsRankType (
  IN       CH_DEF_STRUCT *CurrentChannel
  );

UINT16
MemPProceedTblDrvOverride (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       PSO_TABLE *PlatformMemoryConfiguration,
  IN       UINT8 ProceededPSOType
  );

BOOLEAN
MemPGetPSCPass1Seed (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

VOID
MemPPreparePsTabLookupConditions (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

PSC_TBL_ENTRY *
MemPGetTableEntry (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       PSC_TBL_ENTRY *ListOfTables[],
     OUT   UINT8 *TableSize
  );

#endif  /* _MP_H_ */

