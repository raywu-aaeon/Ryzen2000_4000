/* $NoKeywords:$ */
/**
 * @file
 *
 * mttEdgeDetect.h
 *
 * Technology Common Training Header file
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem)
 * @e \$Revision: 309090 $ @e \$Date: 2014-12-10 02:28:05 +0800 (Wed, 10 Dec 2014) $
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

#ifndef _MTTEDGEDETECT_H_
#define _MTTEDGEDETECT_H_

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


//#define SCAN_LEFT       0            ///<  Scan Down
//#define SCAN_RIGHT      1            ///<  Scan Up
#define LEFT_EDGE       0            ///<  searching for the left edge
#define RIGHT_EDGE      1            ///<  searching for the right edge

#define SweepStages     4
#define TRN_DELAY_MAX   31           ///<  Max Virtual delay value for DQS Position Training

/*----------------------------------------------------------------------------
 *                         TYPEDEFS, STRUCTURES, ENUMS
 *
 *----------------------------------------------------------------------------
 */

/**
 *  Sweep Table Structure. ROM based table defining parameters for DQS position
 *  training delay sweep.
*/
typedef struct {
  INT8    BeginDelay;          ///<  Starting Delay Value
  INT8    EndDelay;            ///<  Ending Delay Value
  BOOLEAN ScanDir;             ///<  Scan Direction.  0 = down, 1 = up
  INT8    Step;                ///<  Amount to increment delay value
  UINT16  EndResult;           ///<  Result value to stop sweeping (to compare with failure mask)
  BOOLEAN MinMax;              ///<  Flag indicating lower (left edge) or higher(right edge)
} DQS_POS_SWEEP_TABLE;

/**
 * Sweep Information Struct - Used to track data through the DQS Delay Sweep
 *
*/
typedef struct _SWEEP_INFO {
  BOOLEAN Error;                               ///< Indicates an Error has been found
  UINT32  TestAddrRJ16[MAX_CS_PER_CHANNEL];    ///< System address of chipselects RJ 16 bits (Addr[47:16])
  BOOLEAN CsAddrValid[MAX_CS_PER_CHANNEL];     ///< Indicates which chipselects to test
  INT8    BeginDelay;                          ///< Beginning Delay value (Virtual)
  INT8    EndDelay;                            ///< Ending Delay value (Virtual)
  INT8    Step;                                ///< Amount to Inc or Dec Virtual Delay value
  BOOLEAN Edge;                                ///< Left or right edge (0 = LEFT, 1= RIGHT)
  UINT16  EndResult;                           ///< Result value that will stop a Dqs Sweep
  UINT16  InsertionDelayMsk;                   ///< Mask of Byte Lanes that should use ins. dly. comparison
  UINT16  LaneMsk;                             ///< Mask indicating byte lanes to update
  UINT16  ResultFound;                         ///< Mask indicating byte lanes where desired result was found on a sweep
  INT8    *TrnDelays;                          ///< Delay Values for each byte (Virtual).  Points into the delay values
} SWEEP_INFO;                                  ///< stored in the CH_DEF_STRUCT.

/*----------------------------------------------------------------------------
 *                           FUNCTIONS PROTOTYPE
 *
 *----------------------------------------------------------------------------
 */



#endif  /* _MTTEDGEDETECT_H_ */



