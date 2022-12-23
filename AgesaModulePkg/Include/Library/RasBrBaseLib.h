/* $NoKeywords:$ */
/**
 * @file
 *
 * MEMORY SMM Library
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AMD Memory Smm Library
 * @e sub-project:  Library
 * @e \$Revision$   @e \$Date$
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
#ifndef DRAM_MAP_KB_H_
#define DRAM_MAP_CZ_H_

#define BUS_0 0
#define FUNCTION_1 1
#define FUNCTION_2 2
#define FUNCTION_3 3
#define DEVICE_24 24

#define NUM_NODES 1
#define NUM_CHANNELS_PER_NODE  2
#define NUM_CS_PER_CHANNEL  4
#define MAX_BANK_ADDR  0x7
#define MAX_ROW_ADDR  0xFFFF
#define MAX_COL_ADDR  0x3FFF

VOID
PlatformTranslateSysAddrToCS (
  IN       UINT64      SysAddr,
     OUT   BOOLEAN     *CSFound,
     OUT   UINT64      *NormalizedChannelAddr,
     OUT   UINT8       *NodeID,
     OUT   UINT8       *ChannelSelect,
     OUT   UINT8       *ChipSelect,
     OUT   UINT8       *Bank,
     OUT   UINT32      *Row,
     OUT   UINT16      *Col
  );

VOID
PlatformTranslateCsAddrToSys (
  IN       UINT64      NormalizedChannelAddr,
  IN       UINT8       NormalizedDieId,
  IN       UINT8       ChannelSelect,
     OUT   BOOLEAN     *CSFound,
     OUT   UINT64      *SystemAddr,
     OUT   UINT8       *ChipSelect,
     OUT   UINT8       *Bank,
     OUT   UINT32      *Row,
     OUT   UINT16      *Col
  );

#endif

