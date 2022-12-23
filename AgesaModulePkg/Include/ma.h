/* $NoKeywords:$ */
/**
 * @file
 *
 * ma.h
 *
 * ARDK common header file
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

#ifndef _MA_H_
#define _MA_H_

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


#define MAX_CS_PER_CHANNEL      8   ///< Max CS per channel
/*----------------------------------------------------------------------------
 *                         TYPEDEFS, STRUCTURES, ENUMS
 *
 *----------------------------------------------------------------------------
 */

/** MARDK Structure*/
typedef struct {
  UINT16   Speed;                  ///< Dram speed in MHz
  UINT8    Loads;                  ///< Number of Data Loads
  UINT32   AddrTmg;                ///< Address Timing value
  UINT32   Odc;                    ///< Output Driver Compensation Value
} PSCFG_ENTRY;

/** MARDK Structure*/
typedef struct {
  UINT16   Speed;                  ///< Dram speed in MHz
  UINT8    Loads;                  ///< Number of Data Loads
  UINT32   AddrTmg;                ///< Address Timing value
  UINT32   Odc;                    ///< Output Driver Compensation Value
  UINT8    Dimms;                  ///< Number of Dimms
} ADV_PSCFG_ENTRY;

/** MARDK Structure for RDIMMs*/
typedef struct {
  UINT16   Speed;                  ///< Dram speed in MHz
  UINT16   DIMMRankType;         ///< Bitmap of Ranks   //Bit0-3:DIMM0(1:SR, 2:DR, 4:QR, 0:No Dimm, 0xF:Any), Bit4-7:DIMM1, Bit8-11:DIMM2, Bit12-16:DIMM3
  UINT32   AddrTmg;                ///< Address Timing value
  UINT16   RC2RC8;                   ///< RC2 and RC8 value  //High byte: 1st pair value, Low byte: 2nd pair value
  UINT8    Dimms;                  ///< Number of Dimms
} ADV_R_PSCFG_ENTRY;

/** MARDK Structure*/
typedef struct {
  UINT16   DIMMRankType;         ///< Bitmap of Ranks   //Bit0-3:DIMM0(1:SR, 2:DR, 4:QR, 0:No Dimm, 0xF:Any), Bit4-7:DIMM1, Bit8-11:DIMM2, Bit12-16:DIMM3
  UINT32   PhyRODTCSLow;          ///< Fn2_9C 180
  UINT32   PhyRODTCSHigh;         ///< Fn2_9C 181
  UINT32   PhyWODTCSLow;          ///< Fn2_9C 182
  UINT32   PhyWODTCSHigh;         ///< Fn2_9C 183
  UINT8    Dimms;                  ///< Number of Dimms
} ADV_PSCFG_ODT_ENTRY;

/** MARDK Structure for Write Levelization ODT*/
typedef struct {
  UINT16   DIMMRankType;         ///< Bitmap of Ranks   //Bit0-3:DIMM0(1:SR, 2:DR, 4:QR, 0:No Dimm, 0xF:Any), Bit4-7:DIMM1, Bit8-11:DIMM2, Bit12-16:DIMM3
  UINT8    PhyWrLvOdt[MAX_CS_PER_CHANNEL / 2];            ///< WrLvOdt (Fn2_9C_0x08[11:8]) Value for each Dimm
  UINT8    Dimms;                ///< Number of Dimms
} ADV_R_PSCFG_WL_ODT_ENTRY;

/*----------------------------------------------------------------------------
 *                           FUNCTIONS PROTOTYPE
 *
 *----------------------------------------------------------------------------
 */

AGESA_STATUS
MemAGetPsCfgDef (
  IN OUT   MEM_DATA_STRUCT *MemData,
  IN       UINT8 SocketID,
  IN OUT   CH_DEF_STRUCT *CurrentChannel
  );

UINT16
MemAGetPsRankType (
  IN       CH_DEF_STRUCT *CurrentChannel
  );

#endif  /* _MA_H_ */

