/* $NoKeywords:$ */
/**
 * @file
 *
 * APCB.h
 *
 * AGESA PSP Customization Block
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem)
 * @e \$Revision: 192403 $ @e \$Date: 2012-12-12 15:46:25 -0600 (Wed, 12 Dec 2012) $
 *
 **/
/*****************************************************************************
*
* Copyright 2008 - 2021 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
*
* AMD is granting You permission to use this software and documentation (if
* any) (collectively, the "Software") pursuant to the terms and conditions of
* the Software License Agreement included with the Software. If You do not have
* a copy of the Software License Agreement, contact Your AMD representative for
* a copy.
* 
* You agree that You will not reverse engineer or decompile the Software, in
* whole or in part, except as allowed by applicable law.
* 
* WARRANTY DISCLAIMER: THE SOFTWARE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
* KIND. AMD DISCLAIMS ALL WARRANTIES, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
* BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, QUALITY,
* FITNESS FOR A PARTICULAR PURPOSE, TITLE, NON-INFRINGEMENT AND WARRANTIES
* ARISING FROM CUSTOM OF TRADE OR COURSE OF USAGE WITH RESPECT TO THE SOFTWARE,
* INCLUDING WITHOUT LIMITATION, THAT THE SOFTWARE WILL RUN UNINTERRUPTED OR
* ERROR-FREE. THE ENTIRE RISK ASSOCIATED WITH THE USE OF THE SOFTWARE IS
* ASSUMED BY YOU. Some jurisdictions do not allow the exclusion of implied
* warranties, so the above exclusion may not apply to You, but only to the
* extent required by law.
* 
* LIMITATION OF LIABILITY AND INDEMNIFICATION: TO THE EXTENT NOT PROHIBITED BY
* APPLICABLE LAW, AMD AND ITS LICENSORS WILL NOT, UNDER ANY CIRCUMSTANCES BE
* LIABLE TO YOU FOR ANY PUNITIVE, DIRECT, INCIDENTAL, INDIRECT, SPECIAL OR
* CONSEQUENTIAL DAMAGES ARISING FROM POSSESSION OR USE OF THE SOFTWARE OR
* OTHERWISE IN CONNECTION WITH ANY PROVISION OF THIS AGREEMENT EVEN IF AMD AND
* ITS LICENSORS HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES. THIS
* INCLUDES, WITHOUT LIMITATION, DAMAGES DUE TO LOST OR MISAPPROPRIATED DATA,
* LOST PROFITS OR CONFIDENTIAL OR OTHER INFORMATION, FOR BUSINESS INTERRUPTION,
* FOR PERSONAL INJURY, FOR LOSS OF PRIVACY, FOR FAILURE TO MEET ANY DUTY
* INCLUDING OF GOOD FAITH OR REASONABLE CARE, FOR NEGLIGENCE AND FOR ANY OTHER
* PECUNIARY OR OTHER LOSS WHTSOEVER. In no event shall AMD's total liability to
* You for all damages, losses, and causes of action (whether in contract, tort
* (including negligence) or otherwise) exceed the amount of $50 USD. You agree
* to defend, indemnify and hold harmless AMD, its subsidiaries and affiliates
* and their respective licensors, directors, officers, employees, affiliates or
* agents from and against any and all loss, damage, liability and other
* expenses (including reasonable attorneys' fees), resulting from Your
* possession or use of the Software or violation of the terms and conditions of
* this Agreement.
* 
* U.S. GOVERNMENT RESTRICTED RIGHTS: Notice to U.S. Government End Users. The
* Software and related documentation are "commercial items", as that term is
* defined at 48 C.F.R. Section 2.101, consisting of "commercial computer
* software" and "commercial computer software documentation", as such terms are
* used in 48 C.F.R. Section 12.212 and 48 C.F.R. Section 227.7202,
* respectively. Consistent with 48 C.F.R. Section 12.212 or 48 C.F.R. Sections
* 227.7202-1 through 227.7202-4, as applicable, the commercial computer
* software and commercial computer software documentation are being licensed to
* U.S. Government end users: (a) only as commercial items, and (b) with only
* those rights as are granted to all other end users pursuant to the terms and
* conditions set forth in this Agreement. Unpublished rights are reserved under
* the copyright laws of the United States.
* 
* EXPORT RESTRICTIONS:  You shall adhere to all applicable U.S. import/export
* laws and regulations, as well as the import/export control laws and
* regulations of other countries as applicable. You further agree You will not
* export, re-export, or transfer, directly or indirectly, any product,
* technical data, software or source code received from AMD under this license,
* or the direct product of such technical data or software to any country for
* which the United States or any other applicable government requires an export
* license or other governmental approval without first obtaining such licenses
* or approvals, or in violation of any applicable laws or regulations of the
* United States or the country where the technical data or software was
* obtained. You acknowledges the technical data and software received will not,
* in the absence of authorization from U.S. or local law and regulations as
* applicable, be used by or exported, re-exported or transferred to: (i) any
* sanctioned or embargoed country, or to nationals or residents of such
* countries; (ii) any restricted end-user as identified on any applicable
* government end-user list; or (iii) any party where the end-use involves
* nuclear, chemical/biological weapons, rocket systems, or unmanned air
* vehicles.  For the most current Country Group listings, or for additional
* information about the EAR or Your obligations under those regulations, please
* refer to the website of the U.S. Bureau of Industry and Security at
* http://www.bis.doc.gov/.
* ***************************************************************************
*
*/

#ifndef _APCB_H_
#define _APCB_H_

/// Build Configuration values for BLDCFG_MEMORY_BUS_FREQUENCY_LIMIT & BLDCFG_MEMORY_CLOCK_SELECT
#define DDR400_FREQUENCY  200     ///< DDR 400
#define DDR533_FREQUENCY  266     ///< DDR 533
#define DDR667_FREQUENCY  333     ///< DDR 667
#define DDR800_FREQUENCY  400     ///< DDR 800
#define DDR1066_FREQUENCY 533     ///< DDR 1066
#define DDR1333_FREQUENCY 667     ///< DDR 1333
#define DDR1600_FREQUENCY 800     ///< DDR 1600
#define DDR1866_FREQUENCY 933     ///< DDR 1867
#define DDR2100_FREQUENCY 1050    ///< DDR 2100
#define DDR2133_FREQUENCY 1067    ///< DDR 2133
#define DDR2400_FREQUENCY 1200    ///< DDR 2400
#define DDR2667_FREQUENCY 1333    ///< DDR 2667
#define DDR2733_FREQUENCY 1367    ///< DDR 2733
#define DDR2800_FREQUENCY 1400    ///< DDR 2800
#define DDR2867_FREQUENCY 1433    ///< DDR 2867
#define DDR2933_FREQUENCY 1467    ///< DDR 2933
#define DDR3000_FREQUENCY 1500    ///< DDR 3000
#define DDR3067_FREQUENCY 1533    ///< DDR 3067
#define DDR3133_FREQUENCY 1567    ///< DDR 3133
#define DDR3200_FREQUENCY 1600    ///< DDR 3200
#define DDR3267_FREQUENCY 1633    ///< DDR 3267
#define DDR3333_FREQUENCY 1667    ///< DDR 3333
#define DDR3400_FREQUENCY 1700    ///< DDR 3400
#define DDR3467_FREQUENCY 1733    ///< DDR 3467
#define DDR3533_FREQUENCY 1767    ///< DDR 3533
#define DDR3600_FREQUENCY 1800    ///< DDR 3600
#define DDR3667_FREQUENCY 1833    ///< DDR 3667
#define DDR3733_FREQUENCY 1867    ///< DDR 3733
#define DDR3800_FREQUENCY 1900    ///< DDR 3800
#define DDR3867_FREQUENCY 1933    ///< DDR 3867
#define DDR3933_FREQUENCY 1967    ///< DDR 3933
#define DDR4000_FREQUENCY 2000    ///< DDR 4000
#define DDR4067_FREQUENCY 2033    ///< DDR 4067
#define DDR4133_FREQUENCY 2067    ///< DDR 4133
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

/// UMA Version
typedef enum {
  UMA_LEGACY = 0,              ///< UMA Legacy Version
  UMA_NON_LEGACY = 1,          ///< UMA Non Legacy Version
  UMA_HYBRID_SECURE = 2        ///< UMA Hybrid Secure Version
} UMA_VERSION;

/// UMA Mode
typedef enum {
  UMA_NONE = 0,              ///< UMA None
  UMA_SPECIFIED = 1,         ///< UMA Specified
  UMA_AUTO = 2               ///< UMA Auto
} UMA_MODE;

/// Build Configuration values for BLDCFG_UMA_ALIGNMENT
typedef enum {
  NO_UMA_ALIGNED = 0x00FFFFFF,           ///< NO UMA aligned
  UMA_4MB_ALIGNED = 0x00FFFFC0,          ///< UMA 4MB aligned
  UMA_128MB_ALIGNED = 0x00FFF800,        ///< UMA 128MB aligned
  UMA_256MB_ALIGNED = 0x00FFF000,        ///< UMA 256MB aligned
  UMA_512MB_ALIGNED = 0x00FFE000,        ///< UMA 512MB aligned
} UMA_ALIGNMENT;

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

/// Bank Group Swap Mode
typedef enum {
  BANK_GROUP_SWAP_DISABLED = 0,                              ///< Bank Group Swap disabled
  BANK_GROUP_SWAP_CPU = 1,                                   ///< Bank Group Swap CPU Mode
  BANK_GROUP_SWAP_APU = 2                                    ///< Bank Group Swap APU Mode
} BANK_GROUP_SWAP_MODE;

/// Build Configuration values for BLDCFG_RESOLUTION
typedef enum {
  DISPLAY_1920x1080_And_Below = 0,        ///< 1920x1080 and below
  DISPLAY_2560x1600 = 1,                  ///< 2560x1600
  DISPLAY_3840x2160 = 2                   ///< 3840x2160
} DISPLAY_RESOLUTION;

/// Operater of Post training UMC delays
typedef enum {
  UmcTrnDelayPlus,
  UmcTrnDelayMinus,
  UmcTrnDelayOverride,
  UmcTrnDelayNone = 0xFF,
} UMC_TRN_DELAY_OP;

//#pragma pack(push, 1)
/// Dram technology type
typedef enum {
  DDR2_TECHNOLOGY,        ///< DDR2 technology
  DDR3_TECHNOLOGY,        ///< DDR3 technology
  GDDR5_TECHNOLOGY,       ///< GDDR5 technology
  DDR4_TECHNOLOGY,        ///< DDR4 technology
  LPDDR3_TECHNOLOGY,      ///< LPDDR3 technology
  LPDDR4_TECHNOLOGY,      ///< LPDDR4 technology
  HBM_TECHNOLOGY,         ///< HBM technology
  GDDR6_TECHNOLOGY,       ///< GDDR6 technology
  DDR5_TECHNOLOGY,        ///< DDR5 technology
  UNSUPPORTED_TECHNOLOGY, ///< Unsupported technology
} TECHNOLOGY_TYPE;

/// Structures use to pass system Logical CPU-ID
typedef struct {
  IN OUT   UINT32 Family;             ///< Indicates logical ID Family
  IN OUT   UINT16 Revision;           ///< Indicates logical ID Revision
} APCB_SOC_LOGICAL_ID;

/// Dram technology type
typedef enum {
  SODIMM_PACKAGE,        ///< SODIMM package
  UDIMM_PACKAGE,         ///< UDIMM Package
  RDIMM_PACKAGE,         ///< RDIMM Package
  DRAMDOWN_PACKAGE,      ///< DRAM Down Package
  UNSUPPORTED_PACKAGE,   ///< Unsupported package
} DRAM_PACKAGE_TYPE;

/// SPD_MUX_INFO
typedef struct _SPD_MUX_INFO {
  UINT8  SpdMuxPresent;      ///< SpdMux Present or not. if 1, then yes otherwise no
  UINT8  MuxI2CAddress;      ///< MuxI2cAddress
  UINT8  MuxChannel;         ///< MuxChannel no.
  UINT8  Reserved;           ///< Reserved
} SPD_MUX_INFO;

///
/// Meory Board Layout Info
///
#define MEMORY_LAYOUT_TYPE_DIMM           1
#define MEMORY_LAYOUT_TYPE_ONBOARD        2

//-----------------------------------------------------------------------------
///
/// SPD Data for each DIMM.
///
typedef struct _SPD_DEF_STRUCT {
  BOOLEAN           DramDownSpdValid;           ///< Indicates that the DramDown SPD is valid
  BOOLEAN           DimmPresent;                ///< Indicates that the DIMM is present and Data is valid
  UINT8             PageAddress;                ///< Indicates the 256 Byte EE Page the data belongs to
                                                ///<    0 = Lower Page
                                                ///<    1 = Upper Page
  BOOLEAN           NvDimmPresent;              ///< Indicates this DIMM is NVDIMM
  UINT16            DramManufacturersIDCode;    /// DRAM Manufacture ID
  UINT16            ModuleManufacturersIDCode;  /// Module Manufacture ID
  UINT32            Address;                    ///< SMBus address of the DRAM
  SPD_MUX_INFO      SpdMuxInfo;                 ///< Mux and Channel Number associated with this DIMM
  TECHNOLOGY_TYPE   Technology;                 ///< Indicates the type of Technology used in SPD
                                                ///<    DDR3_TECHNOLOGY = Use DDR3 DIMMs
                                                ///<    DDR4_TECHNOLOGY = Use DDR4 DIMMs
                                                ///<    LPDDR3_TECHNOLOGY = Use LPDDR3
  DRAM_PACKAGE_TYPE Package;                    ///< Indicates the package type
                                                ///<    SODIMM_PACKAGE = SODIMM package
                                                ///<    UDIMM_PACKAGE = UDIMM Package
                                                ///<    RDIMM_PACKAGE = RDIMM Package
                                                ///<    DRAMDOWN_PACKAGE = DRAM Down Package
  UINT8             SocketNumber;               ///< Indicates the socket number
  UINT8             ChannelNumber;              ///< Indicates the channel number
  UINT8             DimmNumber;                 ///< Indicates the channel number
  BOOLEAN           ShadowSpdValid;             ///< Indicates whether the DIMM is present in the last boot
  UINT8             Data[512];                  ///< Buffer for 256 Bytes of SPD data from DIMM
} SPD_DEF_STRUCT;

/////Start PsMemoryCOnfigurations.h
/*----------------------------------------------------------------------------------------
*          M I X E D   (Definitions And Macros / Typedefs, Structures, Enums)
*----------------------------------------------------------------------------------------
*/
#ifndef PSO_ENTRY
#define PSO_ENTRY UINT8
#endif

/*----------------------------------------------------------------------------------------
*                 D E F I N I T I O N S     A N D     M A C R O S
*----------------------------------------------------------------------------------------
*/
/*----------------------------------------------------------------------------------------
*               T Y P E D E F S,   S T R U C T U R E S,    E N U M S
*----------------------------------------------------------------------------------------
*/
/*----------------------------------------------------------------------------------------
*                 PLATFORM SPECIFIC MEMORY DEFINITIONS
*----------------------------------------------------------------------------------------
*/
///
///  Memory Speed and DIMM Population Masks
///
///<  DDR Speed Masks
///<    Specifies the DDR Speed on a memory channel
///
#define ANY_SPEED 0xFFFFFFFFul
#define DDR400  ((UINT32) 1 << (DDR400_FREQUENCY  / 66))
#define DDR533  ((UINT32) 1 << (DDR533_FREQUENCY  / 66))
#define DDR667  ((UINT32) 1 << (DDR667_FREQUENCY  / 66))
#define DDR800  ((UINT32) 1 << (DDR800_FREQUENCY  / 66))
#define DDR1066 ((UINT32) 1 << (DDR1066_FREQUENCY / 66))
#define DDR1333 ((UINT32) 1 << (DDR1333_FREQUENCY / 66))
#define DDR1600 ((UINT32) 1 << (DDR1600_FREQUENCY / 66))
#define DDR1866 ((UINT32) 1 << (DDR1866_FREQUENCY / 66))
#define DDR2133 ((UINT32) 1 << (DDR2133_FREQUENCY / 66))
#define DDR2400 ((UINT32) 1 << (DDR2400_FREQUENCY / 66))
#define DDR2667 ((UINT32) 1 << (DDR2667_FREQUENCY / 66))
#define DDR2933 ((UINT32) 1 << (DDR2933_FREQUENCY / 66))
#define DDR3200 ((UINT32) 1 << (DDR3200_FREQUENCY / 66))
///
///<  DIMM POPULATION MASKS
///<    Specifies the DIMM Population on a channel (can be added together to specify configuration).
///<    ex. SR_DIMM0 + SR_DIMM1                       : Single Rank Dimm in slot 0 AND Slot 1
///<        SR_DIMM0 + DR_DIMM0 + SR_DIMM1 +DR_DIMM1  : Single OR Dual rank in Slot 0 AND Single OR Dual rank in Slot 1
///
#define ANY_       0xFF       ///< Any dimm configuration the current channel
#define SR_DIMM0   0x0001     ///< Single rank dimm in slot 0 on the current channel
#define SR_DIMM1   0x0010     ///< Single rank dimm in slot 1 on the current channel
#define SR_DIMM2   0x0100     ///< Single rank dimm in slot 2 on the current channel
#define SR_DIMM3   0x1000     ///< Single rank dimm in slot 3 on the current channel
#define DR_DIMM0   0x0002     ///< Dual rank dimm in slot 0 on the current channel
#define DR_DIMM1   0x0020     ///< Dual rank dimm in slot 1 on the current channel
#define DR_DIMM2   0x0200     ///< Dual rank dimm in slot 2 on the current channel
#define DR_DIMM3   0x2000     ///< Dual rank dimm in slot 3 on the current channel
#define QR_DIMM0   0x0004     ///< Quad rank dimm in slot 0 on the current channel
#define QR_DIMM1   0x0040     ///< Quad rank dimm in slot 1 on the current channel
#define QR_DIMM2   0x0400     ///< Quad rank dimm in slot 2 on the current channel
#define QR_DIMM3   0x4000     ///< Quad rank dimm in slot 3 on the current channel
#define LR_DIMM0   0x0001     ///< Lrdimm in slot 0 on the current channel
#define LR_DIMM1   0x0010     ///< Lrdimm in slot 1 on the current channel
#define LR_DIMM2   0x0100     ///< Lrdimm in slot 2 on the current channel
#define LR_DIMM3   0x1000     ///< Lrdimm in slot 3 on the current channel
#define ANY_DIMM0   0x000F    ///< Any Dimm combination in slot 0 on the current channel
#define ANY_DIMM1   0x00F0    ///< Any Dimm combination in slot 1 on the current channel
#define ANY_DIMM2   0x0F00    ///< Any Dimm combination in slot 2 on the current channel
#define ANY_DIMM3   0xF000    ///< Any Dimm combination in slot 3 on the current channel
///
///<  CS POPULATION MASKS
///<    Specifies the CS Population on a channel (can be added together to specify configuration).
///<    ex. CS0 + CS1                       : CS0 and CS1 apply to the setting
///
#define CS_ANY_       0xFF       ///< Any CS configuration
#define CS0_   0x01     ///< CS0 bit map mask
#define CS1_   0x02     ///< CS1 bit map mask
#define CS2_   0x04     ///< CS2 bit map mask
#define CS3_   0x08     ///< CS3 bit map mask
#define CS4_   0x10     ///< CS4 bit map mask
#define CS5_   0x20     ///< CS5 bit map mask
#define CS6_   0x40     ///< CS6 bit map mask
#define CS7_   0x80     ///< CS7 bit map mask
///
///< Number of Dimms on the current channel
///<   This is a mask used to indicate the number of dimms in a channel
///<   They can be added to indicate multiple conditions (i.e 1 OR 2 Dimms)
///
#define ANY_NUM     0xFF      ///< Any number of Dimms
#define NO_DIMM     0x00      ///< No Dimms present
#define ONE_DIMM    0x01      ///< One dimm Poulated on the current channel
#define TWO_DIMM    0x02      ///< Two dimms Poulated on the current channel
#define THREE_DIMM  0x04      ///< Three dimms Poulated on the current channel
#define FOUR_DIMM   0x08      ///< Four dimms Poulated on the current channel

///
///<  DIMM VOLTAGE MASKS
///
#define VOLT_ANY_   0xFF      ///< Any voltage configuration
#define VOLT1_5_    0x01      ///< Voltage 1.5V bit map mask
#define VOLT1_35_   0x02      ///< Voltage 1.35V bit map mask
#define VOLT1_25_   0x04      ///< Voltage 1.25V bit map mask

//
// < Not applicable
//
#define NA_ 0                 ///< Not applicable

/*----------------------------------------------------------------------------------------
*
* Platform Specific Override Definitions for Socket, Channel and Dimm
* This indicates where a platform override will be applied.
*
*----------------------------------------------------------------------------------------
*/
///
///< SOCKET MASKS
///<   Indicates associated processor sockets to apply override settings
///
#define ANY_SOCKET     0xFF    ///<  Apply to all sockets
#define SOCKET0        0x01    ///<  Apply to socket 0
#define SOCKET1        0x02    ///<  Apply to socket 1
#define SOCKET2        0x04    ///<  Apply to socket 2
#define SOCKET3        0x08    ///<  Apply to socket 3
#define SOCKET4        0x10    ///<  Apply to socket 4
#define SOCKET5        0x20    ///<  Apply to socket 5
#define SOCKET6        0x40    ///<  Apply to socket 6
#define SOCKET7        0x80    ///<  Apply to socket 7
///
///< CHANNEL MASKS
///<   Indicates Memory channels where override should be applied
///
#define ANY_CHANNEL    0xFF    ///<  Apply to all Memory channels
#define CHANNEL_A      0x01    ///<  Apply to Channel A
#define CHANNEL_B      0x02    ///<  Apply to Channel B
#define CHANNEL_C      0x04    ///<  Apply to Channel C
#define CHANNEL_D      0x08    ///<  Apply to Channel D
///
/// DIMM MASKS
///   Indicates Dimm Slots where override should be applied
///
#define ALL_DIMMS      0xFF    ///<  Apply to all dimm slots
#define DIMM0          0x01    ///<  Apply to Dimm Slot 0
#define DIMM1          0x02    ///<  Apply to Dimm Slot 1
#define DIMM2          0x04    ///<  Apply to Dimm Slot 2
#define DIMM3          0x08    ///<  Apply to Dimm Slot 3
///
/// REGISTER ACCESS MASKS
///   Not supported as an at this time
///
#define ACCESS_NB0     0x0
#define ACCESS_NB1     0x1
#define ACCESS_NB2     0x2
#define ACCESS_NB3     0x3
#define ACCESS_NB4     0x4
#define ACCESS_PHY     0x5
#define ACCESS_DCT_XT  0x6
///
/// MOTHER BOARD DESIGN LAYERS MASKS
///   Indicates the layer design of mother board
///
#define LAYERS_4     0x0
#define LAYERS_6     0x1
/*----------------------------------------------------------------------------------------
*
* Platform Specific Overriding Table Definitions
*
*----------------------------------------------------------------------------------------
*/

#define PSO_END           0     ///< Table End
#define PSO_CKE_TRI       1     ///< CKE Tristate Map
#define PSO_ODT_TRI       2     ///< ODT Tristate Map
#define PSO_CS_TRI        3     ///< CS Tristate Map
#define PSO_MAX_DIMMS     4     ///< Max Dimms per channel
#define PSO_CLK_SPEED     5     ///< Clock Speed
#define PSO_DIMM_TYPE     6     ///< Dimm Type
#define PSO_MEMCLK_DIS    7     ///< MEMCLK Disable Map
#define PSO_MAX_CHNLS     8     ///< Max Channels per Socket
#define PSO_BUS_SPEED     9     ///< Max Memory Bus Speed
#define PSO_MAX_CHIPSELS 10     ///< Max Chipsel per Channel
#define PSO_MEM_TECH     11     ///< Channel Memory Type
#define PSO_WL_SEED      12     ///< DDR3 Write Levelization Seed delay
#define PSO_RXEN_SEED    13     ///< Hardwared based RxEn seed
#define PSO_NO_LRDIMM_CS67_ROUTING 14     ///< CS6 and CS7 are not Routed to all Memoy slots on a channel for LRDIMMs
#define PSO_SOLDERED_DOWN_SODIMM_TYPE 15  ///< Soldered down SODIMM type
#define PSO_LVDIMM_VOLT1_5_SUPPORT 16     ///< Force LvDimm voltage to 1.5V
#define PSO_MIN_RD_WR_DATAEYE_WIDTH 17    ///< Min RD/WR dataeye width
#define PSO_CPU_FAMILY_TO_OVERRIDE 18     ///< CPU family signature to tell following PSO macros are CPU family dependent
#define PSO_MAX_SOLDERED_DOWN_DIMMS 19    ///< Max Soldered-down Dimms per channel
#define PSO_MEMORY_POWER_POLICY 20        ///< Memory power policy override
#define PSO_MOTHER_BOARD_LAYERS 21        ///< Mother board layer design

/*----------------------------------
* CONDITIONAL PSO SPECIFIC ENTRIES
*---------------------------------*/
// Condition Types
#define CONDITIONAL_PSO_MIN   100     ///< Start of Conditional Entry Types
#define PSO_CONDITION_AND     100     ///< And Block - Start of Conditional block
#define PSO_CONDITION_LOC     101     ///< Location - Specify Socket, Channel, Dimms to be affected
#define PSO_CONDITION_SPD     102     ///< SPD - Specify a specific SPD value on a Dimm on the channel
#define PSO_CONDITION_REG     103     //   Reserved
#define PSO_CONDITION_MAX     103     ///< End Of Condition Entry Types
// Action Types
#define PSO_ACTION_MIN        120     ///< Start of Action Entry Types
#define PSO_ACTION_ODT        120     ///< ODT values to override
#define PSO_ACTION_ADDRTMG    121     ///< Address/Timing values to override
#define PSO_ACTION_ODCCONTROL 122     ///< ODC Control values to override
#define PSO_ACTION_SLEWRATE   123     ///< Slew Rate value to override
#define PSO_ACTION_REG        124     //   Reserved
#define PSO_ACTION_SPEEDLIMIT 125     ///< Memory Bus speed Limit based on configuration
#define PSO_ACTION_MAX        125     ///< End of Action Entry Types
#define CONDITIONAL_PSO_MAX   139     ///< End of Conditional Entry Types

/*----------------------------------
* TABLE DRIVEN PSO SPECIFIC ENTRIES
*---------------------------------*/
// Condition descriptor
#define PSO_TBLDRV_CONFIG        200  ///< Configuration Descriptor

// Overriding entry types
#define PSO_TBLDRV_START         210  ///< Start of Table Driven Overriding Entry Types
#define PSO_TBLDRV_SPEEDLIMIT    210  ///< Speed Limit
#define PSO_TBLDRV_ODT_RTTNOM    211  ///< RttNom
#define PSO_TBLDRV_ODT_RTTWR     212  ///< RttWr
#define PSO_TBLDRV_ODTPATTERN    213  ///< Odt Patterns
#define PSO_TBLDRV_ADDRTMG       214  ///< Address/Timing values
#define PSO_TBLDRV_ODCCTRL       215  ///< ODC Control values
#define PSO_TBLDRV_SLOWACCMODE   216  ///< Slow Access Mode
#define PSO_TBLDRV_MR0_CL        217  ///< MR0[CL]
#define PSO_TBLDRV_MR0_WR        218  ///< MR0[WR]
#define PSO_TBLDRV_RC2_IBT       219  ///< RC2[IBT]
#define PSO_TBLDRV_RC10_OPSPEED  220  ///< RC10[Opearting Speed]
#define PSO_TBLDRV_LRDIMM_IBT    221  ///< LrDIMM IBT
#define PSO_TBLDRV_2D_TRAINING   222  ///< 2D training
#define PSO_TBLDRV_INVALID_TYPE  223  ///< Invalid Type
#define PSO_TBLDRV_END           223  ///< End of Table Driven Overriding Entry Types

/*----------------------------------------------------------------------------------------
*                 CONDITIONAL OVERRIDE TABLE MACROS
*----------------------------------------------------------------------------------------
*/
#define CPU_FAMILY_TO_OVERRIDE(CpuFamilyRevision) \
  PSO_CPU_FAMILY_TO_OVERRIDE, 4, \
  ((CpuFamilyRevision) & 0x0FF), (((CpuFamilyRevision) >> 8)& 0x0FF), (((CpuFamilyRevision) >> 16)& 0x0FF), (((CpuFamilyRevision) >> 24)& 0x0FF)

#define MEMCLK_DIS_MAP(SocketID, ChannelID, Bit0Map, Bit1Map, Bit2Map, Bit3Map, Bit4Map, Bit5Map, Bit6Map, Bit7Map) \
  PSO_MEMCLK_DIS, 11, SocketID, ChannelID, ALL_DIMMS, Bit0Map, Bit1Map, Bit2Map, Bit3Map, Bit4Map, Bit5Map, Bit6Map \
  , Bit7Map

#define CKE_TRI_MAP(SocketID, ChannelID, Bit0Map, Bit1Map, Bit2Map, Bit3Map) \
  PSO_CKE_TRI, 7, SocketID, ChannelID, ALL_DIMMS, Bit0Map, Bit1Map, Bit2Map, Bit3Map

#define ODT_TRI_MAP(SocketID, ChannelID, Bit0Map, Bit1Map, Bit2Map, Bit3Map) \
  PSO_ODT_TRI, 7, SocketID, ChannelID, ALL_DIMMS, Bit0Map, Bit1Map, Bit2Map, Bit3Map

#define CS_TRI_MAP(SocketID, ChannelID, Bit0Map, Bit1Map, Bit2Map, Bit3Map, Bit4Map, Bit5Map, Bit6Map, Bit7Map) \
  PSO_CS_TRI, 11, SocketID, ChannelID, ALL_DIMMS, Bit0Map, Bit1Map, Bit2Map, Bit3Map, Bit4Map, Bit5Map, Bit6Map, Bit7Map

#define NUMBER_OF_DIMMS_SUPPORTED(SocketID, ChannelID, NumberOfDimmSlotsPerChannel) \
  PSO_MAX_DIMMS, 4, SocketID, ChannelID, ALL_DIMMS, NumberOfDimmSlotsPerChannel

#define NUMBER_OF_SOLDERED_DOWN_DIMMS_SUPPORTED(SocketID, ChannelID, NumberOfSolderedDownDimmsPerChannel) \
  PSO_MAX_SOLDERED_DOWN_DIMMS, 4, SocketID, ChannelID, ALL_DIMMS, NumberOfSolderedDownDimmsPerChannel

#define NUMBER_OF_CHIP_SELECTS_SUPPORTED(SocketID, ChannelID, NumberOfChipSelectsPerChannel) \
  PSO_MAX_CHIPSELS, 4, SocketID, ChannelID, ALL_DIMMS, NumberOfChipSelectsPerChannel

#define NUMBER_OF_CHANNELS_SUPPORTED(SocketID, NumberOfChannelsPerSocket) \
  PSO_MAX_CHNLS, 4, SocketID, ANY_CHANNEL, ALL_DIMMS, NumberOfChannelsPerSocket

#define OVERRIDE_DDR_BUS_SPEED(SocketID, ChannelID, TimingMode, BusSpeed) \
  PSO_BUS_SPEED, 11, SocketID, ChannelID, ALL_DIMMS, TimingMode, (TimingMode >> 8), (TimingMode >> 16), (TimingMode >> 24), \
  BusSpeed, (BusSpeed >> 8), (BusSpeed >> 16), (BusSpeed >> 24)

#define DRAM_TECHNOLOGY(SocketID, MemTechType) \
  PSO_MEM_TECH, 7, SocketID, ANY_CHANNEL, ALL_DIMMS, MemTechType, (MemTechType >> 8), (MemTechType >> 16), (MemTechType >> 24)

#define WRITE_LEVELING_SEED(SocketID, ChannelID, DimmID, Byte0Seed, Byte1Seed, Byte2Seed, Byte3Seed, Byte4Seed, Byte5Seed, \
  Byte6Seed, Byte7Seed, ByteEccSeed) \
  PSO_WL_SEED, 12, SocketID, ChannelID, DimmID, Byte0Seed, Byte1Seed, Byte2Seed, Byte3Seed, Byte4Seed, Byte5Seed, \
  Byte6Seed, Byte7Seed, ByteEccSeed

#define HW_RXEN_SEED(SocketID, ChannelID, DimmID, Byte0Seed, Byte1Seed, Byte2Seed, Byte3Seed, Byte4Seed, Byte5Seed, \
  Byte6Seed, Byte7Seed, ByteEccSeed) \
  PSO_RXEN_SEED, 21, SocketID, ChannelID, DimmID, Byte0Seed, (Byte0Seed >> 8), Byte1Seed, (Byte1Seed >> 8), Byte2Seed, (Byte2Seed >> 8), \
  Byte3Seed, (Byte3Seed >> 8), Byte4Seed, (Byte4Seed >> 8), Byte5Seed, (Byte5Seed >> 8), Byte6Seed, (Byte6Seed >> 8), \
  Byte7Seed, (Byte7Seed >> 8), ByteEccSeed, (ByteEccSeed >> 8)

#define NO_LRDIMM_CS67_ROUTING(SocketID, ChannelID) \
  PSO_NO_LRDIMM_CS67_ROUTING, 4, SocketID, ChannelID, ALL_DIMMS, TRUE

#define SOLDERED_DOWN_SODIMM_TYPE(SocketID, ChannelID) \
  PSO_SOLDERED_DOWN_SODIMM_TYPE, 4, SocketID, ChannelID, ALL_DIMMS, TRUE

#define LVDIMM_FORCE_VOLT1_5_FOR_D0 \
  PSO_LVDIMM_VOLT1_5_SUPPORT, 4, ANY_SOCKET, ANY_CHANNEL, ALL_DIMMS, TRUE

#define MIN_RD_WR_DATAEYE_WIDTH(SocketID, ChannelID, MinRdDataeyeWidth, MinWrDataeyeWidth) \
  PSO_MIN_RD_WR_DATAEYE_WIDTH, 5, SocketID, ChannelID, ALL_DIMMS, MinRdDataeyeWidth, MinWrDataeyeWidth

#define MEMORY_POWER_POLICY_OVERRIDE(PowerPolicy) \
  PSO_MEMORY_POWER_POLICY, 4, ANY_SOCKET, ANY_CHANNEL, ALL_DIMMS, PowerPolicy

#define MOTHER_BOARD_LAYERS(Layers) \
  PSO_MOTHER_BOARD_LAYERS, 4, ANY_SOCKET, ANY_CHANNEL, ALL_DIMMS, Layers

#define MAX_NUMBER_PSO_TABLES 13
/*----------------------------------------------------------------------------------------
*                 CONDITIONAL OVERRIDE TABLE MACROS
*----------------------------------------------------------------------------------------
*/
#define CONDITION_AND \
  PSO_CONDITION_AND, 0

#define COND_LOC(SocketMsk, ChannelMsk, DimmMsk) \
  PSO_CONDITION_LOC, 3, SocketMsk, ChannelMsk, DimmMsk

#define COND_SPD(Byte, Mask, Value) \
  PSO_CONDITION_SPD, 3, Byte, Mask, Value

#define COND_REG(Access, Offset, Mask, Value) \
 PSO_CONDITION_REG, 11, Access, (Offset & 0x0FF), (Offset >> 8), \
   ((Mask) & 0x0FF), (((Mask) >> 8) & 0x0FF), (((Mask) >> 16) & 0x0FF), (((Mask) >> 24) & 0x0FF), \
   ((Value) & 0x0FF), (((Value) >> 8) & 0x0FF), (((Value) >> 16) & 0x0FF), (((Value) >> 24) & 0x0FF)

#define ACTION_ODT(Frequency, Dimms, QrDimms, DramOdt, QrDramOdt, DramDynOdt) \
  PSO_ACTION_ODT, 9, \
  ((Frequency) & 0x0FF), (((Frequency) >> 8)& 0x0FF), (((Frequency) >> 16)& 0x0FF), ((Frequency >> 24)& 0x0FF), \
  Dimms, QrDimms, DramOdt, QrDramOdt, DramDynOdt

#define ACTION_ADDRTMG(Frequency, DimmConfig, AddrTmg) \
  PSO_ACTION_ADDRTMG, 10, \
  ((Frequency) & 0x0FF), (((Frequency) >> 8)& 0x0FF), (((Frequency) >> 16)& 0x0FF), (((Frequency) >> 24)& 0x0FF), \
  ((DimmConfig) & 0x0FF), (((DimmConfig) >> 8) & 0x0FF), \
  (AddrTmg & 0x0FF), ((AddrTmg >> 8)& 0x0FF), ((AddrTmg >> 16)& 0x0FF), ((AddrTmg >> 24)& 0x0FF)

#define ACTION_ODCCTRL(Frequency, DimmConfig, OdcCtrl) \
  PSO_ACTION_ODCCONTROL, 10, \
  ((Frequency) & 0x0FF), (((Frequency) >> 8)& 0x0FF), (((Frequency) >> 16)& 0x0FF), (((Frequency) >> 24)& 0x0FF), \
  ((DimmConfig) & 0x0FF), (((DimmConfig) >> 8) & 0x0FF), \
  (OdcCtrl & 0x0FF), ((OdcCtrl >> 8)& 0x0FF), ((OdcCtrl >> 16)& 0x0FF), ((OdcCtrl >> 24)& 0x0FF)

#define ACTION_SLEWRATE(Frequency, DimmConfig, SlewRate) \
  PSO_ACTION_SLEWRATE, 10, \
  ((Frequency) & 0x0FF), (((Frequency) >> 8)& 0x0FF), (((Frequency) >> 16)& 0x0FF), (((Frequency) >> 24)& 0x0FF), \
  ((DimmConfig) & 0x0FF), (((DimmConfig) >> 8) & 0x0FF), \
  (SlewRate & 0x0FF), ((SlewRate >> 8)& 0x0FF), ((SlewRate >> 16)& 0x0FF), ((SlewRate >> 24)& 0x0FF)

#define ACTION_SPEEDLIMIT(DimmConfig, Dimms, SpeedLimit15, SpeedLimit135, SpeedLimit125) \
  PSO_ACTION_SPEEDLIMIT, 9, \
  ((DimmConfig) & 0x0FF), (((DimmConfig) >> 8) & 0x0FF), Dimms, \
  (SpeedLimit15 & 0x0FF), ((SpeedLimit15 >> 8)& 0x0FF), \
  (SpeedLimit135 & 0x0FF), ((SpeedLimit135 >> 8)& 0x0FF), \
  (SpeedLimit125 & 0x0FF), ((SpeedLimit125 >> 8)& 0x0FF)


#define MEMCLK_DIS_MAP_SIZE  13
#define CKE_TRI_MAP_SIZE  9
#define ODT_TRI_MAP_SIZE  9
#define CS_TRI_MAP_SIZE 13
#define NUMBER_OF_DIMMS_SUPPORTED_SIZE  6
#define NUMBER_OF_SOLDERED_DOWN_DIMMS_SUPPORTED_SIZE  6
#define NUMBER_OF_CHIP_SELECTS_SUPPORTED_SIZE  6
#define NUMBER_OF_CHANNELS_SUPPORTED_SIZE  6
#define OVERRIDE_DDR_BUS_SPEED_SIZE  13
#define DRAM_TECHNOLOGY_SIZE  9
#define SOLDERED_DOWN_SODIMM_TYPE_SIZE  6
#define MEMORY_POWER_POLICY_OVERRIDE_SIZE  6
#define MOTHER_BOARD_LAYERS_SIZE  6

/// End of PsMemoryConfigurations

///Mp.h

/// Type of an entry for Dram Term table
typedef struct {
  _4BYTE_ALIGN UINT32 Speed; ///< BitMap for the supported speed
  _1BYTE_ALIGN UINT8  Dimms; ///< BitMap for supported number of dimm
  _1BYTE_ALIGN UINT8  QR_Dimms; ///< BitMap for supported number of QR dimm
  _1BYTE_ALIGN UINT8  DramTerm; ///< DramTerm value
  _1BYTE_ALIGN UINT8  QR_DramTerm; ///< DramTerm value for QR
  _1BYTE_ALIGN UINT8  DynamicDramTerm; ///< Dynamic DramTerm
} DRAM_TERM_ENTRY;

/// Type of an entry for POR speed limit table
typedef struct {
  _2BYTE_ALIGN UINT16   DIMMRankType;  ///< Bitmap of Ranks
  _1BYTE_ALIGN UINT8    Dimms;  ///< Number of dimm
  _2BYTE_ALIGN UINT16    SpeedLimit_1_5V; ///< POR speed limit for 1.5V
  _2BYTE_ALIGN UINT16    SpeedLimit_1_35V; ///< POR speed limit for 1.35V
  _2BYTE_ALIGN UINT16    SpeedLimit_1_25V; ///< POR speed limit for 1.25V
} POR_SPEED_LIMIT;

/// UDIMM&RDIMM Max. Frequency
typedef union {
  struct {                       ///< PSCFG_MAXFREQ_ENTRY
    _1BYTE_ALIGN UINT8 DimmPerCh;             ///< Dimm slot per chanel
    _2BYTE_ALIGN UINT16 Dimms;              ///< Number of Dimms on a channel
    _2BYTE_ALIGN UINT16 SR;                 ///< Number of single-rank Dimm
    _2BYTE_ALIGN UINT16 DR;                 ///< Number of dual-rank Dimm
    _2BYTE_ALIGN UINT16 QR;                 ///< Number of quad-rank Dimm
    _2BYTE_ALIGN UINT16 Speed1_5V;            ///< Speed limit with voltage 1.5V
    _2BYTE_ALIGN UINT16 Speed1_35V;           ///< Speed limit with voltage 1.35V
    _2BYTE_ALIGN UINT16 Speed1_25V;           ///< Speed limit with voltage 1.25V
  } _MAXFREQ_ENTRY;
  struct {
    _1BYTE_ALIGN UINT8 DimmSlotPerCh;
    _2BYTE_ALIGN UINT16 CDN;                  ///< Condition
    _2BYTE_ALIGN UINT16 CDN1;                  ///< Condition
    _2BYTE_ALIGN UINT16 CDN2;                  ///< Condition
    _2BYTE_ALIGN UINT16 CDN3;                  ///< Condition
    _2BYTE_ALIGN UINT16 Speed[3];             ///< Speed limit
  } MAXFREQ_ENTRY;
} PSCFG_MAXFREQ_ENTRY;

///  LRDIMM Max. Frequency
typedef union {
  struct {                       ///< PSCFG_LR_MAXFREQ_ENTRY
    _1BYTE_ALIGN UINT8 DimmPerCh;             ///< Dimm slot per chanel
    _2BYTE_ALIGN UINT16 Dimms;              ///< Number of Dimms on a channel
    _2BYTE_ALIGN UINT16 LR;                ///< Number of LR-DIMM
    _2BYTE_ALIGN UINT16 Speed1_5V;            ///< Speed limit with voltage 1.5V
    _2BYTE_ALIGN UINT16 Speed1_35V;           ///< Speed limit with voltage 1.35V
    _2BYTE_ALIGN UINT16 Speed1_25V;           ///< Speed limit with voltage 1.25V
  } _LR_MAXFREQ_ENTRY;
  struct {
    _1BYTE_ALIGN UINT8 DimmSlotPerCh;
    _2BYTE_ALIGN UINT16 CDN;
    _2BYTE_ALIGN UINT16 CDN1;                  ///< Condition
    _2BYTE_ALIGN UINT16 CDN2;                  ///< Condition
    _2BYTE_ALIGN UINT16 CDN3;                  ///< Condition
    _2BYTE_ALIGN UINT16 Speed[3];
  } LR_MAXFREQ_ENTRY;
} PSCFG_LR_MAXFREQ_ENTRY;

/// UDIMM&RDIMM RttNom and RttWr
typedef struct {
  _8BYTE_ALIGN UINT64 DimmPerCh;          ///< Dimm slot per chanel
  _8BYTE_ALIGN UINT64 DDRrate;           ///< Bitmap of DDR rate
  _8BYTE_ALIGN UINT64 VDDIO;              ///< Bitmap of VDDIO
  _8BYTE_ALIGN UINT64 Dimm0;              ///< Bitmap of rank type of Dimm0
  _8BYTE_ALIGN UINT64 Dimm1;              ///< Bitmap of rank type of Dimm1
  _8BYTE_ALIGN UINT64 Dimm2;              ///< Bitmap of rank type of Dimm2
  _8BYTE_ALIGN UINT64 Dimm;               ///< Bitmap of rank type of Dimm
  _8BYTE_ALIGN UINT64 Rank;               ///< Bitmap of rank
  _1BYTE_ALIGN UINT8 RttNom;              ///< Dram term
  _1BYTE_ALIGN UINT8 RttWr;               ///< Dynamic dram term
} PSCFG_RTT_ENTRY;

/// LRDIMM RttNom and RttWr
typedef struct {
  _8BYTE_ALIGN UINT64 DimmPerCh;          ///< Dimm slot per chanel
  _8BYTE_ALIGN UINT64 DDRrate;           ///< Bitmap of DDR rate
  _8BYTE_ALIGN UINT64 VDDIO;              ///< Bitmap of VDDIO
  _8BYTE_ALIGN UINT64 Dimm0;              ///< Dimm0 population
  _8BYTE_ALIGN UINT64 Dimm1;              ///< Dimm1 population
  _8BYTE_ALIGN UINT64 Dimm2;             ///< Dimm2 population
  _1BYTE_ALIGN UINT8 RttNom;              ///< Dram term
  _1BYTE_ALIGN UINT8 RttWr;               ///< Dynamic dram term
} PSCFG_LR_RTT_ENTRY;

/// UDIMM&RDIMM&LRDIMM ODT pattern OF 1 DPC
typedef struct {
  _4BYTE_ALIGN UINT32 Dimm0;              ///< Bitmap of dimm0 rank type or dimm0 population of LRDIMM
  _4BYTE_ALIGN UINT32 ODTPatCS0;          ///< ODT Pattern for CS0
  _4BYTE_ALIGN UINT32 ODTPatCS1;          ///< ODT Pattern for CS1
  _4BYTE_ALIGN UINT32 ODTPatCS2;          ///< ODT Pattern for CS2
  _4BYTE_ALIGN UINT32 ODTPatCS3;          ///< ODT Pattern for CS3
} PSCFG_1D_ODTPAT_ENTRY;

/// UDIMM&RDIMM&LRDIMM ODT pattern OF 2 DPC
typedef struct {
  UINT32 Dimm0:4;            ///< Bitmap of dimm0 rank type or dimm0 population of LRDIMM
  UINT32 Dimm1:28;           ///< Bitmap of dimm1 rank type or dimm1 population of LRDIMM
  UINT32 ODTPatCS0;          ///< ODT Pattern for CS0
  UINT32 ODTPatCS1;          ///< ODT Pattern for CS1
  UINT32 ODTPatCS2;          ///< ODT Pattern for CS2
  UINT32 ODTPatCS3;          ///< ODT Pattern for CS3
} PSCFG_2D_ODTPAT_ENTRY;

/// UDIMM&RDIMM&LRDIMM ODT pattern OF 3 DPC
typedef struct {
  UINT32 Dimm0:4;            ///< Bitmap of dimm0 rank type or dimm0 population of LRDIMM
  UINT32 Dimm1:4;            ///< Bitmap of dimm1 rank type or dimm1 population of LRDIMM
  UINT32 Dimm2:24;           ///< Bitmap of dimm2 rank type or dimm2 population of LRDIMM
  UINT32 ODTPatCS0;          ///< ODT Pattern for CS0
  UINT32 ODTPatCS1;          ///< ODT Pattern for CS1
  UINT32 ODTPatCS2;          ///< ODT Pattern for CS2
  UINT32 ODTPatCS3;          ///< ODT Pattern for CS3
} PSCFG_3D_ODTPAT_ENTRY;

/// UDIMM&RDIMM&LRDIMM SlowMode, AddrTmgCtl and ODC
typedef struct {
  _8BYTE_ALIGN UINT64 DimmPerCh;          ///< Dimm slot per channel
  _8BYTE_ALIGN UINT64 DDRrate;           ///< Bitmap of DDR rate
  _8BYTE_ALIGN UINT64 VDDIO;              ///< Bitmap of VDDIO
  _8BYTE_ALIGN UINT64 Dimm0;              ///< Bitmap of dimm0 rank type or dimm0 population of LRDIMM
  _8BYTE_ALIGN UINT64 Dimm1;              ///< Bitmap of dimm1 rank type or dimm1 population of LRDIMM
  _8BYTE_ALIGN UINT64 Dimm2;             ///< Bitmap of dimm2 rank type or dimm2 population of LRDIMM
  _8BYTE_ALIGN UINT64 SlowMode;           ///< SlowMode
  _4BYTE_ALIGN UINT32 AddTmgCtl;            ///< AddTmgCtl
  _4BYTE_ALIGN UINT32 ODC;                  ///< ODC
  _1BYTE_ALIGN UINT8 POdtOff;               ///< POdtOff
} PSCFG_SAO_ENTRY;

/// UDIMM&RDIMM&LRDIMM 2D training config entry
typedef struct {
  _8BYTE_ALIGN UINT64 DimmPerCh;          ///< Dimm per channel
  _8BYTE_ALIGN UINT64 DDRrate;           ///< Bitmap of DDR rate
  _8BYTE_ALIGN UINT64 VDDIO;              ///< Bitmap of VDDIO
  _8BYTE_ALIGN UINT64 Dimm0;              ///< Bitmap of dimm0 rank type or dimm0 population of LRDIMM
  _8BYTE_ALIGN UINT64 Dimm1;              ///< Bitmap of dimm1 rank type or dimm1 population of LRDIMM
  _8BYTE_ALIGN UINT64 Dimm2;             ///< Bitmap of dimm2 rank type or dimm2 population of LRDIMM
  _8BYTE_ALIGN UINT64 Enable2D;           ///< SlowMode
} PSCFG_S2D_ENTRY;

/// UDIMM&RDIMM MR0[WR]
typedef struct {
  _1BYTE_ALIGN UINT8 Timing;                ///< Fn2_22C_dct[1:0][Twr]
  _1BYTE_ALIGN UINT8 Value;                 ///< MR0[WR] : bit0 - bit2 available
} PSCFG_MR0WR_ENTRY;

/// UDIMM&RDIMM MR0[CL]
typedef struct {
  _1BYTE_ALIGN UINT8 Timing;                ///< Fn2_200_dct[1:0][Tcl]
  _1BYTE_ALIGN UINT8 Value;               ///< MR0[CL] : bit0 - bit2 CL[3:1]
  _1BYTE_ALIGN UINT8 Value1;              ///< MR0[CL] : bit3 CL[0]
} PSCFG_MR0CL_ENTRY;

/// UDIMM&RDIMM MR2[IBT]
typedef struct {
  _8BYTE_ALIGN UINT64 DimmPerCh;          ///< Dimm per channel
  _8BYTE_ALIGN UINT64 DDRrate;           ///< Bitmap of DDR rate
  _8BYTE_ALIGN UINT64 VDDIO;              ///< Bitmap of VDDIO
  _8BYTE_ALIGN UINT64 Dimm0;              ///< Bitmap of dimm0 rank type
  _8BYTE_ALIGN UINT64 Dimm1;              ///< Bitmap of dimm1 rank type
  _8BYTE_ALIGN UINT64 Dimm2;              ///< Bitmap of dimm2 rank type
  _8BYTE_ALIGN UINT64 Dimm;               ///< Bitmap of rank type of Dimm
  _8BYTE_ALIGN UINT64 NumOfReg;           ///< Number of registers
  _8BYTE_ALIGN UINT64 IBT;                 ///< MR2[IBT] value
} PSCFG_MR2IBT_ENTRY;

/// UDIMM&RDIMM&LRDIMM Operating Speed
typedef struct {
  _4BYTE_ALIGN UINT32 DDRrate;              ///< Bitmap of DDR rate
  _1BYTE_ALIGN UINT8 OPSPD;                 ///< RC10[OperatingSpeed]
} PSCFG_OPSPD_ENTRY;

/// LRDIMM IBT
typedef struct {
  _8BYTE_ALIGN UINT64 DimmPerCh;          ///< Dimm per channel
  _8BYTE_ALIGN UINT64 DDRrate;           ///< Bitmap of DDR rate
  _8BYTE_ALIGN UINT64 VDDIO;              ///< Bitmap of VDDIO
  _8BYTE_ALIGN UINT64 Dimm0;              ///< Dimm0 population
  _8BYTE_ALIGN UINT64 Dimm1;              ///< Dimm1 population
  _8BYTE_ALIGN UINT64 Dimm2;              ///< Dimm2 population
  _8BYTE_ALIGN UINT64 F0RC8;              ///< F0RC8
  _8BYTE_ALIGN UINT64 F1RC0;              ///< F1RC0
  _8BYTE_ALIGN UINT64 F1RC1;              ///< F1RC1
  _8BYTE_ALIGN UINT64 F1RC2;              ///< F1RC2
} PSCFG_L_IBT_ENTRY;

/// LRDIMM F0RC13[NumPhysicalRanks]
typedef struct {
  _1BYTE_ALIGN UINT8 NumRanks : 3;            ///< NumRanks
  _1BYTE_ALIGN UINT8 NumPhyRanks : 5;         ///< NumPhyRanks
} PSCFG_L_NPR_ENTRY;

/// LRDIMM F0RC13[NumLogicalRanks]
typedef struct {
  _2BYTE_ALIGN UINT16 NumPhyRanks;        ///< NumPhyRanks
  _2BYTE_ALIGN UINT16 DramCap;            ///< DramCap
  _2BYTE_ALIGN UINT16 NumDimmSlot;        ///< NumDimmSlot
  _1BYTE_ALIGN UINT8 NumLogRanks;         ///< NumLogRanks
} PSCFG_L_NLR_ENTRY;

/// UDIMM&RDIMM&LRDIMM pass1 seed entry
typedef struct {
  _1BYTE_ALIGN UINT8 DimmPerCh;             ///< Dimm per channel
  _1BYTE_ALIGN UINT8 Channel;               ///< Channel#
  _2BYTE_ALIGN UINT16 SeedVal;              ///< Seed value
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
  PSCFG_CADBUS_DRAMDN,         ///< PSCFG_CADBUS_DRAMDN
  PSCFG_DATABUS,               ///< PSCFG_DATABUS
  PSCFG_DATABUS_DRAMDN,        ///< PSCFG_DATABUS_DRAMDN

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

/// Table header related definitions
typedef struct {
  PSCFG_TYPE PSCType;           ///< PSC Type
  DIMM_TYPE DimmType;           ///< Dimm Type
  NOD_SUPPORTED NumOfDimm;      ///< Numbef of dimm
  APCB_SOC_LOGICAL_ID LogicalCpuid;  ///< Logical Cpuid
  _1BYTE_ALIGN UINT8 PackageType;            ///< Package Type
  TECHNOLOGY_TYPE TechType;     ///< Technology type
  MB_LAYER_TYPE MotherboardLayer; ///< Motherboard layer type
  MB_POWER_TYPE MotherboardPower; ///< Motherboard power type
} PSC_TBL_HEADER;

/// Table entry
typedef struct {
  PSC_TBL_HEADER Header;        ///< PSC_TBL_HEADER
  _1BYTE_ALIGN UINT8 TableSize;              ///< Table size
  VOID *TBLPtr;                 ///< Pointer of the table
} PSC_TBL_ENTRY;

#define PT_DONT_CARE 0xFF
#define NP 1
#define V1_5  1
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
#define DEVWIDTH_16 1
#define DEVWIDTH_32 2

/// CAD Bus configuration
typedef struct {
  _4BYTE_ALIGN UINT32 DimmPerCh;     ///< Bitmap of Dimm slot per chanel
  _4BYTE_ALIGN UINT32 DDRrate;      ///< Bitmap of DDR rate
  _4BYTE_ALIGN UINT32 VDDIO;         ///< Bitmap of VDDIO
  _4BYTE_ALIGN UINT32 Dimm0;         ///< Bitmap of rank type of Dimm0
  _4BYTE_ALIGN UINT32 Dimm1;         ///< Bitmap of rank type of Dimm1

  _4BYTE_ALIGN UINT16 GearDownMode;  ///< GearDownMode
  _4BYTE_ALIGN UINT16 SlowMode;      ///< SlowMode
  _4BYTE_ALIGN UINT32 AddrCmdCtl;   ///< AddrCmdCtl

  _1BYTE_ALIGN UINT8  CkeStrength;     ///< CKE drive strength
  _1BYTE_ALIGN UINT8  CsOdtStrength;   ///< CS ODT drive strength
  _1BYTE_ALIGN UINT8  AddrCmdStrength; ///< Addr Cmd drive strength
  _1BYTE_ALIGN UINT8  ClkStrength;     ///< CLK drive strength
} PSCFG_CADBUS_ENTRY;

/// CAD Bus configuration for Soldered Down DRAM
typedef struct {
  _4BYTE_ALIGN UINT32 DimmPerCh;     ///< Bitmap of Dimm slot per chanel
  _4BYTE_ALIGN UINT32 DDRrate;       ///< Bitmap of DDR rate
  _4BYTE_ALIGN UINT32 VDDIO;         ///< Bitmap of VDDIO
  _4BYTE_ALIGN UINT32 Dimm0;         ///< Bitmap of rank type of Dimm0
  _4BYTE_ALIGN UINT32 DevWidth;      ///< Device Width

  _4BYTE_ALIGN UINT32 SlowMode;      ///< SlowMode
  _4BYTE_ALIGN UINT32 AddrCmdCtl;    ///< AddrCmdCtl

  _1BYTE_ALIGN UINT8  CkeStrength;     ///< CKE drive strength
  _1BYTE_ALIGN UINT8  CsOdtStrength;   ///< CS ODT drive strength
  _1BYTE_ALIGN UINT8  AddrCmdStrength; ///< Addr Cmd drive strength
  _1BYTE_ALIGN UINT8  ClkStrength;     ///< CLK drive strength
} PSCFG_DRAMDN_CADBUS_ENTRY;

/// On die termination encoding
typedef enum {
  ODT_OFF = 0,     ///<  0 On die termination disabled
  ODT_60 = 1,     ///<  1 60 ohms
  ODT_120 = 2,     ///<  2 120 ohms
  ODT_40 = 3,     ///<  3 40 ohms
  ODT_20 = 4,     ///<  4 20 ohms
  ODT_30 = 5,     ///<  5 30 ohms
} ODT_ENC;

/// DDR4 Rtt_Nom termination encoding
typedef enum {
  RTTNOM_OFF = 0, ///<  0 Rtt_Nom Disabled
  RTTNOM_60 = 1, ///<  1 60 ohms
  RTTNOM_120 = 2, ///<  2 120 ohms
  RTTNOM_40 = 3, ///<  3 40 ohms
  RTTNOM_240 = 4, ///<  4 240 ohms
  RTTNOM_48 = 5, ///<  5 48 ohms
  RTTNOM_80 = 6, ///<  5 80 ohms
  RTTNOM_34 = 7, ///<  5 34 ohms
} D4_RTT_NOM_ENC;

/// DDR4 Rtt_Wr termination encoding
typedef enum {
  RTTWR_OFF = 0, ///<  0 Rtt_Nom Disabled
  RTTWR_120 = 1, ///< 1 120 ohms
  RTTWR_240 = 2, ///<  2 24 ohms
  RTTWR_HIZ = 3, ///<  3 Hi-Z
  RTTWR_80 = 4, ///<  4 80 ohms
} D4_RTT_WR_ENC;

/// DDR4 Rtt_Park termination encoding
typedef enum {
  RTTPRK_OFF = 0, ///<  0 Rtt_Park Disabled
  RTTPRK_60 = 1, ///<  1 60 ohms
  RTTPRK_120 = 2, ///<  2 120 ohms
  RTTPRK_40 = 3, ///<  3 40 ohms
  RTTPRK_240 = 4, ///<  4 240 ohms
  RTTPRK_48 = 5, ///<  5 48 ohms
  RTTPRK_80 = 6, ///<  5 80 ohms
  RTTPRK_34 = 7, ///<  5 34 ohms
} D4_RTT_PRK_ENC;

/// DDR3 Data Bus configuration
typedef struct {
  _4BYTE_ALIGN UINT32 DimmPerCh;   ///< Bitmap of Dimm slot per chanel
  _4BYTE_ALIGN UINT32 DDRrate;    ///< Bitmap of DDR rate
  _4BYTE_ALIGN UINT32 VDDIO;       ///< Bitmap of VDDIO
  _4BYTE_ALIGN UINT32 Dimm0;       ///< Bitmap of rank type of Dimm0
  _4BYTE_ALIGN UINT32 Dimm1;       ///< Bitmap of rank type of Dimm1

  _4BYTE_ALIGN UINT32 RttNom;      ///< Rtt_Nom
  _4BYTE_ALIGN UINT32 RttWr;       ///< Rtt_Wr
  _4BYTE_ALIGN UINT32 DqStrength;  ///< Data drive strength
  _4BYTE_ALIGN UINT32 DqsStrength; ///< DQS drive strength
  _4BYTE_ALIGN UINT32 OdtStrength; ///< ODT drive strength
} PSCFG_DATABUS_ENTRY;

/// Data Bus configuration
typedef struct {
  _4BYTE_ALIGN UINT32 DimmPerCh;   ///< Bitmap of Dimm slot per chanel
  _4BYTE_ALIGN UINT32 DDRrate;    ///< Bitmap of DDR rate
  _4BYTE_ALIGN UINT32 VDDIO;       ///< Bitmap of VDDIO
  _4BYTE_ALIGN UINT32 Dimm0;       ///< Bitmap of rank type of Dimm0
  _4BYTE_ALIGN UINT32 DevWidth;    ///< Device Width

  _4BYTE_ALIGN UINT32 RttNom;      ///< Rtt_Nom
  _4BYTE_ALIGN UINT32 RttWr;       ///< Rtt_Wr
  _4BYTE_ALIGN UINT32 DqStrength;  ///< Data drive strength
  _4BYTE_ALIGN UINT32 DqsStrength; ///< DQS drive strength
  _4BYTE_ALIGN UINT32 OdtStrength; ///< ODT drive strength
} PSCFG_DRAMDN_DATABUS_ENTRY;

/// DDR4 Data Bus configuration
typedef struct {
  _4BYTE_ALIGN UINT8 DimmPerCh;    ///< Bitmap of Dimm slot per chanel
  _4BYTE_ALIGN UINT32 DDRrate;     ///< Bitmap of DDR rate
  _4BYTE_ALIGN UINT32 VDDIO;       ///< Bitmap of VDDIO
  _4BYTE_ALIGN UINT32 Dimm0;       ///< Bitmap of rank type of Dimm0
  _4BYTE_ALIGN UINT32 Dimm1;       ///< Bitmap of rank type of Dimm1

  _4BYTE_ALIGN UINT32 RttNom;      ///< Rtt_Nom
  _4BYTE_ALIGN UINT32 RttWr;       ///< Rtt_Wr
  _4BYTE_ALIGN UINT32 RttPark;     ///< Rtt_Park
  _4BYTE_ALIGN UINT32 DqStrength;  ///< Data drive strength
  _4BYTE_ALIGN UINT32 DqsStrength; ///< DQS drive strength
  _4BYTE_ALIGN UINT32 OdtStrength; ///< ODT drive strength
  _4BYTE_ALIGN UINT32 PMUPhyVref;  ///< Message Block Seed for Host Vref
  _4BYTE_ALIGN UINT32 VrefDq;      ///< Message Block Seed for DRAM MR6 Vref
} PSCFG_DATABUS_ENTRY_D4;

/// DDR4 TrnDly configuration
typedef struct {
  _4BYTE_ALIGN UINT8 DimmPerCh;    ///< Bitmap of Dimm slot per chanel
  _4BYTE_ALIGN UINT32 DDRrate;     ///< Bitmap of DDR rate
  _4BYTE_ALIGN UINT32 VDDIO;       ///< Bitmap of VDDIO
  _4BYTE_ALIGN UINT32 Dimm0;       ///< Bitmap of rank type of Dimm0
  _4BYTE_ALIGN UINT32 Dimm1;       ///< Bitmap of rank type of Dimm1

  _4BYTE_ALIGN UINT32 TrnDlyOpDct0;      ///< Train Dly Operation for DCT 0
  _4BYTE_ALIGN UINT32 TrnDlyOffsetDct0;  ///< Train Dly Offset for DCT 0
  _4BYTE_ALIGN UINT32 TrnDlyOpDct1;      ///< Train Dly Operation for DCT 1
  _4BYTE_ALIGN UINT32 TrnDlyOffsetDct1;  ///< Train Dly Offset for DCT 1
} PSCFG_TRNDLY_ENTRY_D4;

//end of Mp.h
// End of IDS Stuff


/*----------------------------------------------------------------------------
 *                         TYPEDEFS, STRUCTURES, ENUMS
 *
 *----------------------------------------------------------------------------
 */
#define APCB_HEADER_VERSION     0x00000029  // APCB Version

#define APCB_MAX_SOCKETS_SUPPORTED 1  /// Max Sockets supproted by APCB
#define APCB_MAX_CHANNEL_PER_SOCKET 2
#define APCB_MAX_DIMMS_PER_CHANNEL  2
#define APCB_TOTAL_SYSTEM_DIMMS  (APCB_MAX_SOCKETS_SUPPORTED * APCB_MAX_CHANNEL_PER_SOCKET * APCB_MAX_DIMMS_PER_CHANNEL)
#define APCB_TYPE_DATA_START_SIGNATURE()    _16BYTE_ALIGN CHAR8 SigStartTypeData[16] = { '$', 'A', 'P', 'C', 'B', '_', 'T', 'Y', 'P', 'E', '_', 'S', 'T', 'A', 'R', 'T' }
#define APCB_TYPE_DATA_END_SIGNATURE()      _4BYTE_ALIGN CHAR8 SigEndTypeData[16]   = { '$', 'A', 'P', 'C', 'B', '_', 'T', 'Y', 'P', 'E', '_', 'E', 'N', 'D', '_', '$' }

//
// Group Id and Type Id for Memory Specific Data
//

#define APCB_GROUP_PSP                                 0x1701
#define APCB_GROUP_CCX                                 0x1702
#define APCB_GROUP_DF                                  0x1703
#define APCB_GROUP_MEMORY                              0x1704
#define APCB_GROUP_GNB                                 0x1705
#define APCB_GROUP_FCH                                 0x1706
#define APCB_GROUP_CBS                                 0x1707

#define APCB_ENABLED                                   1
#define APCB_MANUAL                                    1
#define APCB_AUTO_U8                                   0xFF
#define APCB_AUTO_U16                                  0xFFFF
#define APCB_AUTO_U32                                  0xFFFFFFFFul
#define APCB_AUTO_U64                                  0xFFFFFFFFFFFFFFFFull

typedef enum {
  APCB_PSP_TYPE_CONFIG_DEFAULT_PARAMETERS     = 1,
  APCB_PSP_TYPE_CONFIG_PARAMETERS,
  APCB_CCX_TYPE_CONFIG_DEFAULT_PARAMETERS     = 3,
  APCB_CCX_TYPE_CONFIG_PARAMETERS,
  APCB_DF_TYPE_CONFIG_DEFAULT_PARAMETERS      = 5,
  APCB_DF_TYPE_CONFIG_PARAMETERS,
  APCB_MEM_TYPE_CONFIG_DEFAULT_PARAMETERS     = 7,
  APCB_MEM_TYPE_CONFIG_PARAMETERS,
  APCB_GNB_TYPE_CONFIG_DEFAULT_PARAMETERS     = 9,
  APCB_GNB_TYPE_CONFIG_PARAMETERS,
  APCB_FCH_TYPE_CONFIG_DEFAULT_PARAMETERS     = 11,
  APCB_FCH_TYPE_CONFIG_PARAMETERS,
  APCB_TYPE_CBS_COMMON_PARAMETERS             = 13,
  APCB_TYPE_CBS_COMMON_DUMMY_PARAMETERS,
  APCB_TYPE_CBS_DEBUG_PARAMETERS              = 15,
  APCB_TYPE_CBS_DEBUG_DUMMY_PARAMETERS,

  APCB_MEM_TYPE_SPD_INFO                      = 0x0030,
  APCB_MEM_TYPE_DIMM_INFO_SMBUS               = 0x0031,
  APCB_MEM_TYPE_MEM_OVERCLOCK_CONFIG          = 0x0033,

  APCB_MEM_TYPE_PSO_DATA                      = 0x0040,
  APCB_MEM_TYPE_PS_UDIMM_DDR4_ODT_PAT         = 0x0041,
  APCB_MEM_TYPE_PS_UDIMM_DDR4_CAD_BUS         = 0x0042,
  APCB_MEM_TYPE_PS_UDIMM_DDR4_DATA_BUS        = 0x0043,
  APCB_MEM_TYPE_PS_UDIMM_DDR4_MAX_FREQ        = 0x0044,
  APCB_MEM_TYPE_PS_UDIMM_DDR4_STRETCH_FREQ    = 0x0045,
  APCB_MEM_TYPE_PS_RDIMM_DDR4_ODT_PAT         = 0x0046,
  APCB_MEM_TYPE_PS_RDIMM_DDR4_CAD_BUS         = 0x0047,
  APCB_MEM_TYPE_PS_RDIMM_DDR4_DATA_BUS        = 0x0048,
  APCB_MEM_TYPE_PS_RDIMM_DDR4_MAX_FREQ        = 0x0049,
  APCB_MEM_TYPE_PS_RDIMM_DDR4_STRETCH_FREQ    = 0x004A,

  APCB_MEM_TYPE_CONSOLE_OUT_CONTROL           = 0x0050,
  APCB_MEM_TYPE_EVENT_CONTROL                 = 0x0051,
  APCB_MEM_TYPE_ERROR_OUT_EVENT_CONTROL       = 0x0052,
  APCB_MEM_TYPE_EXT_VOLTAGE_CONTROL           = 0x0053,

  APCB_MEM_TYPE_PS_LRDIMM_DDR4_ODT_PAT        = 0x0054,
  APCB_MEM_TYPE_PS_LRDIMM_DDR4_CAD_BUS        = 0x0055,
  APCB_MEM_TYPE_PS_LRDIMM_DDR4_DATA_BUS       = 0x0056,
  APCB_MEM_TYPE_PS_LRDIMM_DDR4_MAX_FREQ       = 0x0057,
  APCB_MEM_TYPE_PS_LRDIMM_DDR4_STRETCH_FREQ   = 0x0058,

  APCB_MEM_TYPE_PS_SODIMM_DDR4_ODT_PAT        = 0x0059,
  APCB_MEM_TYPE_PS_SODIMM_DDR4_CAD_BUS        = 0x005A,
  APCB_MEM_TYPE_PS_SODIMM_DDR4_DATA_BUS       = 0x005B,
  APCB_MEM_TYPE_PS_SODIMM_DDR4_MAX_FREQ       = 0x005C,
  APCB_MEM_TYPE_PS_SODIMM_DDR4_STRETCH_FREQ   = 0x005D,

  APCB_PSP_TYPE_BOARD_ID_GETTING_METHOD       = 0x0060,

  APCB_MEM_TYPE_PS_DRAMDOWN_DDR4_ODT_PAT      = 0x0070,
  APCB_MEM_TYPE_PS_DRAMDOWN_DDR4_CAD_BUS      = 0x0071,
  APCB_MEM_TYPE_PS_DRAMDOWN_DDR4_DATA_BUS     = 0x0072,
  APCB_MEM_TYPE_PS_DRAMDOWN_DDR4_MAX_FREQ     = 0x0073,
  APCB_MEM_TYPE_PS_DRAMDOWN_DDR4_STRETCH_FREQ = 0x0074,

  APCB_MEM_TYPE_PS_UDIMM_DDR4_TX_DQ_DLY       = 0x0080,
  APCB_MEM_TYPE_PS_UDIMM_DDR4_RX_CLK_DLY      = 0x0081,
  APCB_MEM_TYPE_PS_SODIMM_DDR4_TX_DQ_DLY      = 0x0082,
  APCB_MEM_TYPE_PS_SODIMM_DDR4_RX_CLK_DLY     = 0x0083,
} APCB_PARAM_TYPE;

/// CBS Items Start
#define BSU08(u8)     ((UINT8) (u8)  & 0xFF)
#define BSU16(u16)    ((UINT16) (u16) & 0xFF), (((UINT16) (u16) >> 8) & 0xFF)
#define BSU32(u32)    ((UINT32) (u32) & 0xFF), (((UINT32) (u32) >> 8) & 0xFF), (((UINT32) (u32) >> 16) & 0xFF), (((UINT32) (u32) >> 24) & 0xFF)
#define BSU64(u64)    ((UINT64) (u64) & 0xFF), (((UINT64) (u64) >> 8) & 0xFF), (((UINT64) (u64) >> 16) & 0xFF), (((UINT64) (u64) >> 24) & 0xFF), \
                      (((UINT64) (u64) >> 32) & 0xFF), (((UINT64) (u64) >> 40) & 0xFF), (((UINT64) (u64) >> 48) & 0xFF), (((UINT64) (u64) >> 56) & 0xFF)
#define BSBLN(bl)     ((UINT8) (bl)  & 0xFF)

//
// DF Type ID
//
#define APCB_DF_TYPE_XGMI_TX_EQ                     0x00D0
#define   APCB_DF_TYPE_XGMI_INSTANCE_SPEED_COMBINED   0   // Instance ID of 5.3G

//
// The enumerator should always grow at the end of the list of each component
// Obsolete tokens should be preserved to maintain backward compatibility
//
typedef enum {
  APCB_TOKEN_CONFIG_PSP_BEGIN = 0x0,
  APCB_TOKEN_CONFIG_PSP_END,
  APCB_TOKEN_CONFIG_CCX_BEGIN = 0x100,
  APCB_TOKEN_CONFIG_CCX_MIN_SEV_ASID,
  APCB_TOKEN_CONFIG_CCX_END,
  APCB_TOKEN_CONFIG_DF_BEGIN = 0x300,
  APCB_TOKEN_CONFIG_DF_GMI_ENCRYPT,
  APCB_TOKEN_CONFIG_DF_XGMI_ENCRYPT,
  APCB_TOKEN_CONFIG_DF_SAVE_RESTORE_MEM_ENCRYPT,
  APCB_TOKEN_CONFIG_DF_SYS_STORAGE_AT_TOP_OF_MEM,
  APCB_TOKEN_CONFIG_DF_PROBE_FILTER_ENABLE,
  APCB_TOKEN_CONFIG_DF_BOTTOMIO,
  APCB_TOKEN_CONFIG_DF_MEM_INTERLEAVING,
  APCB_TOKEN_CONFIG_DF_DRAM_INTERLEAVE_SIZE,
  APCB_TOKEN_CONFIG_DF_ENABLE_CHAN_INTLV_HASH,
  APCB_TOKEN_CONFIG_DF_PCI_MMIO_SIZE,
  APCB_TOKEN_CONFIG_DF_CAKE_CRC_THRESH_PERF_BOUNDS,
  APCB_TOKEN_CONFIG_DF_MEM_CLEAR,
  APCB_TOKEN_CONFIG_DF_END,
  APCB_TOKEN_CONFIG_MEM_BEGIN = 0x700,
  APCB_TOKEN_CONFIG_LIMITMEMORYTOBELOW1TB,
  APCB_TOKEN_CONFIG_USERTIMINGMODE,
  APCB_TOKEN_CONFIG_MEMCLOCKVALUE,
  APCB_TOKEN_CONFIG_ENABLEBANKINTLV,
  APCB_TOKEN_CONFIG_ENABLEECCFEATURE,
  APCB_TOKEN_CONFIG_ENABLEPOWERDOWN,
  APCB_TOKEN_CONFIG_ENABLEPARITY,
  APCB_TOKEN_CONFIG_ENABLEBANKSWIZZLE,
  APCB_TOKEN_CONFIG_ENABLEMEMCLR,
  APCB_TOKEN_CONFIG_UMAMODE,
  APCB_TOKEN_CONFIG_UMASIZE,
  APCB_TOKEN_CONFIG_MEMRESTORECTL,
  APCB_TOKEN_CONFIG_FORCETRAINMODE,
  APCB_TOKEN_CONFIG_DIMMTYPEUSEDINMIXEDCONFIG,
  APCB_TOKEN_CONFIG_DRAMDOUBLEREFRESHRATE,
  APCB_TOKEN_CONFIG_PMUTRAINMODE,
  APCB_TOKEN_CONFIG_ECCREDIRECTION,
  APCB_TOKEN_CONFIG_ECCSYNCFLOOD,
  APCB_TOKEN_CONFIG_ECCSYMBOLSIZE,
  APCB_TOKEN_CONFIG_DQSTRAININGCONTROL,
  APCB_TOKEN_CONFIG_UMAABOVE4G,
  APCB_TOKEN_CONFIG_UMAALIGNMENT,
  APCB_TOKEN_CONFIG_MEMORYALLCLOCKSON,
  APCB_TOKEN_CONFIG_MEMORYBUSFREQUENCYLIMIT,
  APCB_TOKEN_CONFIG_POWERDOWNMODE,
  APCB_TOKEN_CONFIG_IGNORESPDCHECKSUM,
  APCB_TOKEN_CONFIG_MEMORYQUADRANKCAPABLE,
  APCB_TOKEN_CONFIG_MEMORYRDIMMCAPABLE,
  APCB_TOKEN_CONFIG_MEMORYLRDIMMCAPABLE,
  APCB_TOKEN_CONFIG_MEMORYUDIMMCAPABLE,
  APCB_TOKEN_CONFIG_MEMORYSODIMMCAPABLE,
  APCB_TOKEN_CONFIG_DRAMDOUBLEREFRESHRATEEN,
  APCB_TOKEN_CONFIG_DIMMTYPEDDDR4CAPABLE,
  APCB_TOKEN_CONFIG_DIMMTYPEDDDR3CAPABLE,
  APCB_TOKEN_CONFIG_DIMMTYPELPDDDR3CAPABLE,
  APCB_TOKEN_CONFIG_ENABLEBANKGROUPSWAP,
  APCB_TOKEN_CONFIG_ODTSCMDTHROTEN,
  APCB_TOKEN_CONFIG_SWCMDTHROTEN,
  APCB_TOKEN_CONFIG_FORCEPWRDOWNTHROTEN,
  APCB_TOKEN_CONFIG_ODTSCMDTHROTCYC,
  APCB_TOKEN_CONFIG_SWCMDTHROTCYC,
  APCB_TOKEN_CONFIG_DIMMSENSORCONF,
  APCB_TOKEN_CONFIG_DIMMSENSORUPPER,
  APCB_TOKEN_CONFIG_DIMMSENSORLOWER,
  APCB_TOKEN_CONFIG_DIMMSENSORCRITICAL,
  APCB_TOKEN_CONFIG_DIMMSENSORRESOLUTION,
  APCB_TOKEN_CONFIG_AUTOREFFINEGRANMODE,
  APCB_TOKEN_CONFIG_ENABLEMEMPSTATE,
  APCB_TOKEN_CONFIG_SOLDERDOWNDRAM,
  APCB_TOKEN_CONFIG_DDRROUTEBALANCEDTEE,
  APCB_TOKEN_CONFIG_MEM_MBIST_TEST_ENABLE,
  APCB_TOKEN_CONFIG_MEM_MBIST_SUBTEST_TYPE,
  APCB_TOKEN_CONFIG_MEM_MBIST_AGGRESOR_ON,
  APCB_TOKEN_CONFIG_MEM_MBIST_HALT_ON_ERROR,
  APCB_TOKEN_CONFIG_MEM_TSME_ENABLE,
  APCB_TOKEN_CONFIG_MEM_PS_ERROR_HANDLING,
  APCB_TOKEN_CONFIG_MEM_TEMP_CONTROLLED_REFRESH_EN,
  APCB_TOKEN_CONFIG_MEMRESTOREVALIDDAYS,
  APCB_TOKEN_CONFIG_DDR_ROUTE_BALANCED_TEE,
  APCB_TOKEN_CONFIG_MEM_FORCE_DATA_MASK_DISABLE,
  APCB_TOKEN_CONFIG_MEM_CPU_VREF_RANGE,
  APCB_TOKEN_CONFIG_MEM_DRAM_VREF_RANGE,
  APCB_TOKEN_CONFIG_MEM_MBIST_PER_BIT_SLAVE_DIE_REPORT,
  APCB_TOKEN_CONFIG_PMU_TRAIN_ERROR_RECOVERY,
  APCB_TOKEN_CONFIG_MEM_END,
  APCB_TOKEN_CONFIG_GNB_BEGIN = 0x1800,
  APCB_TOKEN_CONFIG_BMC_SOCKET_NUMBER,
  APCB_TOKEN_CONFIG_BMC_START_LANE,
  APCB_TOKEN_CONFIG_BMC_END_LANE,
  APCB_TOKEN_CONFIG_BMC_DEVICE,
  APCB_TOKEN_CONFIG_BMC_FUNCTION,
  APCB_TOKEN_CONFIG_PCIE_RESET_CONTROL,
  APCB_TOKEN_CONFIG_PCIE_RESET_GPIO_PIN,
  APCB_TOKEN_CONFIG_GNB_END,
  APCB_TOKEN_CONFIG_FCH_BEGIN = 0x1C00,
  APCB_TOKEN_CONFIG_FCH_CONSOLE_OUT_ENABLE,
  APCB_TOKEN_CONFIG_FCH_CONSOLE_OUT_SERIAL_PORT,
  APCB_TOKEN_CONFIG_FCH_ASSERT_ENABLE,
  APCB_TOKEN_CONFIG_FCH_TURTLE_BOOT_ENABLE,
  APCB_TOKEN_CONFIG_FCH_ELEVATE_SMBUS_CLOCK,
  APCB_TOKEN_CONFIG_FCH_UART_BAUD_RATE,
  APCB_TOKEN_CONFIG_FCH_ABL_DEBUG_PRINT_SERIAL_PORT_DETECT_EN,
  APCB_TOKEN_CONFIG_FCH_ESPI_ABL_INIT_ENABLE,
  APCB_TOKEN_CONFIG_FCH_ESPI_IO80_ENABLE,
  APCB_TOKEN_CONFIG_FCH_ESPI_KBC6064_ENABLE,
  APCB_TOKEN_CONFIG_FCH_ESPI_CLOCK,
  APCB_TOKEN_CONFIG_FCH_ESPI_IOMODE,
  APCB_TOKEN_CONFIG_FCH_ESPI_ALERT_MODE,
  APCB_TOKEN_CONFIG_FCH_ESPI_IORANGE0_SIZE,
  APCB_TOKEN_CONFIG_FCH_ESPI_IORANGE1_SIZE,
  APCB_TOKEN_CONFIG_FCH_ESPI_IORANGE2_SIZE,
  APCB_TOKEN_CONFIG_FCH_ESPI_IORANGE3_SIZE,
  APCB_TOKEN_CONFIG_FCH_ESPI_IORANGE0_BASE,
  APCB_TOKEN_CONFIG_FCH_ESPI_IORANGE1_BASE,
  APCB_TOKEN_CONFIG_FCH_ESPI_IORANGE2_BASE,
  APCB_TOKEN_CONFIG_FCH_ESPI_IORANGE3_BASE,
  APCB_TOKEN_CONFIG_FCH_ESPI_MMIORANGE0_SIZE,
  APCB_TOKEN_CONFIG_FCH_ESPI_MMIORANGE1_SIZE,
  APCB_TOKEN_CONFIG_FCH_ESPI_MMIORANGE2_SIZE,
  APCB_TOKEN_CONFIG_FCH_ESPI_MMIORANGE3_SIZE,
  APCB_TOKEN_CONFIG_FCH_ESPI_MMIORANGE0_BASE,
  APCB_TOKEN_CONFIG_FCH_ESPI_MMIORANGE1_BASE,
  APCB_TOKEN_CONFIG_FCH_ESPI_MMIORANGE2_BASE,
  APCB_TOKEN_CONFIG_FCH_ESPI_MMIORANGE3_BASE,
  APCB_TOKEN_CONFIG_FCH_END,
  APCB_TOKEN_CONFIG_LIMIT = 0x1FFF
} APCB_PARAM_CONFIG_TOKEN;

//
// CBS CMN APCB Tokens
//
#define APCB_TOKEN_CBS_CMN_BEGIN 0x0000
#define APCB_TOKEN_CBS_DF_CMN_GMI_ENCRYPTION 0x0001
#define APCB_TOKEN_CBS_DF_CMN_X_GMI_ENCRYPTION 0x0002
#define APCB_TOKEN_CBS_DF_CMN_CC6_MEM_ENCRYPTION 0x0003
#define APCB_TOKEN_CBS_DF_CMN_CC6_ALLOCATION_SCHEME 0x0004
#define APCB_TOKEN_CBS_DF_CMN_SYS_PROBE_FILTER 0x0005
#define APCB_TOKEN_CBS_DF_CMN_MEM_INTLV 0x0006
#define APCB_TOKEN_CBS_DF_CMN_MEM_INTLV_SIZE 0x0007
#define APCB_TOKEN_CBS_DF_CMN_CHNL_INTLV_HASH 0x0008
#define APCB_TOKEN_CBS_CMN_MEM_MAPPING_BANK_INTERLEAVE_DDR4 0x0009
#define APCB_TOKEN_CBS_CMN_MEM_CTRLLER_BANK_GROUP_SWAP_DDR4 0x000A
#define APCB_TOKEN_CBS_CMN_MEM_CTRLLER_BANK_SWIZZLE_DDR4 0x000B
#define APCB_TOKEN_CBS_CMN_MEM_ADDRESS_HASHING_DDR4 0x000C
#define APCB_TOKEN_CBS_CMN_MEM_SPEED_DDR4 0x000D
#define APCB_TOKEN_CBS_CMN_MEM_TIMING_TCL_DDR4 0x000E
#define APCB_TOKEN_CBS_CMN_MEM_TIMING_TRCDRD_DDR4 0x000F
#define APCB_TOKEN_CBS_CMN_MEM_TIMING_TRCDWR_DDR4 0x0010
#define APCB_TOKEN_CBS_CMN_MEM_TIMING_TRP_DDR4 0x0011
#define APCB_TOKEN_CBS_CMN_MEM_TIMING_TRAS_DDR4 0x0012
#define APCB_TOKEN_CBS_CMN_MEM_DATA_POISONING_DDR4 0x0013
#define APCB_TOKEN_CBS_CMN_MEM_ADDRESS_HASH_BANK_DDR4 0x0014
#define APCB_TOKEN_CBS_CMN_MEM_ADDRESS_HASH_CS_DDR4 0x0015
#define APCB_TOKEN_CBS_CMN_MEM_TSME_DDR4 0x0016
#define APCB_TOKEN_CBS_CMN_MEM_OVERCLOCK_DDR4 0x0017
#define APCB_TOKEN_CBS_CMN_GNB_GFX_UMA_MODE 0x0018
#define APCB_TOKEN_CBS_CMN_GNB_GFX_UMA_VERSION 0x0019
#define APCB_TOKEN_CBS_CMN_GNB_GFX_DISPLAY_RESOLUTION 0x001A
#define APCB_TOKEN_CBS_CMN_GNB_GFX_UMA_FRAME_BUFFER_SIZE 0x001B
#define APCB_TOKEN_CBS_CMN_CPU_SEV_ASID_SPACE_LIMIT 0x001C
#define APCB_TOKEN_CBS_CMN_MEM_SPD_READ_OPTIMIZATION_DDR4 0x001D
#define APCB_TOKEN_CBS_CMN_MEM_MBIST_EN 0x001E
#define APCB_TOKEN_CBS_CMN_MEM_MBIST_SUB_TEST 0x001F
#define APCB_TOKEN_CBS_DF_CMN_MEM_CLEAR 0x0020
#define APCB_TOKEN_CBS_CMN_MEM_TIMING_TRC_CTRL_DDR4 0x0021
#define APCB_TOKEN_CBS_CMN_MEM_TIMING_TRC_DDR4 0x0022
#define APCB_TOKEN_CBS_CMN_MEM_TIMING_TRRD_S_DDR4 0x0023
#define APCB_TOKEN_CBS_CMN_MEM_TIMING_TRRD_L_DDR4 0x0024
#define APCB_TOKEN_CBS_CMN_MEM_TIMING_TFAW_CTRL_DDR4 0x0025
#define APCB_TOKEN_CBS_CMN_MEM_TIMING_TFAW_DDR4 0x0026
#define APCB_TOKEN_CBS_CMN_MEM_TIMING_TWTR_S_DDR4 0x0027
#define APCB_TOKEN_CBS_CMN_MEM_TIMING_TWTR_L_DDR4 0x0028
#define APCB_TOKEN_CBS_CMN_MEM_TIMING_TWR_CTRL_DDR4 0x0029
#define APCB_TOKEN_CBS_CMN_MEM_TIMING_TWR_DDR4 0x002A
#define APCB_TOKEN_CBS_CMN_MEM_TIMING_TRCPAGE_CTRL_DDR4 0x002B
#define APCB_TOKEN_CBS_CMN_MEM_TIMING_TRCPAGE_DDR4 0x002C
#define APCB_TOKEN_CBS_CMN_MEM_TIMING_TRDRD_SC_L_CTRL_DDR4 0x002D
#define APCB_TOKEN_CBS_CMN_MEM_TIMING_TRDRD_SC_L_DDR4 0x002E
#define APCB_TOKEN_CBS_CMN_MEM_TIMING_TWRWR_SC_L_CTRL_DDR4 0x002F
#define APCB_TOKEN_CBS_CMN_MEM_TIMING_TWRWR_SC_L_DDR4 0x0030
#define APCB_TOKEN_CBS_CMN_MEM_TIMING_TRFC_CTRL_DDR4 0x0031
#define APCB_TOKEN_CBS_CMN_MEM_TIMING_TRFC_DDR4 0x0032
#define APCB_TOKEN_CBS_CMN_MEM_TIMING_TRFC2_CTRL_DDR4 0x0033
#define APCB_TOKEN_CBS_CMN_MEM_TIMING_TRFC2_DDR4 0x0034
#define APCB_TOKEN_CBS_CMN_MEM_TIMING_TRFC4_CTRL_DDR4 0x0035
#define APCB_TOKEN_CBS_CMN_MEM_TIMING_TRFC4_DDR4 0x0036
#define APCB_TOKEN_CBS_CMN_MEM_OVERCLOCK_FAIL_CNT 0x0037
#define APCB_TOKEN_CBS_CMN_MEM_CTRLLER_PROC_ODT_DDR4 0x0038
#define APCB_TOKEN_CBS_CMN_MEM_TIMING_TRDRD_SC_DDR4 0x0039
#define APCB_TOKEN_CBS_CMN_MEM_TIMING_TRDRD_SD_DDR4 0x003A
#define APCB_TOKEN_CBS_CMN_MEM_TIMING_TRDRD_DD_DDR4 0x003B
#define APCB_TOKEN_CBS_CMN_MEM_TIMING_TWRWR_SC_DDR4 0x003C
#define APCB_TOKEN_CBS_CMN_MEM_TIMING_TWRWR_SD_DDR4 0x003D
#define APCB_TOKEN_CBS_CMN_MEM_TIMING_TWRWR_DD_DDR4 0x003E
#define APCB_TOKEN_CBS_CMN_MEM_TIMING_TRDWR_DDR4 0x003F
#define APCB_TOKEN_CBS_CMN_MEM_TIMING_TWRRD_DDR4 0x0040
#define APCB_TOKEN_CBS_CMN_MEM_TIMING_TRTP_DDR4 0x0041
#define APCB_TOKEN_CBS_CMN_MEM_TIMING_TCWL_DDR4 0x0042
#define APCB_TOKEN_CBS_CMN_MEM_DATA_BUS_CONFIG_CTL_DDR4 0x0043
#define APCB_TOKEN_CBS_CMN_MEM_CTRLLER_RTT_NOM_DDR4 0x0044
#define APCB_TOKEN_CBS_CMN_MEM_CTRLLER_RTT_WR_DDR4 0x0045
#define APCB_TOKEN_CBS_CMN_MEM_CTRLLER_RTT_PARK_DDR4 0x0046
#define APCB_TOKEN_CBS_CMN_MEM_TIMING_TCKE_DDR4 0x0047
#define APCB_TOKEN_CBS_CMN_MEM_CTRLLER_DATA_SCRAMBLE_DDR4 0x0048
#define APCB_TOKEN_CBS_CMN_RESERVE_0049 0x0049
#define APCB_TOKEN_CBS_CMN_RESERVE_004A 0x004A
#define APCB_TOKEN_CBS_CMN_MEM_CTRLLER2_T_MODE_DDR4 0x004B
#define APCB_TOKEN_CBS_CMN_MEM_GEAR_DOWN_MODE_DDR4 0x004C
#define APCB_TOKEN_CBS_CMN_MEM_MBIST_AGGRESSORS 0x004D
#define APCB_TOKEN_CBS_CMN_MEM_MBIST_PER_BIT_SLAVE_DIE_REPORT 0x004E
#define APCB_TOKEN_CBS_CMN_MEM_CTRLLER_PWR_DN_EN_DDR4 0x004F
#define APCB_TOKEN_CBS_CMN_MEM_CAD_BUS_TIMING_CTL_DDR4 0x0050
#define APCB_TOKEN_CBS_CMN_MEM_ADDR_CMD_SETUP_DDR4 0x0051
#define APCB_TOKEN_CBS_CMN_MEM_CS_ODT_SETUP_DDR4 0x0052
#define APCB_TOKEN_CBS_CMN_MEM_CKE_SETUP_DDR4 0x0053
#define APCB_TOKEN_CBS_CMN_MEM_CAD_BUS_DRV_STREN_CTL_DDR4 0x0054
#define APCB_TOKEN_CBS_CMN_MEM_CAD_BUS_CLK_DRV_STREN_DDR4 0x0055
#define APCB_TOKEN_CBS_CMN_MEM_CAD_BUS_ADDR_CMD_DRV_STREN_DDR4 0x0056
#define APCB_TOKEN_CBS_CMN_MEM_CAD_BUS_CS_ODT_DRV_STREN_DDR4 0x0057
#define APCB_TOKEN_CBS_CMN_MEM_CAD_BUS_CKE_DRV_STREN_DDR4 0x0058
#define APCB_TOKEN_CBS_CPU_RELAXED_EDC_THROTTLING 0x0059
#define APCB_TOKEN_CBS_CMN_MEM_CTRLLER_BANK_GROUP_SWAP_ALT_DDR4 0x005A
#define APCB_TOKEN_CBS_CMN_RESERVE_005B 0x005B
#define APCB_TOKEN_CBS_CMN_MEM_OVERCLOCK_DIMM_CONFIG_CHECK 0x005C
#define APCB_TOKEN_CBS_CMN_MEM_CTRLLER_DRAM_ECC_EN_DDR4 0x005D
#define APCB_TOKEN_CBS_CMN_MEM_CTRLLER_DRAM_ECC_SYMBOL_SIZE_DDR4 0x005E
#define APCB_TOKEN_CBS_CMN_GNB_SOC_OVERCLOCK_VID 0x005F
#define APCB_TOKEN_CBS_CMN_GNB_FCLK_OC_FLAG 0x0060
#define APCB_TOKEN_CBS_CMN_MEM_DATA_MASK_DDR4 0x0061
#define APCB_TOKEN_CBS_CMN_MEM_CTRLLER_PMU_TRAIN_DFE_DDR4 0x0062
#define APCB_TOKEN_CBS_CMN_MEM_CTRLLER_PMU_TRAIN_FFE_DDR4 0x0063
#define APCB_TOKEN_CBS_CMN_PMU_PATTERN_BITS_CTRL_DDR4 0x0064
#define APCB_TOKEN_CBS_CMN_PMU_PATTERN_BITS_DDR4 0x0065
#define APCB_TOKEN_CBS_CMN_CLDO_VDDP_CTL 0x0066
#define APCB_TOKEN_CBS_CMN_CLDOVDD_PVOLTAGE 0x0067
#define APCB_TOKEN_CBS_CMN_GNBD_GPU_ENHANCED_MEMORY_MODE 0x0068
#define APCB_TOKEN_CBS_DF_CMN_UMA_ABOVE4_G 0x0069
#define APCB_TOKEN_CBS_CMN_SPD_SMBUS_VOLTAGE 0x6A
#define APCB_TOKEN_CBS_CMN_MEM_CTRLLER_DIS_BURST_PPND_REFRESH 0x006B
#define APCB_TOKEN_CBS_CMN_MEM_SUB_URG_REF_LOWER_BOUND 0x006C
#define APCB_TOKEN_CBS_CMN_MEM_URG_REF_LIMIT 0x006D
#define APCB_TOKEN_CBS_CMN_MEM_MAX_ACTIVATE_COUNT1 0x006E
#define APCB_TOKEN_CBS_CMN_MEM_DIS_MEM_ERR_INJ    0x006F
#define APCB_TOKEN_CBS_CMN_SOC_RPMC_CONTROL 0x0070
#define APCB_TOKEN_CBS_CMN_END 0x0071
#define APCB_TOKEN_CBS_CMN_LIMIT 0x1FFF

//
// CBS DBG APCB Tokens
//
#define APCB_TOKEN_CBS_DBG_BEGIN 0x0000
#define APCB_TOKEN_CBS_DF_DBG_CORE_MSTR_REQ_ORDERING 0x0001
#define APCB_TOKEN_CBS_DF_DBG_IO_MSTR_REQ_ORDERING 0x0002
#define APCB_TOKEN_CBS_DF_DBG_MEM_CANCEL_DIS 0x0003
#define APCB_TOKEN_CBS_DF_DBG_MIG_PRB_DIS 0x0004
#define APCB_TOKEN_CBS_DF_DBG_STOP_ON_SPF_ERROR 0x0005
#define APCB_TOKEN_CBS_DF_DBG_TCDX_BYPASS_DIS 0x0006
#define APCB_TOKEN_CBS_DF_DBG_F1F_FETCH_PRB_RMT 0x0007
#define APCB_TOKEN_CBS_DF_DBG_F1F_FETCH_PRB_LCL 0x0008
#define APCB_TOKEN_CBS_DF_DBG_F1F_FETCH_PRB_TARGET 0x0009
#define APCB_TOKEN_CBS_DF_DBG_SPF_WAY_DIS 0x000A
#define APCB_TOKEN_CBS_DF_DBG_IO_REQ_BUS_LOCK_CTRL 0x000B
#define APCB_TOKEN_CBS_DF_DBG_IOM_PERF_MON_PRB_RSP 0x000C
#define APCB_TOKEN_CBS_DF_DBG_IOM_PERF_MON_TGT_SEL 0x000D
#define APCB_TOKEN_CBS_DF_DBG_WDT_CTRL 0x000E
#define APCB_TOKEN_CBS_DF_DBG_CAKE_REQ_ADDR_COMPRESSION 0x000F
#define APCB_TOKEN_CBS_DF_DBG_CAKE_DATA_COMPRESSION 0x0010
#define APCB_TOKEN_CBS_DF_DBG_CAKE_RSP_CMD_PACKING 0x0011
#define APCB_TOKEN_CBS_DF_DBG_CAKE_PRB_COMBINING 0x0012
#define APCB_TOKEN_CBS_DF_DBG_CAKE_IO_ADDR_COMP_BIT 0x0013
#define APCB_TOKEN_CBS_DF_DBG_IO_BUS_LOCK_INV_DIS 0x0014
#define APCB_TOKEN_CBS_DF_DBG_PIE_PRQ_BCST_LIMIT 0x0015
#define APCB_TOKEN_CBS_DF_DBG_LMT_MAX_IO_REQ_MASTER 0x0016
#define APCB_TOKEN_CBS_DF_DBG_LMT_MAX_IO_REQ_LIMIT 0x0017
#define APCB_TOKEN_CBS_DF_DBG_IOS_RSP_BYPASS_CTRL 0x0018
#define APCB_TOKEN_CBS_DF_DBG_CAKE_BYPASS_CTRL 0x0019
#define APCB_TOKEN_CBS_DF_DBG_CS_BYPASS_CTRL 0x001A
#define APCB_TOKEN_CBS_DF_DBG_TGT_START_CTRL 0x001B
#define APCB_TOKEN_CBS_DF_DBG_LINK_ERR_INJ 0x001C
#define APCB_TOKEN_CBS_DF_DBG_VC8_TRACING_TOK_ALLOC 0x001D
#define APCB_TOKEN_CBS_DF_DBG_VC8_TRACING_REQ_CS 0x001E
#define APCB_TOKEN_CBS_DF_DBG_VC8_TRACING_REQ_IOMS 0x001F
#define APCB_TOKEN_CBS_DF_DBG_VC8_TRACING_CSQ 0x0020
#define APCB_TOKEN_CBS_DF_DBG_VC8_TRACING_RSP_IOMS 0x0021
#define APCB_TOKEN_CBS_DF_DBG_VC8_TRACING_RSP_TCDX 0x0022
#define APCB_TOKEN_CBS_DF_DBG_REDUCE_CREDITS_REQ 0x0023
#define APCB_TOKEN_CBS_DF_DBG_REDUCE_CREDITS_PRB 0x0024
#define APCB_TOKEN_CBS_DF_DBG_REDUCE_CREDITS_RSP 0x0025
#define APCB_TOKEN_CBS_DF_DBG_LOAD_STEP_CTRL_DIS 0x0026
#define APCB_TOKEN_CBS_DBG_MEM_TIMING_ENFORCE_FREQ_DDR4 0x0027
#define APCB_TOKEN_CBS_DBG_MEM_TIMING_CTL_DDR4 0x0028
#define APCB_TOKEN_CBS_DBG_MEM_SPEED_DDR4 0x0029
#define APCB_TOKEN_CBS_DBG_MEM_TIMING_UCLK_DIV1_M0_DDR4 0x002A
#define APCB_TOKEN_CBS_DBG_MEM_TIMING_UCLK_DIV1_M1_DDR4 0x002B
#define APCB_TOKEN_CBS_DBG_MEM_TIMING_UCLK_DIV1_M2_DDR4 0x002C
#define APCB_TOKEN_CBS_DBG_MEM_TIMING_UCLK_DIV1_M3_DDR4 0x002D
#define APCB_TOKEN_CBS_DBG_MEM_TIMING_TRC_CTL_DDR4 0x002E
#define APCB_TOKEN_CBS_DBG_MEM_TIMING_TRC_DDR4 0x002F
#define APCB_TOKEN_CBS_DBG_MEM_TIMING_TREF_CTL_DDR4 0x0030
#define APCB_TOKEN_CBS_DBG_MEM_TIMING_TREF_DDR4 0x0031
#define APCB_TOKEN_CBS_DBG_MEM_TIMING_TRWT_WB_DDR4 0x0032
#define APCB_TOKEN_CBS_DBG_MEM_TIMING_TRFC0_CTL_DDR4 0x0033
#define APCB_TOKEN_CBS_DBG_MEM_TIMING_TRFC0_DDR4 0x0034
#define APCB_TOKEN_CBS_DBG_MEM_TIMING_TRFC1_CTL_DDR4 0x0035
#define APCB_TOKEN_CBS_DBG_MEM_TIMING_TRFC1_DDR4 0x0036
#define APCB_TOKEN_CBS_DBG_MEM_TIMING_TCKSRX_CTL_DDR4 0x0037
#define APCB_TOKEN_CBS_DBG_MEM_TIMING_TCKSRX_DDR4 0x0038
#define APCB_TOKEN_CBS_DBG_MEM_TIMING_TCKSRE_CTL_DDR4 0x0039
#define APCB_TOKEN_CBS_DBG_MEM_TIMING_TCKSRE_DDR4 0x003A
#define APCB_TOKEN_CBS_DBG_MEM_TIMING_TPD_CTL_DDR4 0x003B
#define APCB_TOKEN_CBS_DBG_MEM_TIMING_TPD_DDR4 0x003C
#define APCB_TOKEN_CBS_DBG_MEM_CTRLLER_ADDR_CMD_TRI_EN_DDR4 0x003D
#define APCB_TOKEN_CBS_DBG_MEM_CTRLLER_ON_DIMM_TEMP_SENSOR_EN_DDR4 0x003E
#define APCB_TOKEN_CBS_DBG_MEM_CTRLLER_CMD_THROTTLE_MODE_CTL_DDR4 0x003F
#define APCB_TOKEN_CBS_DBG_MEM_CTRLLER_CMD_THROTTLE_MODE_DDR4 0x0040
#define APCB_TOKEN_CBS_DBG_MEM_CTRLLER_WR_CRC_EN_DDR4 0x0041
#define APCB_TOKEN_CBS_DBG_MEM_HW_HISTORY_MECH_DDR4 0x0042
#define APCB_TOKEN_CBS_DBG_MEM_DRAM_PARITY_DDR4 0x0043
#define APCB_TOKEN_CBS_DBG_MEM_RCD_PARITY_DDR4 0x0044
#define APCB_TOKEN_CBS_DBG_MEM_DBI_DDR4 0x0045
#define APCB_TOKEN_CBS_DBG_MEM_ADDR_TWEAK_EN_CTRL_DDR4 0x0046
#define APCB_TOKEN_CBS_DBG_MEM_ADDR_TWEAK_EN_DDR4 0x0047
#define APCB_TOKEN_CBS_DBG_MEM_DATA_ENCRYPTION_DDR4 0x0048
#define APCB_TOKEN_CBS_DBG_MEM_FORCE_ENCRYPTION_DDR4 0x0049
#define APCB_TOKEN_CBS_DBG_MEM_FINE_GRAN_REF_DDR4 0x004A
#define APCB_TOKEN_CBS_DBG_MEM_CTRLLER_PWR_DN_EN_DDR4 0x004B
#define APCB_TOKEN_CBS_DBG_MEM_CTRLLER_PWR_DN_MO_DDR4 0x004C
#define APCB_TOKEN_CBS_DBG_MEM_CTRLLER_PD_DLY_CTL_DDR4 0x004D
#define APCB_TOKEN_CBS_DBG_MEM_CTRLLER_PD_DLY_DDR4 0x004E
#define APCB_TOKEN_CBS_DBG_MEM_CTRLLER_AGGRESSIVE_PWR_DOWN_EN_DDR4 0x004F
#define APCB_TOKEN_CBS_DBG_MEM_CTRLLER_AGGRE_PD_DLY_CTL_DDR4 0x0050
#define APCB_TOKEN_CBS_DBG_MEM_CTRLLER_AGGRE_PD_DLY_DDR4 0x0051
#define APCB_TOKEN_CBS_DBG_MEM_CTRLLER_PHY_POWER_SAVING_DDR4 0x0052
#define APCB_TOKEN_CBS_DBG_MEM_CTRLLER_PD_PHY_POWER_SAVE_DIS_DDR4 0x0053
#define APCB_TOKEN_CBS_DBG_MEM_CTRLLER_PHY_RECEIVER_POWER_MODE_DDR4 0x0054
#define APCB_TOKEN_CBS_DBG_MEM_CTRLLER_MEM_PWR_POLICY_DDR4 0x0055
#define APCB_TOKEN_CBS_DBG_MEM_CTRLLER_ALL_MEM_CLKS_DDR4 0x0056
#define APCB_TOKEN_CBS_DBG_MEM_CTRLLER_ALL_CKE_DDR4 0x0057
#define APCB_TOKEN_CBS_DBG_MEM_CTRLLER_ALL_CS_DDR4 0x0058
#define APCB_TOKEN_CBS_DBG_MEM_DATA_POISONING_DDR4 0x0059
#define APCB_TOKEN_CBS_DBG_MEM_ADDR_CMD_PARITY_RETRY_DDR4 0x005A
#define APCB_TOKEN_CBS_DBG_MEM_ADDR_CMD_PARITY_ERROR_MAX_REPLAY_DDR4 0x005B
#define APCB_TOKEN_CBS_DBG_MEM_WRITE_CRC_RETRY_DDR4 0x005C
#define APCB_TOKEN_CBS_DBG_MEM_WRITE_CRC_ERROR_MAX_REPLAY_DDR4 0x005D
#define APCB_TOKEN_CBS_DBG_MEM_INJECT_TX_CMD_PARITY_ERRORS_DDR4 0x005E
#define APCB_TOKEN_CBS_DBG_MEM_CTRLLER_DRAM_ECC_SYMBOL_SIZE_DDR4 0x005F
#define APCB_TOKEN_CBS_DBG_MEM_CTRLLER_DRAM_ECC_EN_DDR4 0x0060
#define APCB_TOKEN_CBS_DBG_MEM_DATA_BUS_CONFIG_CTL_DDR4 0x0061
#define APCB_TOKEN_CBS_DBG_MEM_CTRLLER_DATA_DRV_STR_DDR4 0x0062
#define APCB_TOKEN_CBS_DBG_MEM_TIMING_A_RD_PTR_MP0_CTL_DDR4 0x0063
#define APCB_TOKEN_CBS_DBG_MEM_TIMING_A_RD_PTR_MP0_DDR4 0x0064
#define APCB_TOKEN_CBS_DBG_MEM_TIMING_A_RD_PTR_MP1_CTL_DDR4 0x0065
#define APCB_TOKEN_CBS_DBG_MEM_TIMING_A_RD_PTR_MP1_DDR4 0x0066
#define APCB_TOKEN_CBS_DBG_MEM_DFI_MRL_MARGIN_CTL_DDR4 0x0067
#define APCB_TOKEN_CBS_DBG_MEM_DFI_MRL_MARGIN_DDR4 0x0068
#define APCB_TOKEN_CBS_DBG_MEM_PER_RANK_TIMING_DDR4 0x0069
#define APCB_TOKEN_CBS_DBG_MEM_CTRLLER_PMU_TRAIN_MODE_DDR4 0x006A
#define APCB_TOKEN_CBS_DBG_MEM_CTRLLER_MR6_VREF_DQ_CTRL_DDR4 0x006B
#define APCB_TOKEN_CBS_DBG_MEM_CTRLLER_MR6_VREF_DQ_DDR4 0x006C
#define APCB_TOKEN_CBS_DBG_MEM_VREF_RANGE_DDR4 0x006D
#define APCB_TOKEN_CBS_DBG_CLDO_E12_GA 0x006E
#define APCB_TOKEN_CBS_DBG_CLDO_DDR 0x006F
#define APCB_TOKEN_CBS_DBG_CLDO_WAFL 0x0070
#define APCB_TOKEN_CBS_DBG_CLDO_E12_GB 0x0071
#define APCB_TOKEN_CBS_DBG_CLDO_VDDM0 0x0072
#define APCB_TOKEN_CBS_DBG_CLDO_VDDM1 0x0073
#define APCB_TOKEN_CBS_DBG_CLDO_VDDP_CTL 0x0074
#define APCB_TOKEN_CBS_DBG_CLDOVDD_PVOLTAGE 0x0075
#define APCB_TOKEN_CBS_DBG_CLDO_VDDM_CTL 0x0076
#define APCB_TOKEN_CBS_DBG_CLDOVDD_MVOLTAGE 0x0077
#define APCB_TOKEN_CBS_DBG_CPU_GEN_ABL_BP 0x0078
#define APCB_TOKEN_CBS_DBG_CPU_GEN_ABL_CON_OUT 0x0079
#define APCB_TOKEN_CBS_DBG_MEM_UMC_KEY0_DDR4 0x007A
#define APCB_TOKEN_CBS_DBG_MEM_CTRLLER_PMU_TRAIN_DFE_DDR4 0x007B
#define APCB_TOKEN_CBS_DBG_MEM_CTRLLER_PMU_TRAIN_FFE_DDR4 0x007C
#define APCB_TOKEN_CBS_DBG_GNB_DBGU_NBIO_PORT80_TRACING 0x007D
#define APCB_TOKEN_CBS_DBG_GNB_DBGU_NBIO_PORT80_TIMESTAMP 0x007E
#define APCB_TOKEN_CBS_DBG_GNB_RESERVED1 0x007F
#define APCB_TOKEN_CBS_DBG_GNB_RESERVED2 0x0080
#define APCB_TOKEN_CBS_DF_DBG_CAKE_TKN_THRESH 0x0081
#define APCB_TOKEN_CBS_DF_DBG_OPT_CAKE_DAT_LAT 0x0082
#define APCB_TOKEN_CBS_DF_DBG_CPU_MSTR_RCV_PRB_RSP 0x0083
#define APCB_TOKEN_CBS_DF_DBG_IO_MSTR_RCV_PRB_RSP 0x0084
#define APCB_TOKEN_CBS_DBG_CLDO_VDDM 0x0085
#define APCB_TOKEN_CBS_DBG_MEM_PSTATES_DDR4 0x0086
#define APCB_TOKEN_CBS_DBG_CBS_SMU_FCLKUCLK_MODE 0x0087
#define APCB_TOKEN_CBS_DBG_CLDO_VDDP 0x0088
#define APCB_TOKEN_CBS_DBG_VDDP_VOLTAGE_CTL 0x0089
#define APCB_TOKEN_CBS_DBG_VDDP_VOLTAGE 0x008A
#define APCB_TOKEN_CBS_DBG_VDDM_VOLTAGE_CTL 0x008B
#define APCB_TOKEN_CBS_DBG_VDDM_VOLTAGE 0x008C
#define APCB_TOKEN_CBS_DBG_MEM_TEMP_CTRL_REF_MODE_DDR4 0x008D
#define APCB_TOKEN_CBS_DBG_MEM_RRW_FOR_ALL_MSTATES_DDR4 0x008E
#define APCB_TOKEN_CBS_DBG_MEM_PHY_RX_EN_DLY_OVERRIDE_OP 0x008F
#define APCB_TOKEN_CBS_DBG_MEM_PHY_RX_EN_DLY_OVERRIDE_VALUE 0x0090
#define APCB_TOKEN_CBS_DBG_MEM_DATA_MASK_DDR4 0x0091
#define APCB_TOKEN_CBS_DBG_MEM_CTRLLER_CPU_VREF_TRAINING_SEED_CTRL_DDR4 0x0092
#define APCB_TOKEN_CBS_DBG_MEM_CTRLLER_CPU_VREF_TRAINING_SEED_DDR4 0x0093
#define APCB_TOKEN_CBS_DBG_MEM_RD_PREAMBLE_CRITICAL_SPEED_DDR4 0x0094
#define APCB_TOKEN_CBS_DBG_MEM_RD_PREAMBLE_MSTATE_BITMAP_DDR4 0x0095
#define APCB_TOKEN_CBS_DBG_MEM_WR_PREAMBLE_CRITICAL_SPEED_DDR4 0x0096
#define APCB_TOKEN_CBS_DBG_MEM_WR_PREAMBLE_MSTATE_BITMAP_DDR4 0x0097
#define APCB_TOKEN_CBS_DBG_MEM_CTRLLER_CUSTOM1_D_MSG_CTRL1 0x0098
#define APCB_TOKEN_CBS_DBG_MEM_CTRLLER1_D_MSG_OFFSET1 0x0099
#define APCB_TOKEN_CBS_DBG_MEM_CTRLLER1_D_MSG_DATA1 0x009A
#define APCB_TOKEN_CBS_DBG_MEM_CTRLLER_CUSTOM1_D_MSG_CTRL2 0x009B
#define APCB_TOKEN_CBS_DBG_MEM_CTRLLER1_D_MSG_OFFSET2 0x009C
#define APCB_TOKEN_CBS_DBG_MEM_CTRLLER1_D_MSG_DATA2 0x009D
#define APCB_TOKEN_CBS_DBG_MEM_CTRLLER_CUSTOM2_D_MSG_CTRL1 0x009E
#define APCB_TOKEN_CBS_DBG_MEM_CTRLLER2_D_MSG_OFFSET1 0x009F
#define APCB_TOKEN_CBS_DBG_MEM_CTRLLER2_D_MSG_DATA1 0x00A0
#define APCB_TOKEN_CBS_DBG_MEM_CTRLLER_CUSTOM2_D_MSG_CTRL2 0x00A1
#define APCB_TOKEN_CBS_DBG_MEM_CTRLLER2_D_MSG_OFFSET2 0x00A2
#define APCB_TOKEN_CBS_DBG_MEM_CTRLLER2_D_MSG_DATA2 0x00A3
#define APCB_TOKEN_CBS_DBG_MEM_PHY_RX_CLK_DLY_OVERRIDE_OP 0x00A4
#define APCB_TOKEN_CBS_DBG_MEM_PHY_RX_CLK_DLY_OVERRIDE_VALUE 0x00A5
#define APCB_TOKEN_CBS_DBG_MEM_PHY_VREF_DA_C1_OVERRIDE_OP 0x00A6
#define APCB_TOKEN_CBS_DBG_MEM_PHY_VREF_DA_C1_OVERRIDE_VALUE 0x00A7
#define APCB_TOKEN_CBS_DBG_CPU_PM_SC_THROTTLE 0x00A8
#define APCB_TOKEN_CBS_DBG_CPU_PM_SC_THROTTLE_CTRL 0x00A9
#define APCB_TOKEN_CBS_DBG_MEM_CTRLLER_DATA_SCRAMBLE_DDR4 0x00AA
#define APCB_TOKEN_CBS_DBG_MEM_CONTEXT_RESTORE 0x00AB
#define APCB_TOKEN_CBS_DBG_MEM_PHY_RX_PB_DLY_OVERRIDE_OP 0x00AC
#define APCB_TOKEN_CBS_DBG_MEM_PHY_RX_PB_DLY_OVERRIDE_VALUE 0x00AD
#define APCB_TOKEN_CBS_DBG_CPU_GEN_ABL_CON_DBG 0x00AE
#define APCB_TOKEN_CBS_DBG_MEM_VREF_DAC_PERBIT_CTL 0x00AF
#define APCB_TOKEN_CBS_DBG_MEM_VREF_DAC_BIT_MSK_LO0 0x00B0
#define APCB_TOKEN_CBS_DBG_MEM_VREF_DAC_BIT_MSK_HI0 0x00B1
#define APCB_TOKEN_CBS_DBG_MEM_VREF_DAC_SELECT0 0x00B2
#define APCB_TOKEN_CBS_DBG_MEM_VREF_DAC_STEP0 0x00B3
#define APCB_TOKEN_CBS_DBG_MEM_VREF_DAC_BIT_MSK_LO1 0x00B4
#define APCB_TOKEN_CBS_DBG_MEM_VREF_DAC_BIT_MSK_HI1 0x00B5
#define APCB_TOKEN_CBS_DBG_MEM_VREF_DAC_SELECT1 0x00B6
#define APCB_TOKEN_CBS_DBG_MEM_VREF_DAC_STEP1 0x00B7
#define APCB_TOKEN_CBS_DBG_MEM_VREF_DAC_BIT_MSK_LO2 0x00B8
#define APCB_TOKEN_CBS_DBG_MEM_VREF_DAC_BIT_MSK_HI2 0x00B9
#define APCB_TOKEN_CBS_DBG_MEM_VREF_DAC_SELECT2 0x00BA
#define APCB_TOKEN_CBS_DBG_MEM_VREF_DAC_STEP2 0x00BB
#define APCB_TOKEN_CBS_DBG_MEM_VREF_DAC_BIT_MSK_LO3 0x00BC
#define APCB_TOKEN_CBS_DBG_MEM_VREF_DAC_BIT_MSK_HI3 0x00BD
#define APCB_TOKEN_CBS_DBG_MEM_VREF_DAC_SELECT3 0x00BE
#define APCB_TOKEN_CBS_DBG_MEM_VREF_DAC_STEP3 0x00BF
#define APCB_TOKEN_CBS_DBG_MEM_VREF_DAC_UMC_SELECT0 0x00C0
#define APCB_TOKEN_CBS_DBG_MEM_VREF_DAC_UMC_SELECT1 0x00C1
#define APCB_TOKEN_CBS_DBG_MEM_VREF_DAC_UMC_SELECT2 0x00C2
#define APCB_TOKEN_CBS_DBG_MEM_VREF_DAC_UMC_SELECT3 0x00C3
#define APCB_TOKEN_CBS_DBG_MEM_PMU_TARGET_UMC_DDR4 0x00C4
#define APCB_TOKEN_CBS_DBG_MEM_PHY_TX_DQ_DLY_OVERRIDE_OP 0x00C5
#define APCB_TOKEN_CBS_DBG_MEM_PHY_TX_DQ_DLY_OVERRIDE_VALUE 0x00C6
#define APCB_TOKEN_CBS_DBG_MEM_ERROR_RECOVERY_DDR4 0x00C7
#define APCB_TOKEN_CBS_DBG_CPU_GEN_SYNC_FLOOD_MCA 0xC8
#define APCB_TOKEN_CBS_DBG_MEM_CTRLLER_DRAM_OUTPUT_DRV_DDR4 0x00C9
#define APCB_TOKEN_CBS_DBG_MEM_POWER_OPT_SETTING_DDR4 0x00CA
#define APCB_TOKEN_CBS_DBG_END 0x00CB
#define APCB_TOKEN_CBS_DBG_LIMIT 0x1FFF

typedef enum {
  APCB_TIME_POINT_NONE = 0,
  APCB_TIME_POINT_ANY = 1,
  APCB_TIME_POINT_BEFORE_DRAM_INIT,
  APCB_TIME_POINT_AFTER_DRAM_SPD_TIMING_INIT,
  APCB_TIME_POINT_AFTER_DRAM_DATASHEET_TIMING_INIT,
  APCB_TIME_POINT_AFTER_DRAM_PHY_INIT,
  APCB_TIME_POINT_AFTER_DRAM_INIT,
  APCB_TIME_POINT_BEFORE_PMU_TRAINING,
  APCB_TIME_POINT_AFTER_PMU_TRAINING,
  APCB_TIME_POINT_AFTER_DRAM_FINALIZATION,
  APCB_TIME_POINT_BEFORE_GMI_TRAINING,
  APCB_TIME_POINT_AFTER_GMI_TRAINING,
  APCB_TIME_POINT_AFTER_DF_FINAL_INIT,
  APCB_TIME_POINT_BEFORE_DF_SPF_INIT,
  APCB_TIME_POINT_BEFORE_DF_CREDIT_RELEASE,
  APCB_TIME_POINT_END
} APCB_TIME_POINT;

typedef struct {
  UINT32                TimePoint:8;  ///< Specify when the parameter can be retrieved
  UINT32                Token:13;
  UINT32                Size:3;       ///< The actual size of the parameter - 1
  UINT32                Reserved:8;
} APCB_PARAM_ATTRIBUTE;

typedef struct {
  UINT8                 *BaseAddr;   ///< Pointers to the value stream
} APCB_PARAM_BASE_ADDRESS;

typedef struct {
  UINT8                 Valid:1;      ///< Indicator if the map entry is valid
  UINT8                 Size:3;
  UINT8                 Reserved:4;
  UINT8                 TimePoint;
  UINT16                Offset;       ///< Offset to the parameter
                                      ///< within the APCB parameter block
} APCB_PARAM_MAP;

typedef struct {
  UINT16                ApcbTokenConfig;      ///< The APCB Config Token to be linked
  UINT16                ApcbTokenCbs;         ///< The APCB CBS Token to be linked
} APCB_LINKED_TOKENS;

///===============================================================================
/// Mempory Overclock configuration
#define MEM_OC_SAFE_BOOT_CONTROL_METHOD_DIS  0      ///< Safe Boot is disabled
#define MEM_OC_SAFE_BOOT_CONTROL_METHOD_G3   1      ///< Safe Boot is applied only when mechanical off
#define MEM_OC_SAFE_BOOT_CONTROL_METHOD_G2   2      ///< Safe Boot is applied only when soft-off or suspend to disk

typedef struct _MEM_OC_SAFE_BOOT_CONTROL_INDEX_IO_STRUCT {
  UINT32                          Size;
  UINT8                           Method;
  UINT8                           IndexPort;    ///< 72
  UINT8                           DataPort;     ///< 73
  UINT8                           Address;      ///< 0x04
  UINT8                           UnlockValue;  ///< 0x55
  UINT8                           LockValue;    ///< 0xAA
} MEM_OC_SAFE_BOOT_CONTROL_INDEX_IO_STRUCT;

#define MEM_OC_VDDIO_CONTROL_METHOD_DIS  0        ///< VDDIO Voltage Control is disabled
#define MEM_OC_VDDIO_CONTROL_METHOD_EN   1        ///< VDDIO Voltage Control is enabled when Memory OC mode
#define MEM_OC_VDDIO_CONTROL_METHOD_DEF  2        ///< VDDIO Voltage Control default initialization is enabled
#define MEM_OC_VDDIO_CONTROL_ACCESS_TYPE_DIS      0
#define MEM_OC_VDDIO_CONTROL_ACCESS_TYPE_INDEX_IO 1
#define MEM_OC_VDDIO_CONTROL_SMBUS_HC_0  0
#define MEM_OC_VDDIO_CONTROL_SMBUS_HC_1  1
#define MEM_OC_VDDIO_CONTROL_SMBUS_WRITE_BYTE 1
#define MEM_OC_VDDIO_CONTROL_SMBUS_WRITE_WORD 2
#define MEM_OC_VDDIO_CONTROL_SMBUS_ATTRIBUTE_FIXED     0   ///< From SmbusData0, SmbusData1
#define MEM_OC_VDDIO_CONTROL_SMBUS_ATTRIBUTE_UPDATABLE 1   ///< From IndexIo when Memory OC mode

typedef struct _MEM_OC_VDDIO_VOLT_CTRL_INFO {
  UINT8                           SmbusHc;
  UINT8                           SmbusAdderess;
  UINT8                           SmbusHostCmd;
  UINT8                           Operation;
  UINT8                           Attr;
  UINT8                           SmbusData0;
  UINT8                           SmbusData1;
} MEM_OC_VDDIO_VOLT_CTRL_INFO;

typedef struct _MEM_OC_VDDIO_VOLT_CTRL_INDEX_IO {
  UINT8                           AccessType;   ///< Index IO
  UINT8                           IndexPort;    ///< 72
  UINT8                           DataPort;     ///< 73
  UINT8                           Offset;       ///< 0x04
} MEM_OC_VDDIO_VOLT_CTRL_INDEX_IO;

typedef struct _MEM_OC_VDDIO_CONTROL_SMBUS_STRUCT {
  UINT32                          Size;
  UINT8                           Method;
  UINT8                           NumOfCtrlInfo;
  MEM_OC_VDDIO_VOLT_CTRL_INDEX_IO VoltCtrlIndexIoData0;
  MEM_OC_VDDIO_VOLT_CTRL_INDEX_IO VoltCtrlIndexIoData1;
  MEM_OC_VDDIO_VOLT_CTRL_INFO     VoltCtrlInfo[];
} MEM_OC_VDDIO_CONTROL_SMBUS_STRUCT;

typedef struct _MEM_OC_CONFIG_STRUCT {
  UINT32                                    Size;
  MEM_OC_SAFE_BOOT_CONTROL_INDEX_IO_STRUCT  SafeBootCtrlIndexIo;
  MEM_OC_VDDIO_CONTROL_SMBUS_STRUCT         MemVddioCtrl;
} MEM_OC_CONFIG_STRUCT;

///
/// Memory Board Layout Info
///
#define MEMORY_LAYOUT_TYPE_DIMM           1
#define MEMORY_LAYOUT_TYPE_ONBOARD        2

//-----------------------------------------------------------------------------
///
/// SPD Data for each DIMM.
///
typedef struct _DIMM_INFO {
  UINT8  DimmSlotPresent;     ///< Indicates that the DIMM is present and Data is valid
  UINT8  SocketId;            ///< Indicates the socket number
  UINT8  ChannelId;           ///< Indicates the channel number
  UINT8  DimmId;              ///< Indicates the channel number
  UINT8  DimmSmbusAdderess;   ///< SMBus address of the DRAM
  UINT8  I2CMuxAddress;       ///< I2C Mux Address
  UINT8  MuxControlAddress;
  UINT8  MuxChannel;          ///< I2C Mux Channel assocaited iwth this SPD
} DIMM_INFO_SMBUS;

 //-----


///===============================================================================
/// _PSP_PSC_DRAMDOWN_STRUCT
/// This data structure is used to pass wrapper parameters to the memory configuration code
///
typedef struct _PSP_PSO_STRUCT {
  PSO_ENTRY MemClkDisMap[MEMCLK_DIS_MAP_SIZE];
  PSO_ENTRY CkeTriMap[CKE_TRI_MAP_SIZE];
  PSO_ENTRY OdtTriMap[ODT_TRI_MAP_SIZE];
  PSO_ENTRY CsTriMap[CS_TRI_MAP_SIZE];
  PSO_ENTRY NumberDimmSupported[NUMBER_OF_DIMMS_SUPPORTED_SIZE];
  PSO_ENTRY NumberSolderedDownDimmsSupported[NUMBER_OF_SOLDERED_DOWN_DIMMS_SUPPORTED_SIZE];
  PSO_ENTRY NumberChipSelectsSupported[NUMBER_OF_CHIP_SELECTS_SUPPORTED_SIZE];
  PSO_ENTRY NumberChannelsSupported[NUMBER_OF_CHANNELS_SUPPORTED_SIZE];
  PSO_ENTRY OverrideBusSpeed[OVERRIDE_DDR_BUS_SPEED_SIZE];
  PSO_ENTRY DramTechnology[DRAM_TECHNOLOGY_SIZE];
  PSO_ENTRY SolderedDownSoDimmType[SOLDERED_DOWN_SODIMM_TYPE_SIZE];
  PSO_ENTRY MemoryPowerPolicyOverride[MEMORY_POWER_POLICY_OVERRIDE_SIZE];
  PSO_ENTRY MotherboardLayers[MOTHER_BOARD_LAYERS_SIZE];
} PSP_PSO_STRUCT;
///===============================================================================
/// _PSP_SPD_LPDDR3_STRUCT
/// This data structure is used to pass wrapper parameters to the memory configuration code
///
typedef struct _PSP_SPD_STRUCT {
   UINT32 TotalDimms;
  SPD_DEF_STRUCT  SpdData[APCB_TOTAL_SYSTEM_DIMMS];
} PSP_SPD_STRUCT;

/// HDTOUT Header.
typedef struct _HDTOUT_HEADER {
  UINT32 Signature;               ///< 0xDB1099CC
  UINT16 Version;                 ///< HDTOUT version.
  UINT16 BufferSize;              ///< Size in bytes.
  UINT16 DataIndex;               ///< Data Index.
  UINT8  PrintCtrl;               ///< 0 off no print  1 on print
  UINT8  NumBreakpointUnit;       ///< default 0 no bp unit others number of bp unit
  UINT32 FuncListAddr;            ///< 32 bit address to the list of functions that script can execute
  UINT8  ConsoleType;             ///< Console type - deprecated
  UINT8  Event;                   ///< Event type. - deprecated
  UINT8  OutBufferMode;           ///< Off:stack mode, On: heap mode - deprecated
  UINT32 EnableMask;              ///< Bitmap to select which part should be streamed out
  UINT64 ConsoleFilter;           ///< Filter use to select which part should be streamed out
  UINT8  BspOnlyFlag;             ///< 1 Only Enable Bsp output, 0 enable On All cores
  UINT8  Reserved[56 - 32];       ///< Reserved for header expansion

  CHAR8  BreakpointList[300];     ///< Breakpoint list
  CHAR8  StatusStr[156];          ///< Shows current node, DCT, CS,...
  CHAR8  Data[2];                 ///< HDTOUT content. Its size will be determined by BufferSize.
} HDTOUT_HEADER;


/// ABL Console Out Header.
typedef struct _ABL_CONSOLE_OUT_HEADER {
  BOOLEAN AblConsoleEnable;                     ///< Enable ABL Console output
                                                ///< TRUE - Enable ABL console output  (Default)
                                                ///< FALSE - Disable ABL console output
  UINT32  AblConsolePort;                       ///< 32 bit ABL Console output port (Default - 0x80)
  BOOLEAN AblConsoleFilterMemFlowEnable;        ///< ABL Console out filter for "MEM FLOW"    (Default - Enabled)
                                                ///< TRUE - Filter is enabled  (Default)
                                                ///< FALSE - Fitler is diesabed
  BOOLEAN AblConsoleFilterMemSetRegEnable;      ///< ABL Console out filter to enable "MEM SETREG" (Default - Enabled)
                                                ///< TRUE - Filter is enabled  (Default)
                                                ///< FALSE - Fitler is diesabed
  BOOLEAN AblConsoleFilterMemGetRegEnable;      ///< ABL Console out filter to enable "MEM GETREG"   (Default - disabled)
                                                ///< TRUE - Filter is enabled
                                                ///< FALSE - Fitler is diesabed (Default)
  BOOLEAN AblConsoleFilterMemStatusEnable;      ///< ABL Console out filter to enable "MEM STATUS"   (Default - disabled)
                                                ///< TRUE - Filter is enabled
                                                ///< FALSE - Fitler is diesabed (Default)
  BOOLEAN AblConsoleFilterMemPmuEnable;         ///< ABL Console out filter to enable "MEM PMU"   (Default - disabled)
                                                ///< TRUE - Filter is enabled
                                                ///< FALSE - Fitler is diesabed (Default)
  BOOLEAN AblConsoleFilterMemPmuSramReadEnable; ///< ABL Console out filter to enable "MEM PMU SRAM READ" (Default - disabled)
                                                ///< TRUE - Filter is enabled
                                                ///< FALSE - Fitler is diesabed (Default)
  BOOLEAN AblConsoleFilterMemPmuSramWriteEnable; ///< ABL Console out filter to enable "MEM PMU SRAM WRITE" (Default - disabled)
                                                 ///< TRUE - Filter is enabled
                                                 ///< FALSE - Fitler is diesabed (Default)
  BOOLEAN AblConsoleFilterMemTestVerboseEnable; ///< ABL Console out filter to enable "MEM TEST VERBOSE" (Default - disabled)
                                                ///< TRUE - Filter is enabled
                                                ///< FALSE - Fitler is diesabed (Default)
} ABL_CONSOLE_OUT_HEADER;

/// Breakpoint control
typedef struct _ABL_BREAKPOINT_CONTROL {
  BOOLEAN BreakPointEnable;      ///< Enable ABL Console output
                                 ///< TRUE - All dies will stop at the same breakpoints (Default)
                                 ///< FALSE - Master will only stop with breakpoints
  BOOLEAN BreakOnAllDies;        ///< Enable ABL Console output
                                 ///< TRUE - All dies will stop at the same breakpoints  (Default)
                                 ///< FALSE - Master will only stop with breakpoints
} ABL_BREAKPOINT_CONTROL;

///===============================================================================
/// PSP_CONSOLE_OUT_STRUCT
/// This data structure is used to control console output support
///
typedef struct _PSP_CONSOLE_OUT_STRUCT {
  ABL_CONSOLE_OUT_HEADER  ConsoleOutControl;    //< Control structure for Console out
  ABL_BREAKPOINT_CONTROL  BreakPointControl;    //< Control structure for Breakpoints
} PSP_CONSOLE_OUT_STRUCT;

///===============================================================================
/// PSP_EVENT_OUT_CONTROL_STRUCT
/// This data structure is used to control sending AGESA Event info to the specified port
///
typedef struct PSP_ERROR_OUT_CONTROL_STRUCT {
  IN
  BOOLEAN EVENT_OUT_PORT_ENABLED; ///< Indicates if AGESA PSP will output Event Info to specificed port
  IN
  BOOLEAN HALT_ON_CRITICAL_FATAL_EVENT_ENABLED; ///< Indicates if AGESA PSP will halt on critical/fatal event
  IN
  UINT64  EventInfoPort;    //< Port to output AGESA Event Info
} PSP_EVENT_OUT_CONTROL_STRUCT;

///===============================================================================
/// ERROR_ABL_GPIO
/// This data structure is user-defined GPIO indicator of a failure
///
typedef struct _ERROR_ABL_GPIO {
  UINT8     Gpio;          ///< FCH GPIO number of failure indicator
  UINT8     GpioIoMUX;     ///< Value write to IOMUX to configure this GPIO pin
  UINT8     GpioBankCtl;   ///< Value write to GPIOBankCtl[23:16] to configure this GPIO pin
} ERROR_ABL_GPIO;

///===============================================================================
/// ERROR_BEEP_CODE_TABLE
/// This data structure can be customized/enhanced as per platform need
///
#define BEEP_ERROR_TYPE_MASK       0xF000
#define BEEP_ERROR_OPERATION_MASK  0x0FFF
#define BEEP_ERROR_TYPE_GENERAL    0x3000
#define BEEP_ERROR_TYPE_MEMORY     0x4000
#define BEEP_ERROR_TYPE_DF         0x5000
#define BEEP_ERROR_TYPE_CCX        0x6000
#define BEEP_ERROR_TYPE_GNB        0x7000
#define BEEP_ERROR_TYPE_PSP        0x8000
#define BEEP_ERROR_TYPE_SMU        0x9000
#define BEEP_ERROR_TYPE_UNKNOW     0xFFFF
#define BEEP_ERROR_TABLE_SIZE      8

// PEAK_ATTR attribute
typedef union {
  UINT32  Uint32;
  struct {
    UINT32  PeakCnt:5;        ///< number of valid bit, zeor based
    UINT32  PulseWidths:3;    ///< pulse widths of positive peak, multiple of 0.1s
    UINT32  RepeatCnt:4;      ///< waves repeat count
    UINT32  :20;              ///< Reserved
  } Bits;
} PEAK_ATTR;

///===============================================================================
/// MEMORY OVERCLOCK ERROR TYPE
///
typedef enum {
  MEM_OVERCLOCK_ERROR_MEM_INIT        = 0,
  MEM_OVERCLOCK_ERROR_MEM_TEST        = 1,
  MEM_OVERCLOCK_ERROR_MEM_OTHER       = 2,
  MEM_OVERCLOCK_ERROR_PMU_TRAINING    = 3,
  MEM_OVERCLOCK_ERROR_RRW_TEST        = 4,
  MEM_OVERCLOCK_ERROR_MAX             = 5
} MEMORY_OVERCLOCK_ERROR_TYPE;

typedef struct _ERROR_BEEP_CODE_TABLE {
  UINT16    ErrorType;     ///< Error type is specified for the beep codes
  UINT16    PeakMap;       ///< Peak bitmap value to indicated the error
  PEAK_ATTR PeakAttr;      ///< Attribute structure for PeakMap
} ERROR_BEEP_CODE_TABLE;

///===============================================================================
/// PSP_ERROR_OUT_CONTROL_STRUCT
/// This data structure is used to control sending AGESA Event info to the specified port
///
typedef struct _PSP_ERROR_OUT_CONTROL_STRUCT {
  IN
  BOOLEAN ErrorLogPortReportingEnable;         ///< Indicates if ABL will report errors via a port
                                               ///< TRUE - Error logging will be reported via a port
                                               ///< FALSE - Error logging will not be reported via a port
  IN
  BOOLEAN ErrorReportErrorGpioEnable;          ///< Indicates if ABL will report errors via GPIO
                                               ///< TRUE - Error logging will be reported via a GPIO
                                               ///< FALSE - Error logging will not be reported via a GPIO
                                               ///< (only valid if ErrorLogPortReportingEnable = TRUE)
  IN
  BOOLEAN ErrorReportErrorBeepCodeEnable;      ///< This flag indicates if the ABL will report error via beep codes
                                               ///< TRUE - Error logging will be reported via FCH speaker
                                               ///< FALSE - Error logging will not be reported via FCH speaker
                                               ///< (only valid if ErrorLogPortReportingEnable = TRUE)
  IN
  BOOLEAN ErrorLogReportUsingHandshakeEnable;  ///< This flag indicates if the ABL will use an handshake for the Error Log
                                               ///< TRUE - Error log reported using a handshake with the "ErrorLogOutputPort" and "ErrorLogInputPort"
                                               ///< FALSE - Error log reported using "ErrorLogOutputPort" only with each DWORD in log delayed by
                                               ///<         ErrorLogOutputDwordDelay
  IN
  UINT32  ErrorLogInputPort;                   ///< Input Port to receive ABL Error information
                                               ///<  (only valid if ReportErrorLogUsingHandshakeEnable = TRUE)
  IN
  UINT32  ErrorLogOutputDwordDelay;            ///< Number of "10ns" to wait before sending the next Log Dword informaiton via "ErrorLogOutputPort"
                                               ///< (only valid if ReportErrorLogUsingHandshakeEnable = FALSE)
  IN
  UINT32  ErrorLogOutputPort;                  ///< Output Port for ABL Error information
  IN
  BOOLEAN  ErrorStopOnFirstFatalErrorEnable;   ///< Indicates that ABL will stop on the first fatal error
                                               ///< TRUE - Stop and report the first FATAL error
                                               ///< FALSE - Report all errors
  IN
  UINT32  ErrorLogReportInputPortSize;          ///< Indicates the sie of the input and outut port
                                                ///< 1 - 8 bit port
                                                ///< 2 - 16 bit port
                                                ///< 4 - 32 bit port
  IN
  UINT32  ErrorLogReportOutputPortSize;         ///< Indicates the sie of the input and outut port
                                                ///< 1 - 8 bit port
                                                ///< 2 - 16 bit port
                                                ///< 4 - 32 bit port
  IN
  UINT32  ErrorLogReportInputPortType;          ///< Indicates the type of Input Port or location of the port
                                                ///< 0 - PCIE HT0
                                                ///< 2 - PCIE HT1
                                                ///< 5 - PCIE MMIO
                                                ///< 6 - FCH_HT_IO (Default)
                                                ///< 7 - FCH_MMIO
  IN
  UINT32  ErrorLogReportOutputPortType;          ///< Indicates the type of Output Port or location of the port
                                                ///< 0 - PCIE HT0
                                                ///< 2 - PCIE HT1
                                                ///< 5 - PCIE MMIO
                                                ///< 6 - FCH_HT_IO (Default)
                                                ///< 7 - FCH_MMIO

  IN
  BOOLEAN  ErrorLogReportClearAcknowledgement;   ///< Indicates if the ABL will clear acknolgements during protocol
                                                 ///< TRUE - Clear acknowledgemetns
                                                 ///< FALSE - Do not clear acknologements

  ERROR_ABL_GPIO   ErrorLogReportGpioReport;     ///< Structure for the GPIO definition
                                                 ///< (only valid if ErrorReportErrorGpioEnable = TRUE)

  ERROR_BEEP_CODE_TABLE  BeepCodeTable[BEEP_ERROR_TABLE_SIZE];        ///< Structure for definition of beep codes
                                                                      ///< (only valid if ErrorReportErrorBeepCodeEnable = TRUE)
  IN
  BOOLEAN ErrorLogHeartBeatEnable;             ///< Indicates if ABL will provide periodic status to a port as a heart beat
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
  IN
  BOOLEAN ErrorLogPowerGoodGpioEnable;         ///< Indicates if ABL will report power good status via GPIO
                                               ///< TRUE - ABL will report power good status via a GPIO
                                               ///< FALSE - ABL will not report power good status via a GPIO
                                               ///< (only valid if ErrorLogPortReportingEnable = TRUE)

  ERROR_ABL_GPIO   ErrorLogPowerGoodGpio;      ///< Structure for Power Good GPIO definition
                                               ///< (only valid if ErrorLogPowerGoodGpioEnable = TRUE)
} PSP_ERROR_OUT_CONTROL_STRUCT;

///===============================================================================
/// PSP_EXT_VOLTAGE_CONTROL_STRUCT
/// This data structure is used to control sending AGESA volatage info to the specified port
///
typedef struct _PSP_EXT_VOLTAGE_CONTROL_STRUCT {
  IN
  BOOLEAN ExtVoltageControlEnable;             ///< Indicates if ABL will supprot external voltage changes
                                               ///< TRUE - External voltage change are supported
                                               ///< FALSE - No external voltage change are supported (Default)
  IN
  UINT32  ExtVoltageInputPort;                 ///< Input Port to receive voltage information  (Default = 0x84)
  IN
  UINT32  ExtVoltageOutputPort;                ///< Output Port to send voltage (Default = 0x80)
  IN
  UINT32  ExtVoltageInputPortSize;             ///< Indicates the sie of the input and outut port
                                               ///< 1 - 8 bit port
                                               ///< 2 - 16 bit port
                                               ///< 4 - 32 bit port (Default)
  IN
  UINT32  ExtVoltageOutputPortSize;            ///< Indicates the sie of the input and outut port
                                               ///< 1 - 8 bit port
                                               ///< 2 - 16 bit port
                                               ///< 4 - 32 bit port (Default)
  IN
  UINT32  ExtVoltageInputPortType;              ///< Indicates the type of Input Port or location of the port
                                                ///< 0 - PCIE HT0
                                                ///< 2 - PCIE HT1
                                                ///< 5 - PCIE MMIO
                                                ///< 6 - FCH_HT_IO (Default)
                                                ///< 7 - FCH_MMIO
  IN
  UINT32  ExtVoltageOutputPortType;             ///< Indicates the type of Output Port or location of the port
                                                ///< 0 - PCIE HT0
                                                ///< 2 - PCIE HT1
                                                ///< 5 - PCIE MMIO
                                                ///< 6 - FCH_HT_IO (Default)
                                                ///< 7 - FCH_MMIO

  IN
  BOOLEAN  ExtVoltageClearAcknowledgement;     ///< Indicates if the ABL will clear acknolgements during protocol
                                               ///< TRUE - Clear acknowledgemetns (Default)
                                               ///< FALSE - Do not clear acknologements
} PSP_EXT_VOLTAGE_CONTROL_STRUCT;


//APCB HEADER
//#define APCB_HEADER_VERSION_MAJOR   2
//#define APCB_HEADER_VERSION_MINOR   0
//#define APCB_HEADER_VERSION         ((APCB_HEADER_VERSION_MAJOR << 4) | APCB_HEADER_VERSION_MINOR)

//
// APCB Header Definition Version 2
//
typedef struct {
  UINT32  Signature;          // ASCII "APCB", 'A' is LSB
  UINT16  SizeOfHeader;       // Size of header
  UINT16  Version;            // Version, BCD. Version 1.2 is 0x12
  UINT32  SizeOfApcb;         // Size of APCB
  UINT32  UniqueApcbInstance; // UniqueApcbInstance to ensure
                              // compatibitly for giveen flshed BIOS lifecycle
  UINT8   CheckSumByte;        // APCB Checksum Byte
  UINT8   Reserved1[3];        // Reserved
  UINT32  Reserved2[3];        // Reserved
} APCB_HEADER;


#define APCB_INDEX_HEADER_VERSION_MAJOR   0
#define APCB_INDEX_HEADER_VERSION_MINOR   1
#define APCB_INDEX_HEADER_VERSION         ((APCB_INDEX_HEADER_VERSION_MAJOR << 4) | APCB_INDEX_HEADER_VERSION_MINOR)
//
// APCB Index of Data Type Header Definition
//
typedef struct {
  UINT16  SizeOfHeader;     // Size of header
  UINT16  Version;          // Version, BCD. Version 1.2 is 0x12
  UINT16  Reserved;         // Reserved
  UINT32  SizeOfIndexData;  // Size of index data, absolute address in PSP
                            // NOTE: Will we support it to be relative address to starging address of APCB?
} APCB_INDEX_HEADER;

//
// APCB Index of Data Type  Definition
//
typedef struct {
  UINT16  GroupId;          // Group ID
  UINT16  TypeId;           // Type ID
  UINT32  Address;          // Data address
} APCB_TYPE_INDEX;

//
// APCB Data Type Header Definition
//
typedef struct {
  UINT16  GroupId;          // Group ID
  UINT16  TypeId;           // Type ID
  UINT16  SizeOfType;       // Size of type, in bytes
  UINT16  InstanceId;       // Instance ID
  UINT32  Reserved1;
  UINT32  Reserved2;
} APCB_TYPE_HEADER;

#define ALIGN_SIZE_OF_TYPE    4


#define APCB_GROUP_HEADER_VERSION_MAJOR   0
#define APCB_GROUP_HEADER_VERSION_MINOR   1
#define APCB_GROUP_HEADER_VERSION         ((APCB_GROUP_HEADER_VERSION_MAJOR << 4) | APCB_GROUP_HEADER_VERSION_MINOR)

#define INVALID_GROUP_ID    0xFFFF
#define UNKNOWN_GROUP_ID    0xFFFE

#define OVERRIDE_INSTANCE 0x10000
#define INSTANCE_ID_MASK 0xFFFF

//
// APCB Data Group Header Definition
//
typedef struct {
  UINT32  Signature;        // ASCII Signature
  UINT16  GroupId;          // Group ID
  UINT16  SizeOfHeader;     // Size of header
  UINT16  Version;          // Version, BCD. Version 1.2 is 0x12
  UINT16  Reserved;         // Reserved
  UINT32  SizeOfGroup;      // Size of group
} APCB_GROUP_HEADER;

///===============================================================================
// Get board ID retrieve method, then load the APCB instance based on the board ID


#define BOARD_ID_METHOD_SMBUS     1
#define BOARD_ID_METHOD_EEPROM    2
#define BOARD_ID_METHOD_GPIO      3
#define METHOD_USER_CONFIG        0xF

#define ID_FEATURE_MASK           0x80   // This is Bit 7 of

typedef struct {
  IN       UINT8    IdAndFeatureMask;    ///< Mask to the value read from board ID register
                                         ///< Bit 6:0 - Id Mask Bits
                                         ///< Bit7 - detemines between normal or feature controlled Instance
                                         ///< Bit7,   1 = User Controlled Feature Enabled, 0 - Normal Mode
  IN       UINT8    IdAndFeatureValue;   ///< IdValue after mask
  IN       UINT8    ApcbInstance;        ///< The corresponding APCB instance
} ID_APCB_MAPPING;

/// For EEPROM method
typedef struct _PSP_GET_BOARD_ID_FROM_EEPROM_STRUCT {
  IN       UINT16   AccessMethod;   ///< 0: EEPROM, 1: Smbus, 2: FCH GPIO. 0xF: USER_CONFIG
  IN       UINT16   I2cCtrlr;       ///< ZP I2C controller: 0: I2C_0, 1: I2C_1, 2: I2C_2, 3: I2C_3, 4: I2C_4, 5: I2C_5                                   ///
  IN       UINT16   SmbusAddr;      ///< Smbus address of the EEPROM
} PSP_GET_BOARD_ID_FROM_EEPROM_STRUCT;

/// For Smbus device method
typedef struct _PSP_GET_BOARD_ID_FROM_SMBUS_STRUCT {
  IN       UINT16   AccessMethod;       ///< 0: EEPROM, 1: Smbus, 2: FCH GPIO F: None
  IN       UINT8    I2cCtrlr;           ///< ZP I2C controller: 0: I2C_0, 1: I2C_1, 2: I2C_2, 3: I2C_3, 4: I2C_4, 5: I2C_5
  IN       UINT8    I2cMuxAddress;      ///< I2C Mux Address
  IN       UINT8    MuxControlAddress;  ///< Mux Control Address
  IN       UINT8    MuxChannel;         ///< I2C Mux Channel assocaited iwth this SPD
  IN       UINT16   SmbusAddr;          ///< Smbus address of the device to get the board ID
  IN       UINT16   RegIndex;           ///< Register index of the Smbus device to get the board ID
  IN       ID_APCB_MAPPING   IdApcbMapping[];
} PSP_GET_BOARD_ID_FROM_SMBUS_STRUCT;

/// For FCH GPIO method
typedef struct _PSP_GET_BOARD_ID_FROM_GPIO_STRUCT {
  IN       UINT16   AccessMethod;   ///< 0: EEPROM, 1: Smbus, 2: FCH GPIO, 0xF: USER_CONFIG
  IN       UINT8    Gpio0;          ///< FCH GPIO number of the board ID bit 0
  IN       UINT8    Gpio0IoMUX;     ///< Value write to IOMUX to configure this GPIO pin
  IN       UINT8    Gpio0BankCtl;   ///< Value write to GPIOBankCtl[23:16] to configure this GPIO pin
  IN       UINT8    Gpio1;          ///< FCH GPIO number of the board ID bit 1
  IN       UINT8    Gpio1IoMUX;     ///< Value write to IOMUX to configure this GPIO pin
  IN       UINT8    Gpio1BankCtl;   ///< Value write to GPIOBankCtl[23:16] to configure this GPIO pin
  IN       UINT8    Gpio2;          ///< FCH GPIO number of the board ID bit 2, put 0xff if does not exist
  IN       UINT8    Gpio2IoMUX;     ///< Value write to IOMUX to configure this GPIO pin
  IN       UINT8    Gpio2BankCtl;   ///< Value write to GPIOBankCtl[23:16] to configure this GPIO pin
  IN       UINT8    Gpio3;          ///< FCH GPIO number of the board ID bit 3, put 0xff if does not exist
  IN       UINT8    Gpio3IoMUX;     ///< Value write to IOMUX to configure this GPIO pin
  IN       UINT8    Gpio3BankCtl;   ///< Value write to GPIOBankCtl[23:16] to configure this GPIO pin
  IN       ID_APCB_MAPPING   IdApcbMapping[];
} PSP_GET_BOARD_ID_FROM_GPIO_STRUCT;

/// For User Controlled Method to Load Specific APCB Instance
typedef struct _PSP_METHOD_USER_CONTROLLED_FEATURE_STRUCT {
  IN       UINT16   AccessMethod;           ///< 0: EEPROM, 1: Smbus, 2: FCH GPIO,  0xF: USER_CONFIG
  IN       UINT16   FeatureMaskData;        ///< Data Pattern defined by user which can be used to
                                            ///< mask between normal and feature enabled Instance selection
  IN       ID_APCB_MAPPING   IdApcbMapping[];
} PSP_METHOD_USER_CONTROLLED_FEATURE_STRUCT;

//
// XGMI TX EQ definitions
//
#define XGMI_BIT_POS(Position)                  (1 << Position)

// NOTE: Bit28~31 are used as NodeType in common.
#define XGMI_TX_EQ_COMMON_NODE_TYPE_SHIFT       28
#define XGMI_TX_EQ_COMMON_NODE_TYPE_SIZE_MASK   0x0F
#define XGMI_TX_EQ_COMMON_NODE_TYPE_MASK        (XGMI_TX_EQ_COMMON_NODE_TYPE_SIZE_MASK << XGMI_TX_EQ_COMMON_NODE_TYPE_SHIFT)
// Shared node type definitions
#define   XGMI_TX_EQ_NODE_TYPE_RSVD             0x0
#define   XGMI_TX_EQ_NODE_TYPE_DATA             0x1
#define   XGMI_TX_EQ_NODE_TYPE_LOC              0x2
#define   XGMI_TX_EQ_NODE_TYPE_FREQ             0x3
#define   XGMI_TX_EQ_NODE_TYPE_FREQ_TBL         0x4
#define   XGMI_TX_EQ_NODE_TYPE_FREQ_END         0x5
#define   XGMI_TX_EQ_NODE_TYPE_END              0xF

// XGMI_TX_EQ MAKE_TX_EQ_FREQ_TABLE attribute
typedef struct _XGMI_TX_EQ_COMMON {
  UINT32  :24;                                   ///< Reserved
  UINT32  :4;                                    ///< Reserved
  UINT32  NodeType:4;                            ///< Node type
} XGMI_TX_EQ_COMMON;

#define XGMI_TX_EQ_FREQ_SPEED_MASK_SHIFT        0
#define XGMI_TX_EQ_FREQ_SPEED_MASK_SIZE_MASK    0xFF
#define XGMI_TX_EQ_FREQ_SPEED_MASK_MASK         (XGMI_TX_EQ_FREQ_SPEED_MASK_SIZE_MASK << XGMI_TX_EQ_FREQ_SPEED_MASK_SHIFT)
#define   XGMI_TX_EQ_SPEED_53                   XGMI_BIT_POS(0)   // Instance ID of 5.3G
#define   XGMI_TX_EQ_SPEED_64                   XGMI_BIT_POS(1)   // Instance ID of 6.4G
#define   XGMI_TX_EQ_SPEED_75                   XGMI_BIT_POS(2)   // Instance ID of 7.5G
#define   XGMI_TX_EQ_SPEED_85                   XGMI_BIT_POS(3)   // Instance ID of 8.5G
#define   XGMI_TX_EQ_SPEED_96                   XGMI_BIT_POS(4)   // Instance ID of 9.6G
#define   XGMI_TX_EQ_SPEED_107                  XGMI_BIT_POS(5)   // Instance ID of 10.7G
#define   XGMI_TX_EQ_SPEED_117                  XGMI_BIT_POS(6)   // Instance ID of 11.7G
#define   XGMI_TX_EQ_SPEED_128                  XGMI_BIT_POS(7)   // Instance ID of 12.8G
#define   XGMI_TX_EQ_SPEED_ALL                  (XGMI_TX_EQ_SPEED_53 | XGMI_TX_EQ_SPEED_64 | XGMI_TX_EQ_SPEED_75 | XGMI_TX_EQ_SPEED_85 | XGMI_TX_EQ_SPEED_96 | XGMI_TX_EQ_SPEED_107 | XGMI_TX_EQ_SPEED_117 | XGMI_TX_EQ_SPEED_128)

// XGMI_TX_EQ MAKE_TX_EQ_FREQ_TABLE attribute
typedef struct _XGMI_TX_EQ_FREQ {
  UINT32  SpeedMask:8;                          ///< Speed mask
  UINT32  :16;                                  ///< Reserved
  UINT32  :4;                                   ///< Reserved
  UINT32  NodeType:4;                           ///< Node type: MAKE_TX_EQ_FREQ_TABLE
} XGMI_TX_EQ_FREQ;

#define MAKE_TX_EQ_FREQ(SpeedMask)               ((UINT32) (((XGMI_TX_EQ_NODE_TYPE_FREQ & XGMI_TX_EQ_COMMON_NODE_TYPE_SIZE_MASK) << XGMI_TX_EQ_COMMON_NODE_TYPE_SHIFT) | \
                                                                   ((SpeedMask & XGMI_TX_EQ_FREQ_SPEED_MASK_SIZE_MASK) << XGMI_TX_EQ_FREQ_SPEED_MASK_SHIFT)))
#define MAKE_TX_EQ_FREQ_TBL(SpeedMask)           ((UINT32) (((XGMI_TX_EQ_NODE_TYPE_FREQ_TBL & XGMI_TX_EQ_COMMON_NODE_TYPE_SIZE_MASK) << XGMI_TX_EQ_COMMON_NODE_TYPE_SHIFT) | \
                                                                   ((SpeedMask & XGMI_TX_EQ_FREQ_SPEED_MASK_SIZE_MASK) << XGMI_TX_EQ_FREQ_SPEED_MASK_SHIFT)))


#define XGMI_TX_EQ_ATTR_LANE_MASK_SHIFT         0
#define XGMI_TX_EQ_ATTR_LANE_MASK_SIZE_MASK     0xFFFF
#define XGMI_TX_EQ_ATTR_LANE_MASK_MASK          (XGMI_TX_EQ_ATTR_LANE_MASK_SIZE_MASK << XGMI_TX_EQ_ATTR_LANE_MASK_SHIFT)
#define XGMI_TX_EQ_ATTR_DIE_MASK_SHIFT          16
#define XGMI_TX_EQ_ATTR_DIE_MASK_SIZE_MASK      0xFF
#define XGMI_TX_EQ_ATTR_DIE_MASK_MASK           (XGMI_TX_EQ_ATTR_DIE_MASK_SIZE_MASK << XGMI_TX_EQ_ATTR_DIE_MASK_SHIFT)
#define XGMI_TX_EQ_ATTR_SOCKET_MASK_SHIFT       24
#define XGMI_TX_EQ_ATTR_SOCKET_MASK_SIZE_MASK   0x03
#define XGMI_TX_EQ_ATTR_SOCKET_MASK_MASK        (XGMI_TX_EQ_ATTR_SOCKET_MASK_SIZE_MASK << XGMI_TX_EQ_ATTR_SOCKET_MASK_SHIFT)
#define XGMI_TX_EQ_ATTR_DATA_MODE_SHIFT         26
#define XGMI_TX_EQ_ATTR_DATA_MODE_SIZE_MASK     0x03
#define XGMI_TX_EQ_ATTR_DATA_MODE_MASK          (XGMI_TX_EQ_ATTR_DATA_MODE_SIZE_MASK << XGMI_TX_EQ_ATTR_DATA_MODE_SHIFT)
// Data mode definitions
#define   XGMI_TX_EQ_DATA_MODE_PAIR             0        ///< Pair mode, same value for all matched lanes.
#define   XGMI_TX_EQ_DATA_MODE_LIST             1        ///< List mode, list each value for each matched lanes from low to high socket/die/lane.
#define   XGMI_TX_EQ_DATA_MODE_LIST_COMPACT     2        ///< List compact mode, list each value for each matched lanes from low to high socket/die/lane in compact format
#define   XGMI_TX_EQ_DATA_MODE_MAX              3        ///< Maximum data mode
// NOTE: Bit28~31 are used as NodeType in common.

#define XGMI_ALL_SOCKETS                        0x03     ///< 2 sockets per system
#define XGMI_MAX_SOCKET_COUNT                   2
#define XGMI_ALL_DIES                           0x0F     ///< 4 dies per socket
#define XGMI_MAX_DIE_COUNT_PER_SOCKET           4
#define XGMI_ALL_LANES                          0xFFFF   ///< 16 lanes per die
#define XGMI_MAX_LANE_COUNT_PER_DIE             16
#define XGMI_SOCKET0                            XGMI_BIT_POS(0)
#define XGMI_SOCKET1                            XGMI_BIT_POS(1)
#define XGMI_DIE0                               XGMI_BIT_POS(0)
#define XGMI_DIE1                               XGMI_BIT_POS(1)
#define XGMI_DIE2                               XGMI_BIT_POS(2)
#define XGMI_DIE3                               XGMI_BIT_POS(3)
#define XGMI_DIE4                               XGMI_BIT_POS(4)
#define XGMI_DIE5                               XGMI_BIT_POS(5)
#define XGMI_DIE6                               XGMI_BIT_POS(6)
#define XGMI_DIE7                               XGMI_BIT_POS(7)
#define XGMI_LANE0                              XGMI_BIT_POS(0)
#define XGMI_LANE1                              XGMI_BIT_POS(1)
#define XGMI_LANE2                              XGMI_BIT_POS(2)
#define XGMI_LANE3                              XGMI_BIT_POS(3)
#define XGMI_LANE4                              XGMI_BIT_POS(4)
#define XGMI_LANE5                              XGMI_BIT_POS(5)
#define XGMI_LANE6                              XGMI_BIT_POS(6)
#define XGMI_LANE7                              XGMI_BIT_POS(7)
#define XGMI_LANE8                              XGMI_BIT_POS(8)
#define XGMI_LANE9                              XGMI_BIT_POS(9)
#define XGMI_LANE10                             XGMI_BIT_POS(10)
#define XGMI_LANE11                             XGMI_BIT_POS(11)
#define XGMI_LANE12                             XGMI_BIT_POS(12)
#define XGMI_LANE13                             XGMI_BIT_POS(13)
#define XGMI_LANE14                             XGMI_BIT_POS(14)
#define XGMI_LANE15                             XGMI_BIT_POS(15)

// XGMI_TX_EQ apply attribute
typedef struct _XGMI_TX_EQ_ATTR {
  UINT32  LaneMask:16;                           ///< Lane mask per die       (2^4)
  UINT32  DieMask:8;                             ///< Die mask per socket     (2^3)
  UINT32  SocketMask:2;                          ///< Socket mask per system  (2^1)
  UINT32  DataMode:2;                            ///< Data mode. Pair or List
  UINT32  NodeType:4;                            ///< Node type: Location
} XGMI_TX_EQ_ATTR;

#define MAKE_TX_EQ_ATTR(SocketMask, DieMask, LaneMask, DataMode)  ((UINT32) (((XGMI_TX_EQ_NODE_TYPE_LOC & XGMI_TX_EQ_COMMON_NODE_TYPE_SIZE_MASK) << XGMI_TX_EQ_COMMON_NODE_TYPE_SHIFT) | \
                                                                   ((DataMode & XGMI_TX_EQ_ATTR_DATA_MODE_SIZE_MASK) << XGMI_TX_EQ_ATTR_DATA_MODE_SHIFT) | \
                                                                   ((SocketMask & XGMI_TX_EQ_ATTR_SOCKET_MASK_SIZE_MASK) << XGMI_TX_EQ_ATTR_SOCKET_MASK_SHIFT) | \
                                                                   ((DieMask & XGMI_TX_EQ_ATTR_DIE_MASK_SIZE_MASK) << XGMI_TX_EQ_ATTR_DIE_MASK_SHIFT) | \
                                                                   ((LaneMask & XGMI_TX_EQ_ATTR_LANE_MASK_SIZE_MASK) << XGMI_TX_EQ_ATTR_LANE_MASK_SHIFT)))

#define XGMI_TX_EQ_DATA_EQ_PRE_SHIFT            0
#define XGMI_TX_EQ_DATA_EQ_PRE_SIZE_MASK        0x3F
#define XGMI_TX_EQ_DATA_EQ_PRE_MASK             (XGMI_TX_EQ_DATA_EQ_PRE_SIZE_MASK << XGMI_TX_EQ_DATA_EQ_PRE_SHIFT)
#define XGMI_TX_EQ_DATA_EQ_MAIN_SHIFT           8
#define XGMI_TX_EQ_DATA_EQ_MAIN_SIZE_MASK       0x3F
#define XGMI_TX_EQ_DATA_EQ_MAIN_MASK            (XGMI_TX_EQ_DATA_EQ_MAIN_SIZE_MASK << XGMI_TX_EQ_DATA_EQ_MAIN_SHIFT)
#define XGMI_TX_EQ_DATA_EQ_POST_SHIFT           16
#define XGMI_TX_EQ_DATA_EQ_POST_SIZE_MASK       0x3F
#define XGMI_TX_EQ_DATA_EQ_POST_MASK            (XGMI_TX_EQ_DATA_EQ_POST_SIZE_MASK << XGMI_TX_EQ_DATA_EQ_POST_SHIFT)
// NOTE: Bit28~31 are used as NodeType in common.

// XGMI TX EQ settings
typedef struct _XGMI_TX_EQ_DATA {
  UINT32  EqPre:6;                              ///< EQ_PRE/TxCoeffPre
  UINT32  :2;                                   ///< Reserved
  UINT32  EqMain:6;                             ///< EQ_MAIN/TxCoeffCurs
  UINT32  :2;                                   ///< Reserved
  UINT32  EqPost:6;                             ///< EQ_POST/TxCoeffPost
  UINT32  :2;                                   ///< Reserved
  UINT32  :4;                                   ///< Reserved
  UINT32  NodeType:4;                           ///< Node type: Data
} XGMI_TX_EQ_DATA;

#define MAKE_TX_EQ_DATA(EqMain, EqPost, EqPre)          ((UINT32) (((XGMI_TX_EQ_NODE_TYPE_DATA & XGMI_TX_EQ_COMMON_NODE_TYPE_SIZE_MASK) << XGMI_TX_EQ_COMMON_NODE_TYPE_SHIFT) | \
                                                                   ((EqPost & XGMI_TX_EQ_DATA_EQ_POST_SIZE_MASK) << XGMI_TX_EQ_DATA_EQ_POST_SHIFT) | \
                                                                   ((EqMain & XGMI_TX_EQ_DATA_EQ_MAIN_SIZE_MASK) << XGMI_TX_EQ_DATA_EQ_MAIN_SHIFT) | \
                                                                   ((EqPre & XGMI_TX_EQ_DATA_EQ_PRE_SIZE_MASK) << XGMI_TX_EQ_DATA_EQ_PRE_SHIFT)))

#define XGMI_TX_EQ_DATA_COMPACT_EQ_PRE_SHIFT            0
#define XGMI_TX_EQ_DATA_COMPACT_EQ_PRE_SIZE_MASK        XGMI_TX_EQ_DATA_EQ_PRE_SIZE_MASK
#define XGMI_TX_EQ_DATA_COMPACT_EQ_PRE_MASK             (XGMI_TX_EQ_DATA_COMPACT_EQ_PRE_SIZE_MASK << XGMI_TX_EQ_DATA_COMPACT_EQ_PRE_SHIFT)
#define XGMI_TX_EQ_DATA_COMPACT_EQ_MAIN_SHIFT           6
#define XGMI_TX_EQ_DATA_COMPACT_EQ_MAIN_SIZE_MASK       XGMI_TX_EQ_DATA_EQ_MAIN_SIZE_MASK
#define XGMI_TX_EQ_DATA_COMPACT_EQ_MAIN_MASK            (XGMI_TX_EQ_DATA_COMPACT_EQ_MAIN_SIZE_MASK << XGMI_TX_EQ_DATA_COMPACT_EQ_MAIN_SHIFT)
#define XGMI_TX_EQ_DATA_COMPACT_EQ_POST_SHIFT           12
#define XGMI_TX_EQ_DATA_COMPACT_EQ_POST_SIZE_MASK       XGMI_TX_EQ_DATA_EQ_POST_SIZE_MASK
#define XGMI_TX_EQ_DATA_COMPACT_EQ_POST_MASK            (XGMI_TX_EQ_DATA_COMPACT_EQ_POST_SIZE_MASK << XGMI_TX_EQ_DATA_COMPACT_EQ_POST_SHIFT)

typedef struct _XGMI_TX_EQ_DATA_LIST_COMPACT {
  UINT32  EqPre0:6;                           ///< EQ_PRE/TxCoeffPre for 0
  UINT32  EqMain0:6;                          ///< EQ_MAIN/TxCoeffCurs for 0
  UINT32  EqPost0:6;                          ///< EQ_POST/TxCoeffPost for 0
  UINT32  EqPre1:6;                           ///< EQ_PRE/TxCoeffPre for 1
  UINT32  EqMain1:6;                          ///< EQ_MAIN/TxCoeffCurs for 1
  UINT32  EqPost1_1_0:2;                      ///< EQ_POST/TxCoeffPost for 1

  UINT32  EqPost1_5_2:4;                       ///< EQ_POST/TxCoeffPost for 1
  UINT32  EqPre2:6;                           ///< EQ_PRE/TxCoeffPre for 2
  UINT32  EqMain2:6;                          ///< EQ_MAIN/TxCoeffCurs for 2
  UINT32  EqPost2:6;                          ///< EQ_POST/TxCoeffPost for 2
  UINT32  EqPre3:6;                           ///< EQ_PRE/TxCoeffPre for 3
  UINT32  EqMain3_3_0:4;                      ///< EQ_MAIN/TxCoeffCurs for 3

  UINT32  EqMain3_5_4:2;                      ///< EQ_MAIN/TxCoeffCurs for 3
  UINT32  EqPost3:6;                          ///< EQ_POST/TxCoeffPost for 3
  UINT32  EqPre4:6;                           ///< EQ_PRE/TxCoeffPre for 4
  UINT32  EqMain4:6;                          ///< EQ_MAIN/TxCoeffCurs for 4
  UINT32  EqPost4:6;                          ///< EQ_POST/TxCoeffPost for 4
  UINT32  EqPre5:6;                           ///< EQ_PRE/TxCoeffPre for 5

  UINT32  EqMain5:6;                          ///< EQ_MAIN/TxCoeffCurs for 5
  UINT32  EqPost5:6;                          ///< EQ_POST/TxCoeffPost for 5
  UINT32  EqPre6:6;                           ///< EQ_PRE/TxCoeffPre for 6
  UINT32  EqMain6:6;                          ///< EQ_MAIN/TxCoeffCurs for 6
  UINT32  EqPost6:6;                          ///< EQ_POST/TxCoeffPost for 6
  UINT32  EqPre7_1_0:2;                       ///< EQ_PRE/TxCoeffPre for 7

  UINT32  EqPre7_5_2:4;                       ///< EQ_PRE/TxCoeffPre for 7
  UINT32  EqMain7:6;                          ///< EQ_MAIN/TxCoeffCurs for 7
  UINT32  EqPost7:6;                          ///< EQ_POST/TxCoeffPost for 7
  UINT32  EqPre8:6;                           ///< EQ_PRE/TxCoeffPre for 8
  UINT32  EqMain8:6;                          ///< EQ_MAIN/TxCoeffCurs for 8
  UINT32  EqPost8_3_0:4;                      ///< EQ_POST/TxCoeffPost for 8

  UINT32  EqPost8_5_4:2;                      ///< EQ_POST/TxCoeffPost for 8
  UINT32  EqPre9:6;                           ///< EQ_PRE/TxCoeffPre for 9
  UINT32  EqMain9:6;                          ///< EQ_MAIN/TxCoeffCurs for 9
  UINT32  EqPost9:6;                          ///< EQ_POST/TxCoeffPost for 9
  UINT32  EqPre10:6;                          ///< EQ_PRE/TxCoeffPre for 10
  UINT32  EqMain10:6;                         ///< EQ_MAIN/TxCoeffCurs for 10

  UINT32  EqPost10:6;                         ///< EQ_POST/TxCoeffPost for 10
  UINT32  EqPre11:6;                          ///< EQ_PRE/TxCoeffPre for 11
  UINT32  EqMain11:6;                         ///< EQ_MAIN/TxCoeffCurs for 11
  UINT32  EqPost11:6;                         ///< EQ_POST/TxCoeffPost for 11
  UINT32  EqPre12:6;                          ///< EQ_PRE/TxCoeffPre for 12
  UINT32  EqMain12_1_0:2;                     ///< EQ_MAIN/TxCoeffCurs for 12

  UINT32  EqMain12_5_2:4;                     ///< EQ_MAIN/TxCoeffCurs for 12
  UINT32  EqPost12:6;                         ///< EQ_POST/TxCoeffPost for 12
  UINT32  EqPre13:6;                          ///< EQ_PRE/TxCoeffPre for 13
  UINT32  EqMain13:6;                         ///< EQ_MAIN/TxCoeffCurs for 13
  UINT32  EqPost13:6;                         ///< EQ_POST/TxCoeffPost for 13
  UINT32  EqPre14_3_0:4;                      ///< EQ_PRE/TxCoeffPre for 14

  UINT32  EqPre14_5_4:2;                      ///< EQ_PRE/TxCoeffPre for 14
  UINT32  EqMain14:6;                         ///< EQ_MAIN/TxCoeffCurs for 14
  UINT32  EqPost14:6;                         ///< EQ_POST/TxCoeffPost for 14
  UINT32  EqPre15:6;                          ///< EQ_PRE/TxCoeffPre for 15
  UINT32  EqMain15:6;                         ///< EQ_MAIN/TxCoeffCurs for 15
  UINT32  EqPost15:6;                         ///< EQ_POST/TxCoeffPost for 15

} XGMI_TX_EQ_DATA_LIST_COMPACT;

#define MAKE_TX_EQ_LIST_COMPACT_DATA_SUB(EqMain, EqPost, EqPre)     ((UINT32) ( \
                                                                                ((EqPost & XGMI_TX_EQ_DATA_COMPACT_EQ_POST_SIZE_MASK) << XGMI_TX_EQ_DATA_COMPACT_EQ_POST_SHIFT) | \
                                                                                ((EqMain & XGMI_TX_EQ_DATA_COMPACT_EQ_MAIN_SIZE_MASK) << XGMI_TX_EQ_DATA_COMPACT_EQ_MAIN_SHIFT) | \
                                                                                ((EqPre & XGMI_TX_EQ_DATA_COMPACT_EQ_PRE_SIZE_MASK) << XGMI_TX_EQ_DATA_COMPACT_EQ_PRE_SHIFT)))
#define MAKE_TX_EQ_LIST_COMPACT_DATA_SUB_POS_DW0_1ST(EqDw0)         ((UINT32) EqDw0 & 0x3FFFF)
#define MAKE_TX_EQ_LIST_COMPACT_DATA_SUB_POS_DW0_2ND(EqDw1)         (((UINT32) EqDw1 & 0x03FFF) << 18)

#define MAKE_TX_EQ_LIST_COMPACT_DATA_SUB_POS_DW1_1ST(EqDw1)         (((UINT32) EqDw1 & 0x3C000) >> 14)
#define MAKE_TX_EQ_LIST_COMPACT_DATA_SUB_POS_DW1_2ND(EqDw2)         (((UINT32) EqDw2 & 0x3FFFF) << 4)
#define MAKE_TX_EQ_LIST_COMPACT_DATA_SUB_POS_DW1_3RD(EqDw3)         (((UINT32) EqDw3 & 0x003FF) << 22)

#define MAKE_TX_EQ_LIST_COMPACT_DATA_SUB_POS_DW2_1ST(EqDw3)         (((UINT32) EqDw3 & 0x3FC00) >> 10)
#define MAKE_TX_EQ_LIST_COMPACT_DATA_SUB_POS_DW2_2ND(EqDw4)         (((UINT32) EqDw4 & 0x03FFF) << 8)
#define MAKE_TX_EQ_LIST_COMPACT_DATA_SUB_POS_DW2_3RD(EqDw5)         (((UINT32) EqDw5 & 0x0003F) << 26)

#define MAKE_TX_EQ_LIST_COMPACT_DATA_SUB_POS_DW3_1ST(EqDw5)         (((UINT32) EqDw5 & 0x3FFC0) >> 6)
#define MAKE_TX_EQ_LIST_COMPACT_DATA_SUB_POS_DW3_2ND(EqDw6)         (((UINT32) EqDw6 & 0x3FFFF) << 12)
#define MAKE_TX_EQ_LIST_COMPACT_DATA_SUB_POS_DW3_3RD(EqDw7)         (((UINT32) EqDw7 & 0x00003) << 30)

#define MAKE_TX_EQ_LIST_COMPACT_DATA_SUB_POS_DW4_1ST(EqDw7)         (((UINT32) EqDw7 & 0x0FFFF) >> 2)
#define MAKE_TX_EQ_LIST_COMPACT_DATA_SUB_POS_DW4_2ND(EqDw8)         (((UINT32) EqDw8 & 0x0FFFF) << 16)

#define MAKE_TX_EQ_LIST_COMPACT_DATA_SUB_POS_DW5_1ST(EqDw8)         (((UINT32) EqDw8 & 0x30000) >> 16)
#define MAKE_TX_EQ_LIST_COMPACT_DATA_SUB_POS_DW5_2ND(EqDw9)         (((UINT32) EqDw9 & 0x3FFFF) << 2)
#define MAKE_TX_EQ_LIST_COMPACT_DATA_SUB_POS_DW5_3RD(EqDw10)        (((UINT32) EqDw10 & 0x00FFF) << 20)

#define MAKE_TX_EQ_LIST_COMPACT_DATA_SUB_POS_DW6_1ST(EqDw10)        (((UINT32) EqDw10 & 0x3F000) >> 12)
#define MAKE_TX_EQ_LIST_COMPACT_DATA_SUB_POS_DW6_2ND(EqDw11)        (((UINT32) EqDw11 & 0x3FFFF) << 6)
#define MAKE_TX_EQ_LIST_COMPACT_DATA_SUB_POS_DW6_3RD(EqDw12)        (((UINT32) EqDw12 & 0x000FF) << 24)

#define MAKE_TX_EQ_LIST_COMPACT_DATA_SUB_POS_DW7_1ST(EqDw12)        (((UINT32) EqDw12 & 0x3FF00) >> 8)
#define MAKE_TX_EQ_LIST_COMPACT_DATA_SUB_POS_DW7_2ND(EqDw13)        (((UINT32) EqDw13 & 0x3FFFF) << 10)
#define MAKE_TX_EQ_LIST_COMPACT_DATA_SUB_POS_DW7_3RD(EqDw14)        (((UINT32) EqDw14 & 0x0000F) << 28)

#define MAKE_TX_EQ_LIST_COMPACT_DATA_SUB_POS_DW8_1ST(EqDw14)        (((UINT32) EqDw14 & 0x3FFF0) >> 4)
#define MAKE_TX_EQ_LIST_COMPACT_DATA_SUB_POS_DW8_2ND(EqDw15)        (((UINT32) EqDw15 & 0x3FFFF) << 14)

#define MAKE_TX_EQ_LIST_COMPACT_DATA_DW0(EqDw0, EqDw1)              (MAKE_TX_EQ_LIST_COMPACT_DATA_SUB_POS_DW0_1ST(EqDw0) | MAKE_TX_EQ_LIST_COMPACT_DATA_SUB_POS_DW0_2ND(EqDw1))
#define MAKE_TX_EQ_LIST_COMPACT_DATA_DW1(EqDw1, EqDw2, EqDw3)       (MAKE_TX_EQ_LIST_COMPACT_DATA_SUB_POS_DW1_1ST(EqDw1) | MAKE_TX_EQ_LIST_COMPACT_DATA_SUB_POS_DW1_2ND(EqDw2) | MAKE_TX_EQ_LIST_COMPACT_DATA_SUB_POS_DW1_3RD(EqDw3))
#define MAKE_TX_EQ_LIST_COMPACT_DATA_DW2(EqDw3, EqDw4, EqDw5)       (MAKE_TX_EQ_LIST_COMPACT_DATA_SUB_POS_DW2_1ST(EqDw3) | MAKE_TX_EQ_LIST_COMPACT_DATA_SUB_POS_DW2_2ND(EqDw4) | MAKE_TX_EQ_LIST_COMPACT_DATA_SUB_POS_DW2_3RD(EqDw5))
#define MAKE_TX_EQ_LIST_COMPACT_DATA_DW3(EqDw5, EqDw6, EqDw7)       (MAKE_TX_EQ_LIST_COMPACT_DATA_SUB_POS_DW3_1ST(EqDw5) | MAKE_TX_EQ_LIST_COMPACT_DATA_SUB_POS_DW3_2ND(EqDw6) | MAKE_TX_EQ_LIST_COMPACT_DATA_SUB_POS_DW3_3RD(EqDw7))
#define MAKE_TX_EQ_LIST_COMPACT_DATA_DW4(EqDw7, EqDw8)              (MAKE_TX_EQ_LIST_COMPACT_DATA_SUB_POS_DW4_1ST(EqDw7) | MAKE_TX_EQ_LIST_COMPACT_DATA_SUB_POS_DW4_2ND(EqDw8))
#define MAKE_TX_EQ_LIST_COMPACT_DATA_DW5(EqDw8, EqDw9, EqDw10)      (MAKE_TX_EQ_LIST_COMPACT_DATA_SUB_POS_DW5_1ST(EqDw8) | MAKE_TX_EQ_LIST_COMPACT_DATA_SUB_POS_DW5_2ND(EqDw9) | MAKE_TX_EQ_LIST_COMPACT_DATA_SUB_POS_DW5_3RD(EqDw10))
#define MAKE_TX_EQ_LIST_COMPACT_DATA_DW6(EqDw10, EqDw11, EqDw12)    (MAKE_TX_EQ_LIST_COMPACT_DATA_SUB_POS_DW6_1ST(EqDw10) | MAKE_TX_EQ_LIST_COMPACT_DATA_SUB_POS_DW6_2ND(EqDw11) | MAKE_TX_EQ_LIST_COMPACT_DATA_SUB_POS_DW6_3RD(EqDw12))
#define MAKE_TX_EQ_LIST_COMPACT_DATA_DW7(EqDw12, EqDw13, EqDw14)    (MAKE_TX_EQ_LIST_COMPACT_DATA_SUB_POS_DW7_1ST(EqDw12) | MAKE_TX_EQ_LIST_COMPACT_DATA_SUB_POS_DW7_2ND(EqDw13) | MAKE_TX_EQ_LIST_COMPACT_DATA_SUB_POS_DW7_3RD(EqDw14))
#define MAKE_TX_EQ_LIST_COMPACT_DATA_DW8(EqDw14, EqDw15)            (MAKE_TX_EQ_LIST_COMPACT_DATA_SUB_POS_DW8_1ST(EqDw14) | MAKE_TX_EQ_LIST_COMPACT_DATA_SUB_POS_DW8_2ND(EqDw15))

#define MAKE_TX_EQ_LIST_COMPACT_DATA(EqDw0, EqDw1, EqDw2, EqDw3, EqDw4, EqDw5, EqDw6, EqDw7, EqDw8, EqDw9, EqDw10, EqDw11, EqDw12, EqDw13, EqDw14, EqDw15) \
                                                                    MAKE_TX_EQ_LIST_COMPACT_DATA_DW0(EqDw0, EqDw1),           \
                                                                    MAKE_TX_EQ_LIST_COMPACT_DATA_DW1(EqDw1, EqDw2, EqDw3),    \
                                                                    MAKE_TX_EQ_LIST_COMPACT_DATA_DW2(EqDw3, EqDw4, EqDw5),    \
                                                                    MAKE_TX_EQ_LIST_COMPACT_DATA_DW3(EqDw5, EqDw6, EqDw7),    \
                                                                    MAKE_TX_EQ_LIST_COMPACT_DATA_DW4(EqDw7, EqDw8),           \
                                                                    MAKE_TX_EQ_LIST_COMPACT_DATA_DW5(EqDw8, EqDw9, EqDw10),   \
                                                                    MAKE_TX_EQ_LIST_COMPACT_DATA_DW6(EqDw10, EqDw11, EqDw12), \
                                                                    MAKE_TX_EQ_LIST_COMPACT_DATA_DW7(EqDw12, EqDw13, EqDw14), \
                                                                    MAKE_TX_EQ_LIST_COMPACT_DATA_DW8(EqDw14, EqDw15)


// Termination node of XGMI TX EQ setting of frequency table
#define MAKE_TX_EQ_FREQ_END()                           ((UINT32) (((XGMI_TX_EQ_NODE_TYPE_FREQ_END & XGMI_TX_EQ_COMMON_NODE_TYPE_SIZE_MASK) << XGMI_TX_EQ_COMMON_NODE_TYPE_SHIFT)))

// Termination node of XGMI TX EQ setting table
#define MAKE_TX_EQ_END()                                ((UINT32) (((XGMI_TX_EQ_NODE_TYPE_END & XGMI_TX_EQ_COMMON_NODE_TYPE_SIZE_MASK) << XGMI_TX_EQ_COMMON_NODE_TYPE_SHIFT)))


// XGMI TX EQ union
typedef union _XGMI_TX_EQ_UNION {
  UINT32                  Raw;                  ///< Raw data
  XGMI_TX_EQ_COMMON       Common;               ///< Common structure
  XGMI_TX_EQ_FREQ         Freq;                 ///< Frequency structure
  XGMI_TX_EQ_ATTR         Attr;                 ///< Attribute structure
  XGMI_TX_EQ_DATA         Data;                 ///< Data structure
} XGMI_TX_EQ_UNION;

// Macro for all system lanes
#define MAKE_TX_EQ_ALL_SYS_LANES()                      MAKE_TX_EQ_ATTR(XGMI_ALL_SOCKETS, XGMI_ALL_DIES, XGMI_ALL_LANES, XGMI_TX_EQ_DATA_MODE_PAIR)
#define MAKE_TX_EQ_EACH_SYS_LANES()                     MAKE_TX_EQ_ATTR(XGMI_ALL_SOCKETS, XGMI_ALL_DIES, XGMI_ALL_LANES, XGMI_TX_EQ_DATA_MODE_LIST)
// Macros for socket 0
#define MAKE_TX_EQ_SOCKET0_DIE_LANE(DieMask, LaneMask, DataMode)    MAKE_TX_EQ_ATTR(XGMI_SOCKET0, DieMask, LaneMask, DataMode)
#define MAKE_TX_EQ_SOCKET0_DIE_LANE_PAIR(DieMask, LaneMask)         MAKE_TX_EQ_ATTR(XGMI_SOCKET0, DieMask, LaneMask, XGMI_TX_EQ_DATA_MODE_PAIR)
#define MAKE_TX_EQ_SOCKET0_DIE_LANE_LIST(DieMask, LaneMask)         MAKE_TX_EQ_ATTR(XGMI_SOCKET0, DieMask, LaneMask, XGMI_TX_EQ_DATA_MODE_LIST)
#define MAKE_TX_EQ_SOCKET0_DIE0_ALL_LANES()             MAKE_TX_EQ_ATTR(XGMI_SOCKET0, XGMI_DIE0, XGMI_ALL_LANES, XGMI_TX_EQ_DATA_MODE_PAIR)
#define MAKE_TX_EQ_SOCKET0_DIE1_ALL_LANES()             MAKE_TX_EQ_ATTR(XGMI_SOCKET0, XGMI_DIE1, XGMI_ALL_LANES, XGMI_TX_EQ_DATA_MODE_PAIR)
#define MAKE_TX_EQ_SOCKET0_DIE2_ALL_LANES()             MAKE_TX_EQ_ATTR(XGMI_SOCKET0, XGMI_DIE2, XGMI_ALL_LANES, XGMI_TX_EQ_DATA_MODE_PAIR)
#define MAKE_TX_EQ_SOCKET0_DIE3_ALL_LANES()             MAKE_TX_EQ_ATTR(XGMI_SOCKET0, XGMI_DIE3, XGMI_ALL_LANES, XGMI_TX_EQ_DATA_MODE_PAIR)
#define MAKE_TX_EQ_SOCKET0_DIE4_ALL_LANES()             MAKE_TX_EQ_ATTR(XGMI_SOCKET0, XGMI_DIE4, XGMI_ALL_LANES, XGMI_TX_EQ_DATA_MODE_PAIR)
#define MAKE_TX_EQ_SOCKET0_DIE5_ALL_LANES()             MAKE_TX_EQ_ATTR(XGMI_SOCKET0, XGMI_DIE5, XGMI_ALL_LANES, XGMI_TX_EQ_DATA_MODE_PAIR)
#define MAKE_TX_EQ_SOCKET0_DIE6_ALL_LANES()             MAKE_TX_EQ_ATTR(XGMI_SOCKET0, XGMI_DIE6, XGMI_ALL_LANES, XGMI_TX_EQ_DATA_MODE_PAIR)
#define MAKE_TX_EQ_SOCKET0_DIE7_ALL_LANES()             MAKE_TX_EQ_ATTR(XGMI_SOCKET0, XGMI_DIE7, XGMI_ALL_LANES, XGMI_TX_EQ_DATA_MODE_PAIR)
#define MAKE_TX_EQ_SOCKET0_DIE0_EACH_LANES()             MAKE_TX_EQ_ATTR(XGMI_SOCKET0, XGMI_DIE0, XGMI_ALL_LANES, XGMI_TX_EQ_DATA_MODE_LIST)
#define MAKE_TX_EQ_SOCKET0_DIE1_EACH_LANES()             MAKE_TX_EQ_ATTR(XGMI_SOCKET0, XGMI_DIE1, XGMI_ALL_LANES, XGMI_TX_EQ_DATA_MODE_LIST)
#define MAKE_TX_EQ_SOCKET0_DIE2_EACH_LANES()             MAKE_TX_EQ_ATTR(XGMI_SOCKET0, XGMI_DIE2, XGMI_ALL_LANES, XGMI_TX_EQ_DATA_MODE_LIST)
#define MAKE_TX_EQ_SOCKET0_DIE3_EACH_LANES()             MAKE_TX_EQ_ATTR(XGMI_SOCKET0, XGMI_DIE3, XGMI_ALL_LANES, XGMI_TX_EQ_DATA_MODE_LIST)
#define MAKE_TX_EQ_SOCKET0_DIE4_EACH_LANES()             MAKE_TX_EQ_ATTR(XGMI_SOCKET0, XGMI_DIE4, XGMI_ALL_LANES, XGMI_TX_EQ_DATA_MODE_LIST)
#define MAKE_TX_EQ_SOCKET0_DIE5_EACH_LANES()             MAKE_TX_EQ_ATTR(XGMI_SOCKET0, XGMI_DIE5, XGMI_ALL_LANES, XGMI_TX_EQ_DATA_MODE_LIST)
#define MAKE_TX_EQ_SOCKET0_DIE6_EACH_LANES()             MAKE_TX_EQ_ATTR(XGMI_SOCKET0, XGMI_DIE6, XGMI_ALL_LANES, XGMI_TX_EQ_DATA_MODE_LIST)
#define MAKE_TX_EQ_SOCKET0_DIE7_EACH_LANES()             MAKE_TX_EQ_ATTR(XGMI_SOCKET0, XGMI_DIE7, XGMI_ALL_LANES, XGMI_TX_EQ_DATA_MODE_LIST)
#define MAKE_TX_EQ_SOCKET0_DIE0_EACH_LANES_COMPACT()             MAKE_TX_EQ_ATTR(XGMI_SOCKET0, XGMI_DIE0, XGMI_ALL_LANES, XGMI_TX_EQ_DATA_MODE_LIST_COMPACT)
#define MAKE_TX_EQ_SOCKET0_DIE1_EACH_LANES_COMPACT()             MAKE_TX_EQ_ATTR(XGMI_SOCKET0, XGMI_DIE1, XGMI_ALL_LANES, XGMI_TX_EQ_DATA_MODE_LIST_COMPACT)
#define MAKE_TX_EQ_SOCKET0_DIE2_EACH_LANES_COMPACT()             MAKE_TX_EQ_ATTR(XGMI_SOCKET0, XGMI_DIE2, XGMI_ALL_LANES, XGMI_TX_EQ_DATA_MODE_LIST_COMPACT)
#define MAKE_TX_EQ_SOCKET0_DIE3_EACH_LANES_COMPACT()             MAKE_TX_EQ_ATTR(XGMI_SOCKET0, XGMI_DIE3, XGMI_ALL_LANES, XGMI_TX_EQ_DATA_MODE_LIST_COMPACT)
#define MAKE_TX_EQ_SOCKET0_DIE4_EACH_LANES_COMPACT()             MAKE_TX_EQ_ATTR(XGMI_SOCKET0, XGMI_DIE4, XGMI_ALL_LANES, XGMI_TX_EQ_DATA_MODE_LIST_COMPACT)
#define MAKE_TX_EQ_SOCKET0_DIE5_EACH_LANES_COMPACT()             MAKE_TX_EQ_ATTR(XGMI_SOCKET0, XGMI_DIE5, XGMI_ALL_LANES, XGMI_TX_EQ_DATA_MODE_LIST_COMPACT)
#define MAKE_TX_EQ_SOCKET0_DIE6_EACH_LANES_COMPACT()             MAKE_TX_EQ_ATTR(XGMI_SOCKET0, XGMI_DIE6, XGMI_ALL_LANES, XGMI_TX_EQ_DATA_MODE_LIST_COMPACT)
#define MAKE_TX_EQ_SOCKET0_DIE7_EACH_LANES_COMPACT()             MAKE_TX_EQ_ATTR(XGMI_SOCKET0, XGMI_DIE7, XGMI_ALL_LANES, XGMI_TX_EQ_DATA_MODE_LIST_COMPACT)

// Macros for socket 1
#define MAKE_TX_EQ_SOCKET1_DIE_LANE(DieMask, LaneMask, DataMode)    MAKE_TX_EQ_ATTR(XGMI_SOCKET1, DieMask, LaneMask, DataMode)
#define MAKE_TX_EQ_SOCKET1_DIE_LANE_PAIR(DieMask, LaneMask)         MAKE_TX_EQ_ATTR(XGMI_SOCKET1, DieMask, LaneMask, XGMI_TX_EQ_DATA_MODE_PAIR)
#define MAKE_TX_EQ_SOCKET1_DIE_LANE_LIST(DieMask, LaneMask)         MAKE_TX_EQ_ATTR(XGMI_SOCKET1, DieMask, LaneMask, XGMI_TX_EQ_DATA_MODE_LIST)
#define MAKE_TX_EQ_SOCKET1_DIE0_ALL_LANES()             MAKE_TX_EQ_ATTR(XGMI_SOCKET1, XGMI_DIE0, XGMI_ALL_LANES, XGMI_TX_EQ_DATA_MODE_PAIR)
#define MAKE_TX_EQ_SOCKET1_DIE1_ALL_LANES()             MAKE_TX_EQ_ATTR(XGMI_SOCKET1, XGMI_DIE1, XGMI_ALL_LANES, XGMI_TX_EQ_DATA_MODE_PAIR)
#define MAKE_TX_EQ_SOCKET1_DIE2_ALL_LANES()             MAKE_TX_EQ_ATTR(XGMI_SOCKET1, XGMI_DIE2, XGMI_ALL_LANES, XGMI_TX_EQ_DATA_MODE_PAIR)
#define MAKE_TX_EQ_SOCKET1_DIE3_ALL_LANES()             MAKE_TX_EQ_ATTR(XGMI_SOCKET1, XGMI_DIE3, XGMI_ALL_LANES, XGMI_TX_EQ_DATA_MODE_PAIR)
#define MAKE_TX_EQ_SOCKET1_DIE4_ALL_LANES()             MAKE_TX_EQ_ATTR(XGMI_SOCKET1, XGMI_DIE4, XGMI_ALL_LANES, XGMI_TX_EQ_DATA_MODE_PAIR)
#define MAKE_TX_EQ_SOCKET1_DIE5_ALL_LANES()             MAKE_TX_EQ_ATTR(XGMI_SOCKET1, XGMI_DIE5, XGMI_ALL_LANES, XGMI_TX_EQ_DATA_MODE_PAIR)
#define MAKE_TX_EQ_SOCKET1_DIE6_ALL_LANES()             MAKE_TX_EQ_ATTR(XGMI_SOCKET1, XGMI_DIE6, XGMI_ALL_LANES, XGMI_TX_EQ_DATA_MODE_PAIR)
#define MAKE_TX_EQ_SOCKET1_DIE7_ALL_LANES()             MAKE_TX_EQ_ATTR(XGMI_SOCKET1, XGMI_DIE7, XGMI_ALL_LANES, XGMI_TX_EQ_DATA_MODE_PAIR)
#define MAKE_TX_EQ_SOCKET1_DIE0_EACH_LANES()             MAKE_TX_EQ_ATTR(XGMI_SOCKET1, XGMI_DIE0, XGMI_ALL_LANES, XGMI_TX_EQ_DATA_MODE_LIST)
#define MAKE_TX_EQ_SOCKET1_DIE1_EACH_LANES()             MAKE_TX_EQ_ATTR(XGMI_SOCKET1, XGMI_DIE1, XGMI_ALL_LANES, XGMI_TX_EQ_DATA_MODE_LIST)
#define MAKE_TX_EQ_SOCKET1_DIE2_EACH_LANES()             MAKE_TX_EQ_ATTR(XGMI_SOCKET1, XGMI_DIE2, XGMI_ALL_LANES, XGMI_TX_EQ_DATA_MODE_LIST)
#define MAKE_TX_EQ_SOCKET1_DIE3_EACH_LANES()             MAKE_TX_EQ_ATTR(XGMI_SOCKET1, XGMI_DIE3, XGMI_ALL_LANES, XGMI_TX_EQ_DATA_MODE_LIST)
#define MAKE_TX_EQ_SOCKET1_DIE4_EACH_LANES()             MAKE_TX_EQ_ATTR(XGMI_SOCKET1, XGMI_DIE4, XGMI_ALL_LANES, XGMI_TX_EQ_DATA_MODE_LIST)
#define MAKE_TX_EQ_SOCKET1_DIE5_EACH_LANES()             MAKE_TX_EQ_ATTR(XGMI_SOCKET1, XGMI_DIE5, XGMI_ALL_LANES, XGMI_TX_EQ_DATA_MODE_LIST)
#define MAKE_TX_EQ_SOCKET1_DIE6_EACH_LANES()             MAKE_TX_EQ_ATTR(XGMI_SOCKET1, XGMI_DIE6, XGMI_ALL_LANES, XGMI_TX_EQ_DATA_MODE_LIST)
#define MAKE_TX_EQ_SOCKET1_DIE7_EACH_LANES()             MAKE_TX_EQ_ATTR(XGMI_SOCKET1, XGMI_DIE7, XGMI_ALL_LANES, XGMI_TX_EQ_DATA_MODE_LIST)
#define MAKE_TX_EQ_SOCKET1_DIE0_EACH_LANES_COMPACT()             MAKE_TX_EQ_ATTR(XGMI_SOCKET1, XGMI_DIE0, XGMI_ALL_LANES, XGMI_TX_EQ_DATA_MODE_LIST_COMPACT)
#define MAKE_TX_EQ_SOCKET1_DIE1_EACH_LANES_COMPACT()             MAKE_TX_EQ_ATTR(XGMI_SOCKET1, XGMI_DIE1, XGMI_ALL_LANES, XGMI_TX_EQ_DATA_MODE_LIST_COMPACT)
#define MAKE_TX_EQ_SOCKET1_DIE2_EACH_LANES_COMPACT()             MAKE_TX_EQ_ATTR(XGMI_SOCKET1, XGMI_DIE2, XGMI_ALL_LANES, XGMI_TX_EQ_DATA_MODE_LIST_COMPACT)
#define MAKE_TX_EQ_SOCKET1_DIE3_EACH_LANES_COMPACT()             MAKE_TX_EQ_ATTR(XGMI_SOCKET1, XGMI_DIE3, XGMI_ALL_LANES, XGMI_TX_EQ_DATA_MODE_LIST_COMPACT)
#define MAKE_TX_EQ_SOCKET1_DIE4_EACH_LANES_COMPACT()             MAKE_TX_EQ_ATTR(XGMI_SOCKET1, XGMI_DIE4, XGMI_ALL_LANES, XGMI_TX_EQ_DATA_MODE_LIST_COMPACT)
#define MAKE_TX_EQ_SOCKET1_DIE5_EACH_LANES_COMPACT()             MAKE_TX_EQ_ATTR(XGMI_SOCKET1, XGMI_DIE5, XGMI_ALL_LANES, XGMI_TX_EQ_DATA_MODE_LIST_COMPACT)
#define MAKE_TX_EQ_SOCKET1_DIE6_EACH_LANES_COMPACT()             MAKE_TX_EQ_ATTR(XGMI_SOCKET1, XGMI_DIE6, XGMI_ALL_LANES, XGMI_TX_EQ_DATA_MODE_LIST_COMPACT)
#define MAKE_TX_EQ_SOCKET1_DIE7_EACH_LANES_COMPACT()             MAKE_TX_EQ_ATTR(XGMI_SOCKET1, XGMI_DIE7, XGMI_ALL_LANES, XGMI_TX_EQ_DATA_MODE_LIST_COMPACT)

#define MAKE_TX_EQ_PAIR(Attr, Data)                           Attr, Data
#define MAKE_TX_EQ_LIST(Attr, Data0, ...)                     Attr, Data0, __VA_ARGS__
#define MAKE_TX_EQ_LIST_COMPACT(Attr, Lane0, Lane1, Lane2, Lane3, Lane4, Lane5, Lane6, Lane7, Lane8, Lane9, Lane10, Lane11, Lane12, Lane13, Lane14, Lane15)  \
                                                              Attr, MAKE_TX_EQ_LIST_COMPACT_DATA(Lane0, Lane1, Lane2, Lane3, Lane4, Lane5, Lane6, Lane7, Lane8, Lane9, Lane10, Lane11, Lane12, Lane13, Lane14, Lane15)
#define MAKE_TX_EQ_FREQ_TABLE(SpeedMask, TxEqPairOrList, ...)  MAKE_TX_EQ_FREQ_TBL(SpeedMask), TxEqPairOrList, __VA_ARGS__, MAKE_TX_EQ_FREQ_END()

typedef struct _XGMI_TX_EQ_COMPACT_LANE_PER_DIE {
  union {
  UINT32                  AttrLoc;              ///< Must be XGMI_ALL_LANES, XGMI_TX_EQ_DATA_MODE_LIST_COMPACT
  XGMI_TX_EQ_ATTR         Attr;                 ///< Attribute structure
  } unionAttr;
  XGMI_TX_EQ_DATA_LIST_COMPACT    CompactListData;
} XGMI_TX_EQ_COMPACT_LANE_PER_DIE;

///< Total 8 socket die indice, no direct mapping
#define MAKE_TX_EQ_FREQ_TABLE_COMPACT(SpeedMask, SD0, SD1, SD2, SD3, SD4, SD5, SD6, SD7)  \
      MAKE_TX_EQ_FREQ_TBL(SpeedMask), SD0, SD1, SD2, SD3, SD4, SD5, SD6, SD7, MAKE_TX_EQ_FREQ_END()

#define MAKE_TX_EQ_LANE_DATA(EqMain, EqPost, EqPre)         MAKE_TX_EQ_LIST_COMPACT_DATA_SUB(EqMain, EqPost, EqPre)

/*----------------------------------------------------------------------------
 *                           FUNCTIONS PROTOTYPE
 *
 *----------------------------------------------------------------------------
 */

#define  DF_MEM_INTLV_SOCKET  3
#define  DF_MEM_INTLV_DIE     2
#define  DF_MEM_INTLV_CHANNEL 1
#define  DF_MEM_INTLV_NONE    0

#define  DF_DRAM_INTLV_SIZE_256   0
#define  DF_DRAM_INTLV_SIZE_512   1
#define  DF_DRAM_INTLV_SIZE_1024  2
#define  DF_DRAM_INTLV_SIZE_2048  3

//#define AMD_FAMILY_AM     (AMD_FAMILY_16_AM)
// Family 15h AM steppings
//#define AMD_F17_ZP_A0    0x0000000002000000ull
//#define AMD_F17_ZP_Ax    (AMD_F17_ZP_A0)
//#define AMD_F17_ZP_ALL   0x0000000000010000ull
//#define AMD_FAMILY_17_ZP  0x0000000000010000ull
//#define AMD_F17_ALL  AMD_FAMILY_17_ZP
//#define AMD_F17_ALL_APCB AMD_F17_ZP_ALL

 //Note a is from 0 to 31
#define BP_SHIFT(a)   ((UINT64)1 << a)

// Breakpoint Definition
//UMC BPs
#define APCB_BP_UMC_PHASE_1_END                 BP_SHIFT (0)     // End of Phase 1 Initialization - all addressing/UMC configs done
#define APCB_BP_UMC_START_PMU_ON_IMAGE          BP_SHIFT (1)       // Start PMU on imagex - PHY init/SRAM Msg Block done ; just staring 1D training
#define APCB_BP_UMC_MISSION_MODE_CONFIG         BP_SHIFT (2)     // UMC mision mode configuration
#define APCB_BP_UMC_PMU_FINISHED                BP_SHIFT (3)     // PMU Finish
#define APCB_BP_UMC_2D_TRAINING_DONE            BP_SHIFT (4)     // PMU Based Training complete - 2D Training done
#define APCB_BP_UMC_MEM_PHASE_2_END             BP_SHIFT (5)     // End of Phase 2 Initialization - Mission mode timings updated (turn around timings)
#define APCB_BP_UMC_BEFORE_INITIAL_PSTATE        BP_SHIFT (6)     // Before initial P-state change
#define APCB_BP_UMC_AFTER_INITIAL_PSTATE         BP_SHIFT (7)     // After initial P-state change
#define APCB_BP_UMC_BEFORE_DRAM_READY           BP_SHIFT (8)     // Before set UMC DramReady = 1
#define APCB_BP_UMC_BEFORE_RRW_TEST             BP_SHIFT (9)

//DF BPs
#define APCB_BP_DF_INIT_START                   BP_SHIFT (10)
#define APCB_BP_DF_BEFORE_LINK_TRAINING         BP_SHIFT (11)
#define APCB_BP_DF_LINK_TRAINING_COMPLETE       BP_SHIFT (12)
#define APCB_BP_DF_BEFORE_CREDIT_RELEASE        BP_SHIFT (13)
#define APCB_BP_DF_INIT_COMPLETE                BP_SHIFT (14)
#define APCB_BP_DF_BEFORE_MEMCLR                BP_SHIFT (15)
#define APCB_BP_UMC_AFTER_RECOVERY_MOP_SR_DSTATE1_FUNCTION     BP_SHIFT (16)
#define APCB_BP_UMC_BEFORE_INITIAL_IN_PSTATE_FUNCTION          BP_SHIFT (17)     // Before initial P-state change in Pstate function

//Other BPS
#define APCB_BP_CUSTOM                          BP_SHIFT (30)
#define APCB_BREAKPOINT_DONE                    BP_SHIFT (31)


//BP related Register definitions
#define UMC_CTRL_SMN_BASE 0x51000
#define ENV_CONTROL_UMC_SCRATCH_REG_0   (UMC_CTRL_SMN_BASE | 0x050)    // UserDataPattern0
#define ENV_CONTROL_UMC_SCRATCH_REG_1   (UMC_CTRL_SMN_BASE | 0x054)    // UserDataPattern1
#define ENV_CONTROL_UMC_SCRATCH_REG_2   (UMC_CTRL_SMN_BASE | 0x058)    // UserDataPattern2
#define ENV_CONTROL_UMC_SCRATCH_REG_3   (UMC_CTRL_SMN_BASE | 0x05C)    // UserDataPattern3

#define APCB_BREAKPOINT_SMN_DATA_MBOX_0 ENV_CONTROL_UMC_SCRATCH_REG_2   // Data Mailbox
#define APCB_BREAKPOINT_SMN_CMD_MBOX_1 ENV_CONTROL_UMC_SCRATCH_REG_3   // Command Mailbox

#define APCB_BREAKPOINT_CMD_ABL_BP_FOUND    0x5000C001  // Command from ABL indicating that BP found
#define APCB_BREAKPOINT_CMD_DONE            0x5000C002  // Command from ABL to script indicating that command processed
#define APCB_BREAKPOINT_CMD_ABL_BP_DONE     0x5000DEAD  // Command from ABL indicating that All BPs are done
#define APCB_BREAKPOINT_CMD_CONTINUE        0xC001C001  // Command from script to ABL indicating continue execution
#define APCB_BREAKPOINT_CMD_EXTERNAL_ENABLE 0xC001BEE5  // Command to enable breakpoints
#define APCB_BREAKPOINT_CMD_BP_LIST         0xC001BB11  // Command from script to indicating
#define APCB_BREAKPOINT_CMD_GET_PMU_STAGE   0xC001BB12  // Command from script to get training stage of PMU flow

/** ESPI_CLOCKVAL
*   Value range for APCB_TOKEN_CONFIG_FCH_ESPI_CLOCK
*/
typedef enum {
  ESPI_CLOCKVAL_16MHZ,            ///< 16.6MHz
  ESPI_CLOCKVAL_33MHZ,            ///< 33MHz
  ESPI_CLOCKVAL_66MHZ,            ///< 66MHz
} ESPI_CLOCKVAL;

/** ESPI_IOMODEVAL
*   Value range for APCB_TOKEN_CONFIG_FCH_ESPI_IOMODE
*/
typedef enum {
  ESPI_IOMODEVAL_SINGLE,            ///< Single I/O
  ESPI_IOMODEVAL_DUAL,              ///< Dual I/O
  ESPI_IOMODEVAL_QUAD,              ///< Quad I/O
} ESPI_IOMODEVAL;

/** ESPI_ALERT_MODE_VAL 
*   Value range for APCB_TOKEN_CONFIG_FCH_ESPI_ALERT_MODE
*/
typedef enum {
  ESPI_ALERT_MODE_VAL_NO_ALERT_PIN,            ///< I/O[1] pin is used to signal the Alert event
  ESPI_ALERT_MODE_VAL_ALERT_PIN,               ///< A dedicated Alert# pin is used to signal the Alert event
} ESPI_ALERT_MODE_VAL;

#endif

