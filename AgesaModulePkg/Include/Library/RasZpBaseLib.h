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
#ifndef _RAS_ZP_BASE_LIB_H_
#define _Ras_ZP_BASE_LIB_H_

#include "AmdRasRegistersZp.h"
#include "AmdRas.h"

#define NB_SMN_INDEX_2  0xb8
#define NB_SMN_DATA_2   0xbc

#define MYDIETYPELO 21
#define MYDIETYPEHI 22
#define SOCKETIDSHIFTLO 28
#define SOCKETIDSHIFTHI 31
#define SOCKETIDMASKLO 16
#define SOCKETIDMASKHI 23
#define DIEIDSHIFTLO 24
#define DIEIDSHIFTHI 27
#define DIEIDMASKLO 8
#define DIEIDMASKHI 15
#define BLKINSTCOUNTLO 0
#define BLKINSTCOUNTHI 7
#define BLOCKFABRICIDLO 8
#define BLOCKFABRICIDHI 15
#define HIADDROFFSETEN 0
#define HIADDROFFSETLO 20
#define HIADDROFFSETHI 31
#define ADDRRNGVAL 0
#define DRAMBASEADDRLO 12
#define DRAMBASEADDRHI 31
#define DRAMLIMITADDRLO 12
#define DRAMLIMITADDRHI 31
#define LGCYMMIOHOLEEN 1
#define DRAMHOLEBASELO 24
#define DRAMHOLEBASEHI 31
#define INTLVADDRSELLO 8
#define INTLVADDRSELHI 10
#define INTLVNUMCHANLO 4
#define INTLVNUMCHANHI 7
#define INTLVNUMDIESLO 10
#define INTLVNUMDIESHI 11
#define INTLVNUMSKTS 8
#define DSTFABRICIDLO 0
#define DSTFABRICIDHI 7
#define NUM_DRAM_MAPS 16
#define BCAST 0xffffffff
#define DIE_PER_SOCKET 4
#define UMC_PER_DIE 2
#define CHANNEL_PER_UMC 1

#define DF_SYSCFG_ADDR ((1<<10)|(0x200))
#define DF_SYSFABIDMASK_ADDR ((1<<10)|(0x208))
#define DF_FABBLKINSTCNT_ADDR ((0<<10)|(0x040))
#define DF_FABBLKINFO3_ADDR ((0<<10)|(0x050))
#define DF_DRAMBASE0_ADDR ((0<<10)|(0x110))
#define DF_DRAMLIMIT0_ADDR ((0<<10)|(0x114))
#define DF_DRAMOFFSET0_ADDR ((0<<10)|(0x1B0)) // DramOffset0 doesn't technically exist.
#define DF_DRAMHOLECTRL_ADDR ((0<<10)|(0x104))
#define FABRIC_REG_ACC_BC    (0xFF)

/* Fabric Indirect Config Access Address 3 Register */
#define FICAA3_FUNC 0x4
#define FICAA3_REG 0x05C

/* Fabric Indirect Config Access Data 3 Low Register */
#define FICAD3_LO_FUNC 0x4
#define FICAD3_LO_REG 0x98

/* Fabric Indirect Config Access Data 3 High Register */
#define FICAD3_HI_FUNC 0x4
#define FICAD3_HI_REG 0x9C

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

VOID
NormalizedToBankAddrMap (
  UINT64  ChannelAddr,
  UINT32 CSMask,
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
  UINT8 chan,
  UINT8 vcm_en,
  UINT8 numbgbits,
  UINT8 bankgroupen,
  UINT8 invertmsbse,
  UINT8 invertmsbso,
  UINT8 rm0sec,
  UINT8 rm1sec,
  UINT8 rm2sec,
  UINT8 chansec,
  UINT8 invertmsbsesec,
  UINT8 invertmsbsosec,
  UINT64 CSMasksec,
  UINT8 SEC,
  UINT8 cs,
  UINT32 addrhashbank0,
  UINT32 addrhashbank1,
  UINT32 addrhashbank2,
  UINT32 addrhashbank3,
  UINT32 addrhashbank4,
  UINT32 addrhashbankpc,
  UINT32 addrhashbankpc2,
  UINT32 addrhashnormaddr0,
  UINT32 addrhashnormaddr1
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
  UINT64  sysAddr,
  UINT32  ccmInstanceId
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

#endif //_RAS_ZP_BASE_LIB_H_

