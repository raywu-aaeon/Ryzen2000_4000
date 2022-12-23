/* $NoKeywords:$ */
/**
 * @file
 *
 * mtspd3.h
 *
 * Technology SPD support for DDR3
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/Tech/DDR3)
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

#ifndef _MTSPD3_H_
#define _MTSPD3_H_

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
 *   Jedec DDR III
 *===============================================================================
 */
#define SPD_BYTE_USED     0
#define SPD_TYPE         2              /* SPD byte read location */
#define JED_DDR_SDRAM     7              /* Jedec defined bit field */
#define JED_DDR2_SDRAM    8              /* Jedec defined bit field */
#define JED_DDR3SDRAM    0xB            /* Jedec defined bit field */

#define SPD_DIMM_TYPE    3
#define SPD_ATTRIB      21
#define JED_DIF_CK_MSK    0x20            /* Differential Clock Input */
#define JED_RDIMM       1
#define JED_MINIRDIMM   5
#define JED_UDIMM       2
#define JED_SODIMM       3
#define JED_LRDIMM      0xB
#define JED_72B_SODIMM  8
#define JED_UNDEFINED   0                /* Undefined value */

#define SPD_L_BANKS      4               /* [7:4] number of [logical] banks on each device */
#define SPD_DENSITY     4               /* bit 3:0 */
#define SPD_ROW_SZ       5               /* bit 5:3 */
#define SPD_COL_SZ       5               /* bit 2:0 */
#define SPD_RANKS       7               /* bit 5:3 */
#define SPD_DEV_WIDTH    7               /* bit 2:0 */
#define SPD_ECCBITS     8               /* bit 4:3 */
#define JED_ECC         8
#define SPD_RAWCARD     62              /* bit 2:0 */
#define SPD_ADDRMAP     63              /* bit 0 */

#define SPD_CTLWRD03     70              /* bit 7:4 */
#define SPD_CTLWRD04     71              /* bit 3:0 */
#define SPD_CTLWRD05     71              /* bit 7:4 */

#define SPD_FTB          9

#define SPD_DIVIDENT    10
#define SPD_DIVISOR     11

#define SPD_TCK         12
#define SPD_CASLO       14
#define SPD_CASHI       15
#define SPD_TAA         16

#define SPD_TRP         20
#define SPD_TRRD        19
#define SPD_TRCD        18
#define SPD_TRAS        22
#define SPD_TWR         17
#define SPD_TWTR        26
#define SPD_TRTP        27
#define SPD_TRC         23
#define SPD_UPPER_TRC   21              /* bit 7:4 */
#define SPD_UPPER_TRAS  21              /* bit 3:0 */
#define SPD_TFAW        29
#define SPD_UPPER_TFAW  28              /* bit 3:0 */

#define SPD_THERMAL_OPTIONS 31
#define EXT_TEMP_MASK        1
#define ASR_SHIFT            2
#define ASR_MASK             1

#define SPD_THERMAL_SENSOR  32
#define THERMAL_SENSOR_SHIFT 7               /* [7] 1 = Thermal Sensor Present */
#define THERMAL_SENSOR_MASK  1

#define SPD_TCK_FTB     34
#define SPD_TAA_FTB     35
#define SPD_TRCD_FTB    36
#define SPD_TRP_FTB     37
#define SPD_TRC_FTB     38

#define SPD_MAC         41

#define SPD_TRFC_LO     24
#define SPD_TRFC_HI     25

/*-----------------------------
 * Jedec DDR II related equates
 *-----------------------------
 */

#define CL_DEF          4              /* Default value for failsafe operation. 4=CL 6.0 T */
#define T_DEF           4              /* Default value for failsafe operation. 4=2.5ns (cycle time) */

#define BIAS_TRTP_T      4
#define BIAS_TRCD_T      5
#define BIAS_TRAS_T      15
#define BIAS_TRC_T       11
#define BIAS_TRRD_T      4
#define BIAS_TWR_T       4
#define BIAS_TRP_T       5
#define BIAS_TWTR_T      4
#define BIAS_TFAW_T      14

#define MIN_TRTP_T       4
#define MAX_TRTP_T       7
#define MIN_TRCD_T       5
#define MAX_TRCD_T       12
#define MIN_TRAS_T       15
#define MAX_TRAS_T       30
#define MIN_TRC_T        11
#define MAX_TRC_T        42
#define MIN_TRRD_T       4
#define MAX_TRRD_T       7
#define MIN_TWR_T        5
#define MAX_TWR_T        12
#define MIN_TRP_T        5
#define MAX_TRP_T        12
#define MIN_TWTR_T       4
#define MAX_TWTR_T       7
#define MIN_TFAW_T       16
#define MAX_TFAW_T       32

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


#endif  /* _MTSPD3_H_ */



