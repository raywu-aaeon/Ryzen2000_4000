
/* $NoKeywords:$ */
/**
 * @file
 *
 * @e \$Revision:$   @e \$Date:$
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


#include "MyPorting.h"
#include <RV/APCB.h>
#include <ApcbCustomizedDefinitions.h>
#include <ApcbDefaults.h>

CHAR8 mDummyBuf;

APCB_TYPE_DATA_START_SIGNATURE();
APCB_TYPE_HEADER       ApcbTypeHeader = {
  APCB_GROUP_DF,
  APCB_DF_TYPE_CONFIG_DEFAULT_PARAMETERS,
  (
    sizeof (APCB_TYPE_HEADER)
  ),
  0,
  0,
  0
};  // SizeOfType will be fixed up by tool

APCB_PARAM_ATTRIBUTE  ParameterListDefaultsAttribute[] = {
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_DF_GMI_ENCRYPT, sizeof (UINT8) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_DF_XGMI_ENCRYPT, sizeof (UINT8) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_DF_SAVE_RESTORE_MEM_ENCRYPT, sizeof (UINT8) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_DF_SYS_STORAGE_AT_TOP_OF_MEM, sizeof (UINT8) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_DF_PROBE_FILTER_ENABLE, sizeof (UINT8) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_DF_BOTTOMIO, sizeof (UINT8) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_DF_MEM_INTERLEAVING, sizeof (UINT8) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_DF_DRAM_INTERLEAVE_SIZE, sizeof (UINT8) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_DF_ENABLE_CHAN_INTLV_HASH, sizeof (UINT8) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_DF_PCI_MMIO_SIZE, sizeof (UINT32) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_DF_CAKE_CRC_THRESH_PERF_BOUNDS, sizeof (UINT32) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_DF_MEM_CLEAR, sizeof (BOOLEAN) - 1, 0},
  {0, APCB_TOKEN_CONFIG_LIMIT, 0, 0},
};

_1BYTE_ALIGN UINT8  ParameterListDefaultsValue[] = {
  BSU08 (BLDCFG_DF_GMI_ENCRYPT),                  //< GMI encryption
  BSU08 (BLDCFG_DF_XGMI_ENCRYPT),                 //< xGMI encryption
  BSU08 (BLDCFG_DF_SAVE_RESTORE_MEM_ENCRYPT),     //< Save/Restore memory encryption
  BSU08 (BLDCFG_DF_SYS_STORAGE_AT_TOM),           //< Global CC6 enable
  BSU08 (BLDCFG_DF_PROBE_FILTER_ENABLE),          //< SPF
  BSU08 (BLDCFG_DF_BOTTOM_IO),                    //< Bottom IO
  BSU08 (BLDCFG_DF_MEM_INTERLEAVING),             //< Channel, Die, Socket interleaving control
  BSU08 (BLDCFG_DF_DRAM_INTLV_SIZE),              //< Address bit to interleave on
  BSU08 (BLDCFG_DF_CHAN_INTLV_HASH_EN),           //< Enable channel interleaving hash
  BSU32 (BLDCFG_DF_PCI_MMIO_SIZE),                //< Size in bytes of space used for PCI MMIO
  BSU32 (BLDCFG_DF_CAKE_CRC_THRESH_PERF_BOUNDS),  //< Percentage of performance to sacrifice for CAKE CRC in 0.00001% units
  BSBLN (BLDCFG_DF_MEM_CLEAR),          //< Request to do DF PIE mem clear
  BSU08 (0xFF)
};

APCB_TYPE_DATA_END_SIGNATURE();


int main(IN int argc, IN char * argv[])
{
  return 0;
}





