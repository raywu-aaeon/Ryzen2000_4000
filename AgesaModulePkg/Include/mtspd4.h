/* $NoKeywords:$ */
/**
 * @file
 *
 * mtspd4.h
 *
 * Technology SPD support for DDR4
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/Tech/DDR4)
 * @e \$Revision: 329870 $ @e \$Date: 2015-10-29 13:13:29 +0800 (Thu, 29 Oct 2015) $
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

#ifndef _MTSPD4_H_
#define _MTSPD4_H_

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

/*===============================================================================
 *   JEDEC DDR 4
 *===============================================================================
 */

// -----------------------------------------------------------------------------------------------------
//
// Address map
//
//
//Block  Range    Description
//  0   0~127     Base Configuration and DRAM Parameters
//  1   128~191   Module Specific Parameters -- See annexes for details
//      192~255   Hybrid Memory Parameters -- See annexes for details
//  2   256~319   Reserved; must be coded as 0x00
//      320~383   Manufacturing Information
//  3   384~511   End User Programmable
//
// -----------------------------------------------------------------------------------------------------
//
//
/// DDR4 SPD BLOCK
typedef struct _DDR4_SPD_BLOCK {
  UINT8 Array[126];     ///< First 127 Bytes of an SPD Block
  UINT16 CRC;           ///< 16 Bit CRC for this block
} DDR4_SPD_BLOCK;

// -----------------------------------------------------------------------------------------------------
//
// Block 0: Base Configuration and DRAM Parameters
//
// Byte 0: Number of Serial PD Bytes Written / SPD Device Size / CRC Coverage 1, 2
#define SPD_BYTES_USED                 0
  #define BYTES_USED_SHIFT             0
  #define BYTES_USED_MASK              0x0F
#define SPD_BYTES_TOTAL                0
  #define BYTES_TOTAL_SHIFT            4
  #define BYTES_TOTAL_MASK             0x07

// Byte 1: SPD Revision
#define SPD_SPD_REVISION               1

// Byte 2: Key Byte / DRAM Device Type
#define SPD_DRAM_DEVICE_TYPE           2
  #define DEVICE_TYPE_DDR3             0x0B
  #define DEVICE_TYPE_DDR4             0x0C

// Byte 3: Key Byte / Module Type
#define SPD_BASE_MODULE_TYPE           3
  #define MODULE_TYPE_MASK             0x0F
  #define MOD_TYPE_EXT                 0x00
  #define MOD_TYPE_RDIMM               0x01
  #define MOD_TYPE_UDIMM               0x02
  #define MOD_TYPE_SODIMM              0x03
  #define MOD_TYPE_LRDIMM              0x04
  #define MOD_TYPE_MINI_RDIMM          0x05
  #define MOD_TYPE_MINI_UDIMM          0x06
  #define MOD_TYPE_72b_SO_RDIMM        0x08
  #define MOD_TYPE_72b_SO_UDIMM        0x09
  #define MOD_TYPE_16b_SODIMM          0x0C
  #define MOD_TYPE_32b_SODIMM          0x0D
  #define MOD_TYPE_NO_BASE_MEMORY      0x0F
  #define MOD_TYPE_RDIMM               0x01
  #define MOD_TYPE_RDIMM               0x01
  #define MOD_TYPE_RDIMM               0x01
  #define MOD_TYPE_RDIMM               0x01

#define SPD_HYBRID_MEDIA               3
  #define HYBRID_MEDIA_SHIFT           4
  #define HYBRID_MEDIA_MASK            7
  #define NVDIMM_HYBRID                1
#define SPD_HYBRID                     3
  #define HYBRID_SHIFT                 7
  #define HYBRID_MASK                  1
  #define HYBRID_TYPE                  1

// Byte 4: SDRAM Density and Banks
#define SPD_CAPACITY                   4
  #define CAPACITY_MASK                0xF
#define SPD_BANK_ADDR_BITS             4
 #define BANK_ADDR_BITS_SHIFT          4
 #define BANK_ADDR_BITS_MASK           3
// #define GET_BANK_ADDR_BITS(byte) (((byte) >> 4) & 3)
#define SPD_BANK_GROUP_BITS            4
 #define BANK_GROUP_BITS_SHIFT         6
 #define BANK_GROUP_BITS_MASK          3

// Byte 5: SDRAM Addressing
#define SPD_ROWS_COLS                  5 // [5:0] Rows and Columns
#define ROW_COL_MASK                0x3F //
#define SPD_COL_ADDR_BITS              5 // [2:0] Column Address Bits
  #define COL_ADDR_BITS_MASK           7
#define SPD_ROW_ADDR_BITS              5 // [5:3] Row Address Bits
  #define ROW_ADDR_BITS_SHIFT          3
  #define ROW_ADDR_BITS_MASK           7

// Byte 6: SDRAM Package Type
#define SPD_SIGNAL_LOADING             6
#define SPD_DIE_COUNT                  6
#define SPD_PACKAGE_TYPE               6

// Byte 7: SDRAM Optional Features
#define SPD_MAC                        7
  #define MAC_MASK                   0xF
#define SPD_TMAW                       7
  #define MAW_SHIFT                    4
  #define MAW_MASK                     3
#define Untested_MAC                   0
#define Unlimited_MAC                  8



// Byte 8: SDRAM Thermal and Refresh Options

// Byte 9: Other SDRAM Optional Features
#define SPD_PPR                        9

// Byte 10: Reserved -- must be coded as 0x00

// Byte 11: Module Nominal Voltage, VDD
#define SPD_DRAM_VDD                   11 //  [0] 1.2V Operable
                                          //  [1] 1.2V Endurant
                                          //  [2] TBD1 Operable
                                          //  [3] TBD1 Endurant
                                          //  [4] TBD2 Operable
                                          //  [5] TBD2 Endurant

// Byte 12: Module Organization
#define SPD_DEVICE_WIDTH               12 //
  #define DEVICE_WIDTH_MASK             7 //
#define SPD_RANKS                      12 //
  #define RANKS_SHIFT                   3 //
  #define RANKS_MASK                    7 //

// Byte 13: Module Memory Bus Width
#define SPD_BUS_WIDTH                  13 //
#define BUSWIDTH_MASK                   7 // [2:0] Primary Bus width
#define SPD_BUSWIDTH_EXT               13 //
  #define BUSWIDTH_EXT_ECC             (1 << 3)

// Byte 14: Module Thermal Sensor
#define SPD_THERMAL_SENSOR             14
  #define THERMAL_SENSOR_SHIFT          7 // [7] 1 = Thermal Sensor Present
  #define THERMAL_SENSOR_MASK           1 //

// Byte 15: Extended module type
#define SPD_BASE_MODULETYPE_EXT        15 // Reserved, must be coded as 0000

// Byte 16: Reserved -- must be coded as 0x00

// Byte 17: Timebases
#define SPD_FINE_TIMEBASE              17 // [1:0] 0 = 1pS, all others reserved
  #define FTB_MSK                       3
#define SPD_MEDIUM_TIMEBASE            17 // [3:2] 0 = 125pS, all others reserved
  #define MTB_SHIFT                     2
  #define MTB_MSK                       3

// Byte 18: SDRAM Minimum Cycle Time (tCKAVGmin)
#define SPD_TCK                        18 //

// Byte 19: SDRAM Maximum Cycle Time (tCKAVGmax)
#define SPD_TCK_MAX                    19 //

// Byte 20: CAS Latencies Supported, First Byte
// Byte 21: CAS Latencies Supported, Second Byte
// Byte 22: CAS Latencies Supported, Third Byte
// Byte 23: CAS Latencies Supported, Fourth Byte
#define SPD_CAS_BYTE_0                 20 //
#define SPD_CAS_BYTE_1                 21 //
#define SPD_CAS_BYTE_2                 22 //
#define SPD_CAS_BYTE_3                 23 //

// Byte 24: Minimum CAS Latency Time (tAAmin)
#define SPD_TAA                        24 //

// Byte 25: Minimum RAS to CAS Delay Time (tRCDmin)
#define SPD_TRCD                       25 //

// Byte 26: Minimum Row Precharge Delay Time (tRPmin)
#define SPD_TRP                        26 //

// Byte 27: Upper Nibbles for tRASmin and tRCmin
#define SPD_TRAS_UPPERNIBBLE           27 //
#define SPD_TRC_UPPERNIBBLE            27 //

// Byte 28: Minimum Active to Precharge Delay Time (tRASmin), Least Significant Byte
#define SPD_TRAS_LSB                   28 //

// Byte 29: Minimum Active to Active/Refresh Delay Time (tRCmin), Least Significant Byte
#define SPD_TRC_LSB                    29 //

// Byte 30: Minimum Refresh Recovery Delay Time (tRFC1min), LSB
// Byte 31: Minimum Refresh Recovery Delay Time (tRFC1min), MSB
#define SPD_TRFC1_LSB                  30 //
#define SPD_TRFC1_MSB                  31 //

// Byte 32: Minimum Refresh Recovery Delay Time (tRFC2min), LSB
// Byte 33: Minimum Refresh Recovery Delay Time (tRFC2min), MSB
#define SPD_TRFC2_LSB                  32 //
#define SPD_TRFC2_MSB                  33 //

// Byte 34: Minimum Refresh Recovery Delay Time (tRFC4min), LSB
// Byte 35: Minimum Refresh Recovery Delay Time (tRFC4min), MSB
#define SPD_TRFC4_LSB                  34 //
#define SPD_TRFC4_MSB                  35 //

// Byte 36: Minimum Four Activate Window Time (tFAWmin), Most Significant Nibble
#define SPD_TFAW_UPPERNIBBLE           36 //

// Byte 37: Minimum Four Activate Window Time (tFAWmin), Least Significant Byte
#define SPD_TFAW_LSB                   37 //

// Byte 38: Minimum Activate to Activate Delay Time (tRRD_Smin), different bank group
#define SPD_TRRD_S                     38 //

// Byte 39: Minimum Activate to Activate Delay Time (tRRD_Lmin), same bank group
#define SPD_TRRD_L                     39 //

// Byte 40: Minimum CAS to CAS Delay Time (tCCD_Lmin), same bank group
#define SPD_TCCD_L                     40 //

// Byte 41: Minimum Write Recovery Time (tWRmin)
#define SPD_TWR                        41 //

// Byte 42: Minimum Write to Read Time (tWTR_Smin), different bank group
#define SPD_TWTR_S                     42 //

// Byte 43: Minimum Write to Read Time (tWTR_Lmin), same bank group
#define SPD_TWTR_L                     43 //

// Bytes 44~59: Reserved -- must be coded as 0x00

// Bytes 60~77: Connector to SDRAM Bit Mapping
#define SPD_DQ_MAPPING                 60 //

// Bytes 78~116: Reserved -- must be coded as 0x00

// Byte 117: Fine Offset for Minimum CAS to CAS Delay Time (tCCD_Lmin), same bank group
#define SPD_TCCD_L_FTB                 117 //

// Byte 118: Fine Offset for Minimum Activate to Activate Delay Time (tRRD_Lmin), same bank group
#define SPD_TRRD_L_FTB                 118 //

// Byte 119: Fine Offset for Minimum Activate to Activate Delay Time (tRRD_Smin), different bank group
#define SPD_TRRD_S_FTB                 119 //

// Byte 120: Fine Offset for Minimum Activate to Activate/Refresh Delay Time (tRCmin)
#define SPD_TRC_FTB                    120 //

// Byte 121: Fine Offset for Minimum Row Precharge Delay Time (tRPmin)
#define SPD_TRP_FTB                    121 //

// Byte 122: Fine Offset for Minimum RAS to CAS Delay Time (tRCDmin)
#define SPD_TRCD_FTB                   122 //

// Byte 123: Fine Offset for Minimum CAS Latency Time (tAAmin)
#define SPD_TAA_FTB                    123 //

// Byte 124: Fine Offset for SDRAM Maximum Cycle Time (tCKAVGmax)
#define SPD_TCK_MAX_FTB                124 //

// Byte 125: Fine Offset for SDRAM Minimum Cycle Time (tCKAVGmin)
#define SPD_TCK_FTB                    125 //

// Byte 126: CRC for Base Configuration Section, Least Significant Byte
#define SPD_CRC_LSB                    126 //

// Byte 127: CRC for Base Configuration Section, Most Significant Byte
#define SPD_CRC_MSB                    127 //
//
// -----------------------------------------------------------------------------------------------------
// Module-Specific Section: Bytes 128~191 (0x080~0x0BF)
//
// This section contains SPD bytes which are specific to families DDR4 module families. Module
// Type Key Byte 3 is used as an index for the encoding of bytes 128~191. The content of bytes
// 128~191 are described in multiple annexes, one for each memory module family.
//
// -----------------------------------------------------------------------------------------------------
//
// DDR4 UDIMM Specific SPD Bytes
// The following is the SPD address map for the module specific section, bytes 128~255, of
// the SPD for Unbuffered Module Types.
//
// Byte 128: Raw Card Extension, Module Nominal Height
#define SPD_MODULE_HEIGHT              128 // [4:0] Module Nominal Height
#define SPD_RAW_CARD_REV_EXT           128 // [7:5] Raw Card Revision Extension

// Byte 129: Module Maximum Thickness
#define SPD_MAX_THICKNESS_FRONT        129
#define SPD_MAX_THICKNESS_BACK         129

// Byte 130: Reference Raw Card Used
#define SPD_RAWCARD                    130 // [4:0] Reference Raw Card
  #define RAWCARD_MASK                0x1F
#define SPD_RAWCARD_REV                130 // [6:5] Raw Card Revision
  #define RAWCARDREV_SHIFT               5
  #define RAWCARDREV_MASK                2
#define SPD_RAWCARD_EXT                130 // Raw Card Extension
                                           // 0 = R/C A through AL,
                                           // 1 = R/C AM through CB

// Byte 131: Address Mapping from Edge Connector to DRAM
#define SPD_ADDRMAP                    131
  #define ADDRMAP_MASK                 1 // [0] Rank 1 Mapping
                                         //     1 = Mirrored

// Bytes 132~191: Reserved -- Must be coded as 0x00

// Byte 254: CRC for SPD Block 1, Least Significant Byte 1
#define SPD_CRC_BLOCK1_LSB             254 //

// Byte 255: CRC for SPD Block 1, Most Significant Byte 1
#define SPD_CRC_BLOCK1_MSB             255 //

// -----------------------------------------------------------------------------------------------------
//
// DDR4 RDIMM Specific SPD Bytes
// The following is the SPD address map for the module specific section, bytes 128~191, of
// the SPD for Registered Module Types.
//
// Byte 128 Raw Card Extension, Module Nominal Height

// Byte 129 Module Maximum Thickness

// Byte 130 Reference Raw Card Used

// Byte 131 DIMM Module Attributes
#define SPD_NUM_REGISTERS              131 // Number of Registers
  #define NUM_REGISTERS_MASK             3 // [1:0] # of Registers on RDIMM
  #define NUM_REGISTERS_UNDEF            0 // Undefined number of registers

// Byte 132 RDIMM Thermal Heat Spreader Solution

// Byte 133 Register Manufacturer ID Code, Least Significant Byte

// Byte 134 Register Manufacturer ID Code, Most Significant Byte

// Byte 135 Register Revision Number

// Byte 136 Address Mapping from Register to DRAM

// Byte 137~191  Reserved -- must be coded as 0x00

// Byte 254 CRC for SPD Block 1, Least Significant Byte

// Byte 255 CRC for SPD Block 1, Most Significant Byte



//
// Byte 320: Module Manufacturer ID Code, Least Significant Byte
#define SPD_MANUFACTURER_ID_LSB        320
// Byte 321: Module Manufacturer ID Code, Most Significant Byte
#define SPD_MANUFACTURER_ID_MSB        321
// Byte 322: Module Manufacturing Location
// Bytes 323~324: Module Manufacturing Date
// Bytes 325~328: Module Serial Number
#define SPD_SERIAL_NUMBER              325
// Bytes 329~348: Module Part Number
#define SPD_PART_NUMBER                329
// Byte 349: Module Revision Code
// Byte 350: DRAM Manufacturers ID Code, Least Significant Byte
// Byte 351: DRAM Manufacturers ID Code, Most Significant Byte
// Byte 352: DRAM Stepping
// Bytes 353~381: Module Manufacturer Specific


// DDR3 Definitions for Reference
//
// #define SPD_BYTE_USED     0
// #define SPD_TYPE         2               /* SPD byte read location */
// #define JED_DDR4SDRAM    0xC             /* Jedec defined bit field */

// #define SPD_DIMM_TYPE    3               /* Key Byte/DRAM Device Type */
// #define SPD_ATTRIB      27               /* Upper Nibbles for tRASmin and tRCmin */
// #define JED_RDIMM       1
// #define JED_UDIMM       2
// #define JED_SODIMM
// #define JED_LRDIMM      4
// #define JED_UNDEFINED   0                /* Undefined value */

// #define SPD_L_BANKS      4               /* [7:4] number of [logical] banks on each device */ /* SDRAM Density and Banks */
// #define SPD_DENSITY     4                /* bit 3:0 */ /* SDRAM Density and Banks */
// #define SPD_ROW_SZ       5               /* bit 5:3 */ /* SDRAM Addressing */
// #define SPD_COL_SZ       5               /* bit 2:0 */ /* SDRAM Addressing */
// #define SPD_RANKS       12               /* bit 5:3 */ /* Module Organization */
// #define SPD_DEV_WIDTH    12              /* bit 2:0 */ /* Module Organization */
// #define SPD_ECCBITS     13               /* bit 4:3 */ /* Module Memory Bus Width */
// #define JED_ECC         8
// #define SPD_RAWCARD     130              /* bit 2:0 */  /* (Unbuffered): Reference Raw Card Used */
// #define SPD_ADDRMAP     131              /* bit 0 */  /* (Unbuffered): Address Mapping from Edge Connector to DRAM */

// #define SPD_TIMEBASES  17                /* Timebases */
// #define SPD_TIMEBASES_MTB  17            /* bit 3:2 - Timebases */
// #define SPD_TIMEBASES_FTB  17            /* bit 1:0 - Timebases */

// #define SPD_TCK        18                /* SDRAM Minimum Cycle Time (tCKAVGmin) */
// #define SPD_CAS_BYTE_0 20                /* CAS Latency Supported, First Byte */
// #define SPD_CAS_BYTE_1 21                /* CAS Latency Supported, Second Byte */
// #define SPD_CAS_BYTE_2 22                /* CAS Latency Supported, Third Byte */
// #define SPD_CAS_BYTE_3 23                /* CAS Latency Supported, Fourth Byte */
// #define SPD_TAA        24                /* Minimum CAS Latency Time (tAAmin) */

// #define SPD_TRP         26               /* Minimum Row Precharge Delay Time (tRPmin) */
// #define SPD_TRRD_S      38               /* Minimum Activate to Activate Delay Time (tRRD_Smin), different bank group */
// #define SPD_TRRD_L      39               /* Minimum Activate to Activate Delay Time (tRRD_Lmin), same bank group */
// #define SPD_TRCD        25               /* Minimum RAS to CAS Delay Time (tRCDmin) */
// #define SPD_TRAS        28               /* Minimum Active to Precharge Delay Time (tRASmin), Least Significant Byte */
// #define SPD_TRC         29               /* Minimum Active to Active/Refresh Delay Time (tRCmin), Least Significant Byte  */
// #define SPD_UPPER_TRC   27               /* bit 7:4 */ /* Upper Nibbles for tRASmin and tRCmin */
// #define SPD_UPPER_TRAS  27               /* bit 3:0 */ /* Upper Nibbles for tRASmin and tRCmin */
// #define SPD_TFAW        37               /* Minimum Four Activate Window Time (tFAWmin), Least Significant Byte 3 */
// #define SPD_UPPER_TFAW  36               /* Minimum Four Activate Window Time (tFAWmin), Most Significant Nibble 3 */

// #define SPD_TCK_FTB     125              /* Fine Offset for SDRAM Minimum Cycle Time (tCKAVGmin) */
// #define SPD_TAA_FTB     123              /* Fine Offset for SDRAM Minimum CAS Latency Time (tAAmin) */
// #define SPD_TRCD_FTB    122              /* Fine Offset for SDRAM Minimum RAS to CAS Delay Time (tRCDmin) */
// #define SPD_TRP_FTB     121              /* Fine Offset for SDRAM Minimum Row Precharge Delay Time (tRPmin) */
// #define SPD_TRC_FTB     120              /* Fine Offset for SDRAM Minimum Activate to Activate/Refresh Delay Time (tRCmin) */



/*----------------------------------------------------------------------------
 *                         TYPEDEFS, STRUCTURES, ENUMS
 *
 *----------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------
 *                           FUNCTIONS PROTOTYPE
 *
 *----------------------------------------------------------------------------
 */


#endif  /* _MTSPD4_H_ */



