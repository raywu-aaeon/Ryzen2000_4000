/* $NoKeywords:$ */
/**
 * @file
 *
 * Service procedure to initialize Power Play Table
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
 * @e \$Revision: 312286 $   @e \$Date: 2015-02-04 14:11:11 +0800 (Wed, 04 Feb 2015) $
 *
 */
/*
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
*
*/
#ifndef _GFXPWRPLAYTABLEV5_H_
#define _GFXPWRPLAYTABLEV5_H_

#pragma pack (push, 1)

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */

#define POLICY_LABEL_BATTERY                                0x1
#define POLICY_LABEL_PERFORMANCE                            0x2

#define MAX_NUM_OF_SW_STATES                                2//battery(removed), performance, and startup
#define MAX_NUM_OF_DPM_STATES                               10
#define MAX_NUM_OF_VCE_CLK_STATES                           9
#define MAX_NUM_OF_VCE_STATES                               8
#define MAX_NUM_OF_UVD_CLK_STATES                           8
#define MAX_NUM_OF_SAMCLK_STATES                            5
#define MAX_NUM_OF_FUSED_DPM_STATES                         8
#define MAX_NUM_OF_ACPCLK_STATES                            8
/// ATOM_PPLIB_POWERPLAYTABLE::ulPlatformCaps
#define ATOM_PP_PLATFORM_CAP_BACKBIAS                       1
#define ATOM_PP_PLATFORM_CAP_POWERPLAY                      2
#define ATOM_PP_PLATFORM_CAP_SBIOSPOWERSOURCE               4
#define ATOM_PP_PLATFORM_CAP_ASPM_L0s                       8
#define ATOM_PP_PLATFORM_CAP_ASPM_L1                        16
#define ATOM_PP_PLATFORM_CAP_HARDWAREDC                     32
#define ATOM_PP_PLATFORM_CAP_GEMINIPRIMARY                  64
#define ATOM_PP_PLATFORM_CAP_STEPVDDC                       128
#define ATOM_PP_PLATFORM_CAP_VOLTAGECONTROL                 256
#define ATOM_PP_PLATFORM_CAP_SIDEPORTCONTROL                512
#define ATOM_PP_PLATFORM_CAP_TURNOFFPLL_ASPML1              1024
#define ATOM_PP_PLATFORM_CAP_HTLINKCONTROL                  2048
#define ATOM_PP_PLATFORM_CAP_MVDDCONTROL                    4096
#define ATOM_PP_PLATFORM_CAP_GOTO_BOOT_ON_ALERT             0x2000        // Go to boot state on alerts, e.g. on an AC->DC transition.
#define ATOM_PP_PLATFORM_CAP_DONT_WAIT_FOR_VBLANK_ON_ALERT  0x4000        // Do NOT wait for VBLANK during an alert (e.g. AC->DC transition).
#define ATOM_PP_PLATFORM_CAP_VDDCI_CONTROL                  0x8000        // Does
#define ATOM_PP_PLATFORM_CAP_REGULATOR_HOT                  0x00010000ul  // Enable the 'regulator hot' feature.
#define ATOM_PP_PLATFORM_CAP_BACO                           0x00020000ul  // Does the driver supports BACO state.


#define ATOM_PPLIB_CLASSIFICATION_UI_BATTERY                1
#define ATOM_PPLIB_CLASSIFICATION_UI_BALANCED               3
#define ATOM_PPLIB_CLASSIFICATION_UI_PERFORMANCE            5

#define ATOM_PPLIB_CLASSIFICATION_BOOT                      0x0008
#define ATOM_PPLIB_CLASSIFICATION_THERMAL                   0x0010
#define ATOM_PPLIB_CLASSIFICATION_LIMITEDPOWERSOURCE        0x0020
#define ATOM_PPLIB_CLASSIFICATION_REST                      0x0040
#define ATOM_PPLIB_CLASSIFICATION_FORCED                    0x0080
#define ATOM_PPLIB_CLASSIFICATION_3DPERFORMANCE             0x0100
#define ATOM_PPLIB_CLASSIFICATION_OVERDRIVETEMPLATE         0x0200
#define ATOM_PPLIB_CLASSIFICATION_UVDSTATE                  0x0400
#define ATOM_PPLIB_CLASSIFICATION_3DLOW                     0x0800
#define ATOM_PPLIB_CLASSIFICATION_ACPI                      0x1000
#define ATOM_PPLIB_CLASSIFICATION_HD2STATE                  0x2000
#define ATOM_PPLIB_CLASSIFICATION_HDSTATE                   0x4000
#define ATOM_PPLIB_CLASSIFICATION_SDSTATE                   0x8000
#define ATOM_PPLIB_CLASSIFICATION_NONUVDSTATE               0x0000

#define ATOM_PPLIB_CLASSIFICATION2_MVC                      0x0004       //Multi-View

#define ATOM_PPLIB_ENABLE_VARIBRIGHT                        0x00008000ul
#define ATOM_PPLIB_ENABLE_DRR                               0x00080000ul

#define ATOM_PP_FANPARAMETERS_NOFAN                         0x80
#define ATOM_PP_THERMALCONTROLLER_CZ                        19
#define ATOM_PP_THERMALCONTROLLER_ST                        19

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U R E S
 *----------------------------------------------------------------------------------------
 */

/// New added for CZ to replace ATOM_PPLIB_SUMO_CLOCK_INFO
typedef struct _ATOM_PPLIB_CZ_CLOCK_INFO {
  UCHAR                       index;     //indexes ATOM_PPLIB_CLK_VOLT_DEPENDENCY_TABLE, which sits at offset usVddcDependencyOnSCLKOffset
  UCHAR                       rsv[3];    // Reserved
} ATOM_PPLIB_CZ_CLOCK_INFO;


/// Non clock info
typedef struct _ATOM_PPLIB_NONCLOCK_INFO {
  USHORT                      usClassification;             ///< State classification see ATOM_PPLIB_CLASSIFICATION_*
  UCHAR                       ucMinTemperature;             ///< Reserved
  UCHAR                       ucMaxTemperature;             ///< Reserved
  ULONG                       ulCapsAndSettings;            ///< Capability Setting (ATOM_PPLIB_ENABLE_DRR or ATOM_PPLIB_ENABLE_VARIBRIGHT or 0)
  UCHAR                       ucRequiredPower;              ///< Reserved
  USHORT                      usClassification2;            ///< Reserved
  ULONG                       ulVCLK;                       ///< UVD clocks VCLK unit is in 10KHz
  ULONG                       ulDCLK;                       ///< UVD clocks DCLK unit is in 10KHz
  UCHAR                       ucUnused[5];                  ///< Reserved
} ATOM_PPLIB_NONCLOCK_INFO;

/// Thermal controller info stub
typedef struct _ATOM_PPLIB_THERMALCONTROLLER {
  UCHAR                       ucType;                       ///< Reserved. Should be set 0xE
  UCHAR                       ucI2cLine;                    ///< Reserved. Should be set 0
  UCHAR                       ucI2cAddress;                 ///< Reserved. Should be set 0
  UCHAR                       ucFanParameters;              ///< Reserved. Should be set 0x80
  UCHAR                       ucFanMinRPM;                  ///< Reserved. Should be set 0
  UCHAR                       ucFanMaxRPM;                  ///< Reserved. Should be set 0
  UCHAR                       ucReserved;                   ///< Reserved. Should be set 0
  UCHAR                       ucFlags;                      ///< Reserved. Should be set 0
} ATOM_PPLIB_THERMALCONTROLLER;

/// SW state info
typedef struct _ATOM_PPLIB_STATE_V2 {
  UCHAR                       ucNumDPMLevels;               ///< Number of valid DPM levels in this state
  UCHAR                       nonClockInfoIndex;            ///< Index to the array of NonClockInfos
  UCHAR                       ClockInfoIndex[1];            ///< Array of DPM states. Actual number calculated during state enumeration
} ATOM_PPLIB_STATE_V2;

/// SW state Array
typedef struct {
  UCHAR                       ucNumEntries;                 ///< Number of SW states
  ATOM_PPLIB_STATE_V2         States[1];                    ///< SW state info. Actual number calculated during state enumeration
} STATE_ARRAY;

/// Clock info Array
typedef struct {
  UCHAR                       ucNumEntries;                 ///< Number of ClockInfo entries
//  UCHAR                       ucEntrySize;                  ///< size of ATOM_PPLIB_SUMO_CLOCK_INFO
//  ATOM_PPLIB_SUMO_CLOCK_INFO  ClockInfo[1];                 ///< Clock info array. Size will be determined dynamically base on fuses
  UCHAR                       ucEntrySize;                  ///< size of ATOM_PPLIB_CZ_CLOCK_INFO
  ATOM_PPLIB_CZ_CLOCK_INFO    ClockInfo[1];                 ///< Clock info array. Size will be determined dynamically base on fuses
} CLOCK_INFO_ARRAY;

/// Non clock info Array
typedef struct {

  UCHAR                       ucNumEntries;                 ///< Number of Entries;
  UCHAR                       ucEntrySize;                  ///< Size of NonClockInfo
  ATOM_PPLIB_NONCLOCK_INFO    NonClockInfo[1];              ///< Non clock info array
} NON_CLOCK_INFO_ARRAY;

/// VCE clock info
typedef struct {
  USHORT                    usEVClkLow;                   ///< EVCLK low
  UCHAR                     ucEVClkHigh;                  ///< EVCLK high
  USHORT                    usECClkLow;                   ///< ECCLK low
  UCHAR                     ucECClkHigh;                  ///< ECCLK high
} VCECLOCKINFO;

/// VCE clock info array
typedef struct {
  UCHAR                     ucNumEntries;                ///< Number of entries
  VCECLOCKINFO              entries[1];                  ///< VCE clock array
} VCECLOCKINFOARRAY;

/// VCE voltage limit record
typedef struct {
  USHORT                    usVoltage;                    ///< Voltage index
  UCHAR                     ucVCEClockInfoIndex;          ///< Index of VCE clock state
} ATOM_PPLIB_VCE_CLOCK_VOLTAGE_LIMIT_RECORD;

/// VCE voltage limit table
typedef struct {
  UCHAR                                     numEntries;   ///< Number of entries
  ATOM_PPLIB_VCE_CLOCK_VOLTAGE_LIMIT_RECORD entries[1];   ///< Voltage limit state array
} ATOM_PPLIB_VCE_CLOCK_VOLTAGE_LIMIT_TABLE;

/// VCE state record
typedef struct {
  UCHAR                     ucVCEClockInfoIndex;          ///< Index of VCE clock state
  UCHAR                     ucClockInfoIndex;             ///< Index of SCLK clock state
} ATOM_PPLIB_VCE_STATE_RECORD;

/// VCE state table
typedef struct {
  UCHAR                       numEntries;                 ///< Number of state entries
  ATOM_PPLIB_VCE_STATE_RECORD entries[1];                 ///< State entries
} ATOM_PPLIB_VCE_STATE_TABLE;

/// Extended header
typedef struct {
  USHORT                      usSize;                     ///< size of header
  ULONG                       rsv15;                      ///< reserved
  ULONG                       rsv16;                      ///< reserved
  USHORT                      usVCETableOffset;           ///< offset of ATOM_PPLIB_VCE_TABLE
  USHORT                      usUVDTableOffset;           ///< offset of ATOM_PPLIB_UVD_TABLE
  USHORT                      usSAMUTableOffset;          ///< offset of ATOM_PPLIB_SAMU_TABLE
  USHORT                      usPPMTableOffset;           ///< offset of ATOM_PPLIB_PPM_TABLE
  USHORT                      usACPTableOffset;           ///< offset of ATOM_PPLIB_ACP_TABLE
  USHORT                      usPowerTuneTableOffset;     ///< points to ATOM_PPLIB_POWERTUNE_Table
  USHORT                      usSclkVddgfxTableOffset;    ///< points to ATOM_PPLIB_CLOCK_Voltage_Dependency_Table for sclkVddgfxTable
} ATOM_PPLIB_EXTENDEDHEADER;

/// VCE table
typedef struct {
  UCHAR                       revid;                      ///< revision ID
} ATOM_PPLIB_VCE_TABLE;

/// UVD clock info
typedef struct {
  USHORT usVClkLow;                                       ///< Vclk low
  UCHAR  ucVClkHigh;                                      ///< Vclk high
  USHORT usDClkLow;                                       ///< Dclk low
  UCHAR  ucDClkHigh;                                      ///< Dclk high
} UVD_CLOCK_INFO;

/// UVD clock info array
typedef struct {
  UCHAR          ucNumEntries;                            ///< number of entries
  UVD_CLOCK_INFO entries[1];                              ///< array of entries
} UVD_CLOCK_INFO_ARRAY;

/// VCE voltage limit record
typedef struct {
  USHORT                    usVoltage;                    ///< Voltage index
  UCHAR                     ucUVDClockInfoIndex;          ///< Index of VCE clock state
} ATOM_PPLIB_UVD_CLK_VOLT_LIMIT_RECORD;

/// VCE voltage limit table
typedef struct {
  UCHAR                                     numEntries;   ///< Number of entries
  ATOM_PPLIB_UVD_CLK_VOLT_LIMIT_RECORD entries[1];   ///< Voltage limit state array
} UVD_CLK_VOLT_LIMIT_TABLE;

/// UVD table
typedef struct {
  UCHAR                       revid;                      ///< revision ID
} ATOM_PPLIB_UVD_TABLE;

/// SAMU voltage limit record
typedef struct {
  USHORT usVoltage;                                       ///< voltage
  USHORT usSAMClockLow;                                   ///< SamClk low
  UCHAR  usSAMClockHigh;                                  ///< SamClk high
} ATOM_PPLIB_SAMCLK_VOLT_LIMIT_RECORD;

/// SAMU voltage limit table
typedef struct {
  UCHAR numEntries;                                       ///< number of entries
  ATOM_PPLIB_SAMCLK_VOLT_LIMIT_RECORD entries[1];         ///< array of entries
} ATOM_PPLIB_SAMCLK_VOLT_LIMIT_TABLE;

/// SAMU table
typedef struct {
  UCHAR revid;                                            ///< table revision id
//  ATOM_PPLIB_SAMCLK_VOLT_LIMIT_TABLE limits;            ///< offset of table
} ATOM_PPLIB_SAMU_TABLE;

/// Sclk volt dependency record
typedef struct {
  USHORT usClockLow;                                      ///< Sclk low word
  UCHAR  ucClockHigh;                                     ///< Sclk high byte
  USHORT usVoltage;                                       ///< Voltage
} ATOM_PPLIB_CLK_VOLT_DEPENDENCY_RECORD;

/// Sclk volt dependency table
typedef struct {
  UCHAR numEntries;                                       ///< number of entries
  ATOM_PPLIB_CLK_VOLT_DEPENDENCY_RECORD entries[1];       ///< array of entries
} ATOM_PPLIB_CLK_VOLT_DEPENDENCY_TABLE;

/// ACP Clk voltage limit record
typedef struct {
  USHORT usVoltage;                                       ///< voltage
  USHORT usACPClockLow;                                   ///< Acp Clk Low
  UCHAR  ucACPClockHigh;                                  ///< Acp Clk High
} ATOM_PPLIB_ACPCLK_VOLT_LIMIT_RECORD;

/// ACP Clk voltage limit table
typedef struct {
  UCHAR numEntries;                                       ///< number of entries
  ATOM_PPLIB_ACPCLK_VOLT_LIMIT_RECORD entries[1];      ///< array of records
} ATOM_PPLIB_ACPCLK_VOLT_LIMIT_TABLE;

/// ACP table
typedef struct {
  UCHAR revid;                                            ///< revision ID
} ATOM_PPLIB_ACP_TABLE;

#define ATOM_PPM_A_A 1
#define ATOM_PPM_A_I 2

/// Power Play table
typedef struct _ATOM_PPLIB_POWERPLAYTABLE5 {
  ATOM_COMMON_TABLE_HEADER      sHeader;                    ///< Common header
  UCHAR                         ucDataRevision;             ///< Revision of PP table
  UCHAR                         Reserved1[4];               ///< Reserved. ucNumStates ucStateEntrySize ucClockInfoSize ucNonClockSize
  USHORT                        usStateArrayOffset;         ///< Offset from start of this table to array of ucNumStates ATOM_PPLIB_STATE structures
  USHORT                        usClockInfoArrayOffset;     ///< Offset from start of the table to ClockInfoArray
  USHORT                        usNonClockInfoArrayOffset;  ///< Offset from Start of the table to NonClockInfoArray
  USHORT                        Reserved2[2];               ///< Reserved. usBackbiasTime usVoltageTime
  USHORT                        usTableSize;                ///< the size of this structure, or the extended structure
  ULONG                         ulPlatformCaps;             ///< See ATOM_PPLIB_CAPS_*
  ATOM_PPLIB_THERMALCONTROLLER  sThermalController;         ///< Thermal controller stub.
  USHORT                        Reserved4[2];               ///< Reserved. usBootClockInfoOffset usBootNonClockInfoOffset
  ///< ---ATOM_PPLIB_POWERPLAYTABLE----
  UCHAR                         Reserved5;                  ///< Reserved. ucNumCustomThermalPolicy
  USHORT                        Reserved6;                  ///< Reserved. usCustomThermalPolicyArrayOffset
  ///< ---ATOM_PPLIB_POWERPLAYTABLE2---
  USHORT                        usFormatID;                 ///< Format ID
  USHORT                        Reserved7[1];               ///< Reserved. usFanTableOffset
  USHORT                        usExtendendedHeaderOffset;  ///< Extended header offset
  ///< ---ATOM_PPLIB_POWERPLAYTABLE3---
  ULONG                         Reserved8[2];               ///< Reserved. ulGoldenPPID ulGoldenRevision
  USHORT                        usVddcDependencyOnSCLKOffset; ///< Sclk dependency table
  USHORT                        Reserved9[5];               ///< Reserved. usVddciDependencyOnMCLKOffset usVddcDependencyOnMCLKOffset usMaxClockVoltageOnDCOffset usVddcPhaseShedLimitsTableOffset usMvddDependencyOnMCLKOffset
  ///< ---ATOM_PPLIB_POWERPLAYTABLE4---
  ULONG                         ulTDPLimit;                 ///<
  ULONG                         ulNearTDPLimit;             ///<
  ULONG                         ulSQRampingThreshold;       ///<
  USHORT                        usCACLeakageTableOffset;    ///< Points to ATOM_PPLIB_CAC_Leakage_Table
  ULONG                         ulCACLeakage;               ///< The iLeakage for driver calculated CAC leakage table
  USHORT                        usTDPODLimit;               ///<
  USHORT                        usLoadLineSlope;            ///< in milliOhms * 100
} ATOM_PPLIB_POWERPLAYTABLE5;

/// Software state
typedef struct {
  BOOLEAN     Valid;                                  ///< State valid
  UINT16      Classification;                         ///< State classification
  UINT32      CapsAndSettings;                        ///< State capability and settings
  UINT16      Classification2;                        ///< State classification2
  UINT32      Vclk;                                   ///< UVD VCLK
  UINT32      Dclk;                                   ///< UVD DCLK
  UINT8       NumberOfDpmStates;                      ///< Number of DPM states
  UINT8       DpmStatesArray[MAX_NUM_OF_DPM_STATES];  ///< DPM state index array
} SW_STATE;

/// DPM state
typedef struct {
  BOOLEAN     Valid;                                  ///< State valid
  UINT32      Sclk;                                   ///< Sclk in kHz
  UINT8       Vid;                                    ///< VID index
  UINT16      Tdp;                                    ///< Tdp limit
} DPM_STATE;

/// PPlay Workspace (V2)
typedef struct {
  GFX_PLATFORM_CONFIG                       *Gfx;                                                 ///<
  ATOM_PPLIB_POWERPLAYTABLE5                *PpTable;                                             ///<
  PP_FUSE_ARRAY_V2                          *PpFuses;                                             ///<
  SW_STATE                                  SwStateArray [MAX_NUM_OF_SW_STATES];                  ///< SW state array
  DPM_STATE                                 DpmStateArray[MAX_NUM_OF_DPM_STATES];                 ///< Sclk DPM state array
  UINT8                                     NumOfClockVoltageLimitEnties;                         ///<
  ATOM_PPLIB_VCE_CLOCK_VOLTAGE_LIMIT_RECORD VceClockVoltageLimitArray[MAX_NUM_OF_VCE_CLK_STATES]; ///<
  UINT8                                     NumOfVceClockEnties;                                  ///<
  VCECLOCKINFO                              VceClockInfoArray[MAX_NUM_OF_VCE_CLK_STATES];         ///<
  UINT8                                     NumOfVceStateEntries;                                 ///<
  ATOM_PPLIB_VCE_STATE_RECORD               VceStateArray[MAX_NUM_OF_VCE_STATES];                 ///< VCE state array
  UINT8                                     NumOfUvdClkVoltLimitEntries;                          ///<
  ATOM_PPLIB_UVD_CLK_VOLT_LIMIT_RECORD      UvdClkVoltLimitArray[MAX_NUM_OF_UVD_CLK_STATES];      ///<
  UINT8                                     NumOfUvdClockEntries;                                 ///<
  UVD_CLOCK_INFO                            UvdClockInfoArray[MAX_NUM_OF_UVD_CLK_STATES];         ///<
  UINT8                                     NumOfSamClkVoltLimitEntries;                          ///<
  ATOM_PPLIB_SAMCLK_VOLT_LIMIT_RECORD       SamClkVoltLimitArray[MAX_NUM_OF_SAMCLK_STATES];       ///<
  UINT8                                     NumOfSclkVoltDepEntries;                              ///<
  ATOM_PPLIB_CLK_VOLT_DEPENDENCY_RECORD     SclkVoltDepArray[MAX_NUM_OF_FUSED_DPM_STATES];        ///<
  UINT8                                     NumOfAcpClkVoltLimitEntries;                          ///<
  ATOM_PPLIB_ACPCLK_VOLT_LIMIT_RECORD       AcpClkVoltLimitArray[MAX_NUM_OF_ACPCLK_STATES];       ///<
  UINT8                                     NumOfSclkVoltGfxDepEntries;                           ///<
  ATOM_PPLIB_CLK_VOLT_DEPENDENCY_RECORD     SclkVoltGfxDepArray[MAX_NUM_OF_FUSED_DPM_STATES];        ///<
} PP_WORKSPACE_V2;

#pragma pack (pop)


/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

SW_STATE *
GfxPwrPlayCreateSwState (
  IN OUT   PP_WORKSPACE_V2               *PpWorkspace
  );

UINT8
GfxPwrPlayCreateDpmState (
  IN OUT   PP_WORKSPACE_V2               *PpWorkspace,
  IN       UINT32                        Sclk,
  IN       UINT8                         Vid
  );

UINT8
GfxPwrPlayAddDpmState (
  IN OUT   PP_WORKSPACE_V2               *PpWorkspace,
  IN       UINT32                        Sclk,
  IN       UINT8                         Vid
  );

VOID
GfxPwrPlayAddDpmStateToSwState (
  IN OUT   SW_STATE                      *SwStateArray,
  IN       UINT8                         DpmStateIndex
  );

VOID *
GfxPwrPlayAttachStateInfoBlock (
  IN OUT   PP_WORKSPACE_V2               *PpWorkspace
  );

VOID *
GfxPwrPlayAttachClockInfoBlock (
  IN OUT   PP_WORKSPACE_V2              *PpWorkspace
  );

VOID *
GfxPwrPlayAttachNonClockInfoBlock (
  IN OUT   PP_WORKSPACE_V2              *PpWorkspace
  );

BOOLEAN
GfxPwrPlayIsFusedStateValid (
  IN      UINT8                         Index,
  IN      PP_FUSE_ARRAY_V2              *PpFuses,
  IN      GFX_PLATFORM_CONFIG           *Gfx
  );

UINT16
GfxPwrPlayGetClassificationFromFuses (
  IN      UINT8                         Index,
  IN      PP_FUSE_ARRAY_V2              *PpFuses,
  IN      GFX_PLATFORM_CONFIG           *Gfx
  );

VOID
GfxPwrPlayBuildSclkStateTable (
  IN OUT   PP_WORKSPACE_V2               *PpWorkspace
  );

UINT8
GfxPwrPlayAddEclkState (
  IN OUT   PP_WORKSPACE_V2               *PpWorkspace,
  IN       UINT32                        Eclk
  );

UINT8
GfxPwrPlayAddEclkVoltageRecord (
  IN OUT   PP_WORKSPACE_V2               *PpWorkspace,
  IN       UINT8                         EclkIndex,
  IN       UINT8                         Vid
  );

UINT8
GfxPwrPlayAddUvdClkInfo (
  IN OUT   PP_WORKSPACE_V2               *PpWorkspace,
  IN       UINT32                        Vclk,
  IN       UINT32                        Dclk
  );

UINT8
GfxPwrPlayAddUvdVoltageRecord (
  IN OUT   PP_WORKSPACE_V2               *PpWorkspace,
  IN       UINT8                         ClkIndex,
  IN       UINT8                         Vid
  );

UINT8
GfxPwrPlayAddSamuVoltageRecord (
  IN OUT   PP_WORKSPACE_V2               *PpWorkspace,
  IN       UINT8                         Vid,
  IN       UINT32                        Samclk
  );

UINT8
GfxPwrPlayAddAcpVoltageRecord (
  IN OUT   PP_WORKSPACE_V2               *PpWorkspace,
  IN       UINT8                         Vid,
  IN       UINT32                        Acpclk
  );

VOID *
GfxPwrPlayAttachExtendedHeaderBlock (
  IN OUT   PP_WORKSPACE_V2              *PpWorkspace
  );

VOID *
GfxPwrPlayAttachVceTableRevBlock (
  IN OUT   PP_WORKSPACE_V2              *PpWorkspace
  );

VOID *
GfxPwrPlayAttachVceClockInfoBlock (
  IN OUT   PP_WORKSPACE_V2              *PpWorkspace
  );

VOID *
GfxPwrPlayAttachVceVoltageLimitBlock (
  IN OUT   PP_WORKSPACE_V2              *PpWorkspace
  );

VOID *
GfxPwrPlayAttachVceStateTableBlock (
  IN OUT   PP_WORKSPACE_V2              *PpWorkspace
  );

VOID *
GfxPwrPlayAttachUvdTableRevBlock (
  IN OUT   PP_WORKSPACE_V2              *PpWorkspace
  );

VOID *
GfxPwrPlayAttachUvdClockInfoBlock (
  IN OUT   PP_WORKSPACE_V2              *PpWorkspace
  );

VOID *
GfxPwrPlayAttachUvdVoltageLimitBlock (
  IN OUT   PP_WORKSPACE_V2              *PpWorkspace
  );

VOID *
GfxPwrPlayAttachSamuTableRevBlock (
  IN OUT   PP_WORKSPACE_V2              *PpWorkspace
  );

VOID *
GfxPwrPlayAttachSamuVoltageLimitBlock (
  IN OUT   PP_WORKSPACE_V2              *PpWorkspace
  );

VOID *
GfxPwrPlayAttachAcpVoltageLimitBlock (
  IN OUT   PP_WORKSPACE_V2              *PpWorkspace
  );

VOID *
GfxPwrPlayAttachSclkDepTable (
  IN OUT   PP_WORKSPACE_V2              *PpWorkspace
  );

VOID
GfxPwrPlayBuildVceStateTable (
  IN OUT   PP_WORKSPACE_V2               *PpWorkspace
  );

VOID
GfxPwrPlayBuildUvdClockTable (
  IN OUT   PP_WORKSPACE_V2               *PpWorkspace
  );

VOID
GfxPwrPlayBuildSamuTable (
  IN OUT   PP_WORKSPACE_V2               *PpWorkspace
  );

VOID
GfxPwrPlayBuildAcpTable (
  IN OUT   PP_WORKSPACE_V2               *PpWorkspace
  );

AGESA_STATUS
GfxPwrPlayBuildTable (
     OUT  VOID                          *Buffer,
  IN      GFX_PLATFORM_CONFIG           *Gfx
  );


#endif

