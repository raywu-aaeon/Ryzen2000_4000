/*
*****************************************************************************
*
* Copyright 2016 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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
*/
#ifndef _RAS_SSP_BASE_LIB_H_
#define _Ras_SSP_BASE_LIB_H_

#include "AmdRasRegistersSsp.h"
#include "AmdRas.h"

UINT64 
pow_ras (
  UINTN   input,
  UINTN   exp
  );

UINT64
getBits64 (
  UINT32 lowBit,
  UINT32 highBit,
  UINT64 data
  );

UINT32
getBits (
  UINT32 lowBit,
  UINT32 highBit,
  UINT32 data
  );

UINT32
getBit (
  UINT32 bit,
  UINT32 data
  );

UINTN
convert_to_addr_trans_index (
  UINTN  pkg_no,
  UINTN  mpu_no,
  UINTN  umc_inst_num,
  UINTN  umc_chan_num
  );

BOOLEAN
internal_bit_wise_xor (
  UINT32  inp
  );

UINT32 
smnRegRead (
  UINTN   socket,
  UINTN   die,
  UINTN   umc,
  UINTN   ch,
  UINTN   offset,
  UINTN   BusNumberBase
  );

UINT32
popcnt (
  UINT32  inp
  );

VOID
NormalizedToBankAddrMap (
  UINT64  ChannelAddr,
  UINT64 CSMasksec,
  UINT8 *Bank,
  UINT32 *Row,
  UINT16 *Col,
  UINT8 *Rankmul,
  UINT8 numbankbits,
  UINT8 bank4,
  UINT8 bank3,
  UINT8 bank2,
  UINT8 bank1,
  UINT8 bank0,
  UINT8 numrowlobits,
  UINT8 numrowhibits,
  UINT8 numcolbits,
  UINT8 row_lo0,
  UINT8 row_hi0,
  UINT32 COL0REG,
  UINT32 COL1REG,
  UINT8 numcsbits,
  UINT8 rm0,
  UINT8 rm1,
  UINT8 rm2,
  UINT8 invertmsbse,
  UINT8 invertmsbso,
  UINT8 rm0sec,
  UINT8 rm1sec,
  UINT8 rm2sec,
  UINT8 invertmsbsesec,
  UINT8 invertmsbsosec,
  UINT8 SEC,
  UINT8 cs,
  UINT32 addrhashbank0,
  UINT32 addrhashbank1,
  UINT32 addrhashbank2,
  UINT32 addrhashbank3,
  UINT32 addrhashbank4
  );

VOID
translate_norm_to_dram_addr (
  UINT64  ChannelAddr,
  UINT8   pkg_no,
  UINT8   mpu_no,
  UINT8   umc_inst_num, 
  UINT8   umc_chan_num,
  UINT8   *cs_num,
  UINT8   *bank,
  UINT32  *row,
  UINT16  *col,
  UINT8   *rankmul
  );

UINT32
checkDramHit (
  UINT64  sysAddr
  );

UINT64 
calcSysAddr (
  UINT64  normAddr,
  UINT32  mySocketNum,
  UINT32  myDieNum,
  UINT32  myChannelNum
  );

NORMALIZED_ADDRESS
calcNormAddr (
    UINT64 sysAddr
    );

UINT64
get_pcie_ccix_address (
  IN UINT64 address,
  IN BOOLEAN ccix_interleave_en,
  IN INT32 ccix_sdp_port_num_insert_sel,
  IN INT32 ccix_port_number,
  IN INT32 ccix_interleaved_addr_sel,
  IN INT32 ccix_interleaved_addr_remove0,
  IN INT32 ccix_interleaved_addr_remove1,
  IN INT32 ccix_if
  );

VOID
RasSmnRead (
  IN       UINT32              IohcBus,
  IN       UINT32              SmnAddress,
  IN       UINT32              *Value
  );

VOID
RasSmnWrite (
  IN       UINT32              IohcBus,
  IN       UINT32              SmnAddress,
  IN       UINT32              *Value
  );

VOID
RasSmnRW (
  IN       UINT32              IohcBus,
  IN       UINT32              SmnAddress,
  IN       UINT32              AndMask,
  IN       UINT32              OrMask
  );

VOID
RasSmnRead8 (
  IN       UINT32              IohcBus,
  IN       UINT32              SmnAddress,
  IN       UINT8               *Value8
  );

VOID
RasSmnWrite8 (
  IN       UINT32              IohcBus,
  IN       UINT32              SmnAddress,
  IN       UINT8               *Value8
  );

VOID
RasSmnRW8 (
  IN       UINT32              IohcBus,
  IN       UINT32              SmnAddress,
  IN       UINT8               AndMask,
  IN       UINT8               OrMask
  );

extern  ADDR_DATA               *gAddrData;

#endif //_RAS_SSP_BASE_LIB_H_

