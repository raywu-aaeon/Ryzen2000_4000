/*****************************************************************************
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

/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */
#include <Filecode.h>
#include <Guid/EventGroup.h>
#include "AGESA.h"
#include "Addendum/Apcb/Inc/SSP/APOB.h"
#include <Library/DebugLib.h>
#include "Library/IdsLib.h"
#include <Library/UefiDriverEntryPoint.h>
#include <Library/BaseMemoryLib.h>
#include <Library/IoLib.h>
#include <Library/PciLib.h>
#include <Library/AmdPspApobLib.h>
#include <Library/RasSspBaseLib.h>
#include <Protocol/FabricTopologyServices2.h>
#include <Protocol/AmdCoreTopologyProtocol.h>
#include <Protocol/AmdCoreTopologyV2Protocol.h>
#include "AmdRasSspDxe.h"

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */
#define FILECODE RAS_AMDRASSSPDXE_AMDRASSSPDXE_FILECODE


#define RAS_MAX_CORES (CCX_MAX_SOCKETS * CCX_MAX_DIES_PER_SOCKET * CCD_MAX_CCDS_PER_DIE * CCD_MAX_COMPLEXES_PER_CCD * CCX_MAX_CORES_PER_COMPLEX * CCX_MAX_THREADS_PER_CORE)

/*----------------------------------------------------------------------------------------
 *                           G L O B A L   V A R I A B L E S
 *----------------------------------------------------------------------------------------
 */

extern  EFI_BOOT_SERVICES       *gBS;
ADDR_DATA               *gAddrData;
AMD_RAS_POLICY          *mAmdRasPolicy;

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */
EFI_STATUS
CollectDimmMap(VOID);

EFI_STATUS
CollectCpuMap(VOID);

EFI_STATUS
AmdRasPolicyInit(VOID);

//EFI_STATUS
//NbioErrThresInit(VOID);
VOID
NbioErrThresInit(
  IN EFI_EVENT  Event,
  IN VOID       *Context
);

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U R E S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *                          E X P O R T E D    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *                          T A B L E    D E F I N I T I O N S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------*/
/**
 * Read related register and save to global variable
 *
 * @param[in] pkgnoe            Die ID
 * @param[in] mpuno             Channel ID
 * @param[in] umcno             UMC ID
 * @param[in] umcchno           always = 0 in ZP
 * @param[in] BusNumberBase     PCI bus number
 * @retval    VOID
 *----------------------------------------------------------------------------------------*/
STATIC
VOID
retrieve_regs (
  UINTN   pkgno,
  UINTN   mpuno,
  UINTN   umcno,
  UINTN   umcchno,
  UINTN   BusNumberBase
  )
{
  UINTN  channel;

  channel = convert_to_addr_trans_index (pkgno, mpuno, umcno, umcchno);

  // UMC0CHx00000000 [DRAM CS Base Address] (BaseAddr), ch0_cs[3:0]_aliasSMN; UMC0CHx0000_000[[C,8,4,0]];
  // [31:1]BaseAddr: Base Address [39:9]
  gAddrData->CSBASE[channel][0] = ((smnRegRead (pkgno, mpuno, umcno, umcchno, 0x0, BusNumberBase) >> 1) << 1);
  gAddrData->CSBASE[channel][1] = ((smnRegRead (pkgno, mpuno, umcno, umcchno, 0x4, BusNumberBase) >> 1) << 1);
  gAddrData->CSBASE[channel][2] = ((smnRegRead (pkgno, mpuno, umcno, umcchno, 0x8, BusNumberBase) >> 1) << 1);
  gAddrData->CSBASE[channel][3] = ((smnRegRead (pkgno, mpuno, umcno, umcchno, 0xC, BusNumberBase) >> 1) << 1);
  IDS_HDT_CONSOLE (MAIN_FLOW, "\t\tBaseAddr-x00\t\tChannel %x cs0 = %08x cs1 = %08x cs2 = %08x cs3 = %08x\n",
                   channel, gAddrData->CSBASE[channel][0], gAddrData->CSBASE[channel][1], gAddrData->CSBASE[channel][2],
                   gAddrData->CSBASE[channel][3]);

  // UMC0CHx00000020 [DRAM CS Mask Address] (AddrMask), ch0_dimm[1:0]_aliasSMN; UMC0CHx0000_002[4,0];
  // [31:1]AddrMask: Address Mask [39:9]
  gAddrData->CSMASK[channel][0] = smnRegRead (pkgno, mpuno, umcno, umcchno, 0x20, BusNumberBase) | 0x1;
  gAddrData->CSMASK[channel][1] = smnRegRead (pkgno, mpuno, umcno, umcchno, 0x24, BusNumberBase) | 0x1;
  IDS_HDT_CONSOLE (MAIN_FLOW, "\t\tAddrMask-x20\t\tChannel %x Dimm0 = %08x Dimm1 = %08x\n",
                   channel, gAddrData->CSMASK[channel][0], gAddrData->CSMASK[channel][1]);

  // UMC0CHx00000010 [DRAM CS Base Secondary Address] (BaseAddrSec), ch0_cs[3:0]_aliasSMN; UMC0CHx0000_001[[C,8,4,0]];
  // [31:1]BaseAddr: Base Address [39:9]
  gAddrData->CSBASESEC[channel][0] = ((smnRegRead (pkgno, mpuno, umcno, umcchno, 0x10, BusNumberBase) >> 1) << 1);
  gAddrData->CSBASESEC[channel][1] = ((smnRegRead (pkgno, mpuno, umcno, umcchno, 0x14, BusNumberBase) >> 1) << 1);
  gAddrData->CSBASESEC[channel][2] = ((smnRegRead (pkgno, mpuno, umcno, umcchno, 0x18, BusNumberBase) >> 1) << 1);
  gAddrData->CSBASESEC[channel][3] = ((smnRegRead (pkgno, mpuno, umcno, umcchno, 0x1C, BusNumberBase) >> 1) << 1);
  IDS_HDT_CONSOLE (MAIN_FLOW, "\t\tBaseAddrSec-x10\t\tChannel %x cs0 = %08x cs1 = %08x cs2 = %08x cs3 = %08x\n",
                   channel, gAddrData->CSBASESEC[channel][0], gAddrData->CSBASESEC[channel][1], gAddrData->CSBASESEC[channel][2],
                   gAddrData->CSBASESEC[channel][3]);

  // UMC0CHx00000028 [DRAM CS Mask Secondary Address] (AddrMaskSec), _ch0_dimm[1:0]_aliasSMN; UMC0CHx0000_002[C,8];
  // [31:1]AddrMask: Address Mask [39:9]
  gAddrData->CSMASKSEC[channel][0] = smnRegRead (pkgno, mpuno, umcno, umcchno, 0x28, BusNumberBase) | 0x1;
  gAddrData->CSMASKSEC[channel][1] = smnRegRead (pkgno, mpuno, umcno, umcchno, 0x2C, BusNumberBase) | 0x1;
  IDS_HDT_CONSOLE (MAIN_FLOW, "\t\tAddrMaskSec-x28\t\tChannel %x Dimm0 = %08x Dimm1 = %08x\n",
                   channel, gAddrData->CSMASKSEC[channel][0], gAddrData->CSMASKSEC[channel][1]);

  // UMC0CHx00000080 [DIMM Configuration] (DimmCfg), ch0_dimm[1:0]_aliasSMN; UMC0CHx0000_008[4,0];
  // [11]DDR4eEn
  //
  // UMC0CHx00000200 [DRAM Configuration] (DramConfiguration), umc0_ch0_mp[3:0]_aliasSMN; UMC0CHx0000_0[5:2]00;
  // [8]BankGroupEn. This register is per channel, not per DIMM. Following read from 0x200 twice
  gAddrData->CTRLREG[channel][0] =
    ((((smnRegRead (pkgno, mpuno, umcno, umcchno, 0x80, BusNumberBase)) >> 11) & 0x1) << 13) /*bit13*/ |
    ((((smnRegRead (pkgno, mpuno, umcno, umcchno, 0x200, BusNumberBase)) >> 8) & 0x1) << 5); /*bit5*/
  gAddrData->CTRLREG[channel][1] =
    ((((smnRegRead (pkgno, mpuno, umcno, umcchno, 0x84, BusNumberBase)) >> 11) & 0x1) << 13) /*bit13*/ |
    ((((smnRegRead (pkgno, mpuno, umcno, umcchno, 0x200, BusNumberBase)) >> 8) & 0x1) << 5); /*bit5*/
  IDS_HDT_CONSOLE (MAIN_FLOW, "\t\tDimmCfg-x28[11]-x200[8]\tChannel %x Dimm0 DDR4eEn = %x BankGroupEn = %x, Dimm1 DDR4eEn = %x BankGroupEn = %x\n",
                   channel, ((gAddrData->CTRLREG[channel][0] & BIT13) ? 1 : 0), ((gAddrData->CTRLREG[channel][0] & BIT5) ? 1 : 0),
                   ((gAddrData->CTRLREG[channel][1] & BIT13) ? 1 : 0), ((gAddrData->CTRLREG[channel][1] & BIT5) ? 1 : 0));

  // UMC0CHx00000010 [DRAM CS Base Secondary Address] (BaseAddrSec), ch0_cs[3:0]_aliasSMN; UMC0CHx0000_001[[C,8,4,0]];
  // [0]CSEnable
  //
  // UMC0CHx00000030 [DRAM Address Configuration] (AddrCfg), ch0_dimm[1:0]_aliasSMN; UMC0CHx0000_003[4,0];
  // [21:20]NumBanks
  // [19:16]NumCol
  // [15:12]NumRowHi
  // [11:8]NumRowLo
  // [5:4]NumRM
  // [3:2]NumBankGroups
  //
  // UMC0CHx00000000 [DRAM CS Base Address] (BaseAddr), ch0_cs[3:0]_aliasSMN; UMC0CHx0000_000[[C,8,4,0]];
  // [0]CSEnable
  // DIMM 0
  gAddrData->CONFIGDIMM[channel][0] =
    ((((smnRegRead (pkgno, mpuno, umcno, umcchno, 0x14, BusNumberBase)) >> 0) & 0x1) << 25) |
    ((((smnRegRead (pkgno, mpuno, umcno, umcchno, 0x10, BusNumberBase)) >> 0) & 0x1) << 24) |
    ((((smnRegRead (pkgno, mpuno, umcno, umcchno, 0x30, BusNumberBase)) >> 2) & 0x3) << 20) |
    ((((smnRegRead (pkgno, mpuno, umcno, umcchno, 0x30, BusNumberBase)) >> 16) & 0xf) << 16) |
    ((((smnRegRead (pkgno, mpuno, umcno, umcchno, 0x30, BusNumberBase)) >> 12) & 0xf) << 12) |
    ((((smnRegRead (pkgno, mpuno, umcno, umcchno, 0x30, BusNumberBase)) >> 8) & 0xf) << 8) |
    ((((smnRegRead (pkgno, mpuno, umcno, umcchno, 0x30, BusNumberBase)) >> 4) & 0x3) << 6) |
    ((((smnRegRead (pkgno, mpuno, umcno, umcchno, 0x30, BusNumberBase)) >> 20) & 0x3) << 4) |
    (((smnRegRead (pkgno, mpuno, umcno, umcchno, 0x4, BusNumberBase)) & 0x1) << 1) |
    ((smnRegRead (pkgno, mpuno, umcno, umcchno, 0x0, BusNumberBase)) & 0x1);
  IDS_HDT_CONSOLE (MAIN_FLOW, "\t\tAddrCfg-x30\t\tChannel %x Dimm0 = %08x ([25:24]BaseAddrSec CSEnable, [1:0]BaseAddr CSEnable)\n",
                   channel, gAddrData->CONFIGDIMM[channel][0]);

  // As above
  // DIMM 1
  gAddrData->CONFIGDIMM[channel][1] =
    ((((smnRegRead (pkgno, mpuno, umcno, umcchno, 0x1C, BusNumberBase)) >> 0) & 0x1) << 25) |
    ((((smnRegRead (pkgno, mpuno, umcno, umcchno, 0x18, BusNumberBase)) >> 0) & 0x1) << 24) |
    ((((smnRegRead (pkgno, mpuno, umcno, umcchno, 0x34, BusNumberBase)) >> 2) & 0x3) << 20) |
    ((((smnRegRead (pkgno, mpuno, umcno, umcchno, 0x34, BusNumberBase)) >> 16) & 0xf) << 16) |
    ((((smnRegRead (pkgno, mpuno, umcno, umcchno, 0x34, BusNumberBase)) >> 12) & 0xf) << 12) |
    ((((smnRegRead (pkgno, mpuno, umcno, umcchno, 0x34, BusNumberBase)) >> 8) & 0xf) << 8) |
    ((((smnRegRead (pkgno, mpuno, umcno, umcchno, 0x34, BusNumberBase)) >> 4) & 0x3) << 6) |
    ((((smnRegRead (pkgno, mpuno, umcno, umcchno, 0x34, BusNumberBase)) >> 20) & 0x3) << 4) |
    (((smnRegRead (pkgno, mpuno, umcno, umcchno, 0xc, BusNumberBase)) & 0x1) << 1) |
    ((smnRegRead (pkgno, mpuno, umcno, umcchno, 0x8, BusNumberBase)) & 0x1);
  IDS_HDT_CONSOLE (MAIN_FLOW, "\t\tAddrCfg-x30\t\tChannel %x Dimm1 = %08x ([25:24]BaseAddrSec CSEnable, [1:0]BaseAddr CSEnable)\n",
                   channel, gAddrData->CONFIGDIMM[channel][1]);

  // UMC0CHx00000040 [DRAM Bank Address Select] (AddrSel), ch0_dimm[1:0]_aliasSMN; UMC0CHx0000_004[4,0];
  // [19:16]BankBit4
  // [15:12]BankBit3
  // [11:8]BankBit2
  // [7:4]BankBit1
  // [3:0]BankBit0
  gAddrData->BANKSELDIMM[channel][0] = smnRegRead (pkgno, mpuno, umcno, umcchno, 0x40, BusNumberBase) & 0xfffff;

  // As above
  gAddrData->BANKSELDIMM[channel][1] = smnRegRead (pkgno, mpuno, umcno, umcchno, 0x44, BusNumberBase) & 0xfffff;
  IDS_HDT_CONSOLE (MAIN_FLOW, "\t\tAddrSel-x40\t\tChannel %x BankBit Dimm0 = %08x Dimm1 = %08x\n",
                   channel, gAddrData->BANKSELDIMM[channel][0], gAddrData->BANKSELDIMM[channel][1]);

  // UMC0CHx00000040 [DRAM Bank Address Select] (AddrSel), ch0_dimm[1:0]_aliasSMN; UMC0CHx0000_004[4,0];
  // [31:28]RowHi
  // [27:24]RowLo
  gAddrData->ROWSELDIMM[channel][0] = (((smnRegRead (pkgno, mpuno, umcno, umcchno, 0x40, BusNumberBase) >> 24) & 0xff));
  gAddrData->ROWSELDIMM[channel][1] = (((smnRegRead (pkgno, mpuno, umcno, umcchno, 0x44, BusNumberBase) >> 24) & 0xff));
  IDS_HDT_CONSOLE (MAIN_FLOW, "\t\tAddrSel-x40\t\tChannel %x RowHiLo Dimm0 = %08x Dimm1 = %08x\n",
                   channel, gAddrData->ROWSELDIMM[channel][0], gAddrData->ROWSELDIMM[channel][1]);

  // UMC0CHx00000050 [DRAM Column Address Select Low] (ColSelLo), _ch0_dimm[1:0]_aliasSMN; UMC0CHx0000_005[[8,0]];
  gAddrData->COL0SELDIMM[channel][0] = (smnRegRead (pkgno, mpuno, umcno, umcchno, 0x50, BusNumberBase));
  gAddrData->COL0SELDIMM[channel][1] = (smnRegRead (pkgno, mpuno, umcno, umcchno, 0x58, BusNumberBase));
  IDS_HDT_CONSOLE (MAIN_FLOW, "\t\tColSelLo-x50\t\tChannel %x Dimm0 = %08x Dimm1 = %08x\n",
                   channel, gAddrData->COL0SELDIMM[channel][0], gAddrData->COL0SELDIMM[channel][1]);

  // UMC0CHx00000054 [DRAM Column Address Select High] (ColSelHi), _ch0_dimm[1:0]_aliasSMN; UMC0CHx0000_005[[C,4]];
  gAddrData->COL1SELDIMM[channel][0] = (smnRegRead (pkgno, mpuno, umcno, umcchno, 0x54, BusNumberBase));
  gAddrData->COL1SELDIMM[channel][1] = (smnRegRead (pkgno, mpuno, umcno, umcchno, 0x5C, BusNumberBase));
  IDS_HDT_CONSOLE (MAIN_FLOW, "\t\tColSelHi-x54\t\tChannel %x Dimm0 = %08x Dimm1 = %08x\n",
                   channel, gAddrData->COL1SELDIMM[channel][0], gAddrData->COL1SELDIMM[channel][1]);

  // UMC0CHx00000070 [DRAM Rank Multiply Address Select] (RmSel), _ch0_dimm[1:0]_aliasSMN; UMC0CHx0000_007[4,0];
  gAddrData->RMSELDIMM[channel][0] = (smnRegRead (pkgno, mpuno, umcno, umcchno, 0x70, BusNumberBase));
  gAddrData->RMSELDIMM[channel][1] = (smnRegRead (pkgno, mpuno, umcno, umcchno, 0x74, BusNumberBase));
  IDS_HDT_CONSOLE (MAIN_FLOW, "\t\tRmSel-x70\t\tChannel %x Dimm0 = %08x Dimm1 = %08x\n",
                   channel, gAddrData->RMSELDIMM[channel][0], gAddrData->RMSELDIMM[channel][1]);

  // UMC0CHx00000078 [DRAM Rank Multiply Secondary Address Select] (RmSelSec), _ch0_dimm[1:0]_aliasSMN; UMC0CHx0000_007[C,8];
  gAddrData->RMSELDIMMSEC[channel][0] = (smnRegRead (pkgno, mpuno, umcno, umcchno, 0x78, BusNumberBase));
  gAddrData->RMSELDIMMSEC[channel][1] = (smnRegRead (pkgno, mpuno, umcno, umcchno, 0x7C, BusNumberBase));
  IDS_HDT_CONSOLE (MAIN_FLOW, "\t\tRmSelSec-x78\t\tChannel %x Dimm0 = %08x Dimm1 = %08x\n",
                   channel, gAddrData->RMSELDIMMSEC[channel][0], gAddrData->RMSELDIMMSEC[channel][1]);

  // UMC0CHx000000C8 [Address Hash Bank] (AddrHashBank), _ch0_n[4:0]_aliasSMN; UMC0CHx0000_00[D8,D4,D0,CC,C8];
  // [31:14]RowXor: RowXor[17:0]
  // [13:1]ColXor: ColXor[12:0]
  // [0]XorEnable
  gAddrData->ADDRHASHBANK0[channel] = smnRegRead (pkgno, mpuno, umcno, umcchno, 0xC8, BusNumberBase);
  gAddrData->ADDRHASHBANK1[channel] = smnRegRead (pkgno, mpuno, umcno, umcchno, 0xCC, BusNumberBase);
  gAddrData->ADDRHASHBANK2[channel] = smnRegRead (pkgno, mpuno, umcno, umcchno, 0xD0, BusNumberBase);
  gAddrData->ADDRHASHBANK3[channel] = smnRegRead (pkgno, mpuno, umcno, umcchno, 0xD4, BusNumberBase);
  gAddrData->ADDRHASHBANK4[channel] = smnRegRead (pkgno, mpuno, umcno, umcchno, 0xD8, BusNumberBase);
  IDS_HDT_CONSOLE (MAIN_FLOW, "\t\tAddrHashBank-xC8\tChannel %x n0 = %08x n1 = %08x n2 = %08x n3 = %08x n4 = %08x\n",
                   channel, gAddrData->ADDRHASHBANK0[channel], gAddrData->ADDRHASHBANK1[channel], gAddrData->ADDRHASHBANK2[channel],
                   gAddrData->ADDRHASHBANK3[channel], gAddrData->ADDRHASHBANK4[channel]);

  // UMC0CHx000000E8 [Address Hash CS] (AddrHashCS), _ch0_n[1:0]_aliasSMN; UMC0CHx0000_00E[C,8];
  // [31:1]NormAddrXor: NormAddrXor[39:9]
  // [0]XorEn
  gAddrData->ADDRHASHNORMADDR[channel][0] = smnRegRead (pkgno, mpuno, umcno, umcchno, 0xE8, BusNumberBase);
  gAddrData->ADDRHASHNORMADDR[channel][1] = smnRegRead (pkgno, mpuno, umcno, umcchno, 0xEC, BusNumberBase);
  IDS_HDT_CONSOLE (MAIN_FLOW, "\t\tAddrHashCS-xE8\t\tChannel %x n0 = %08x n1 = %08x\n",
                   channel, gAddrData->ADDRHASHNORMADDR[channel][0], gAddrData->ADDRHASHNORMADDR[channel][1]);

  gAddrData->ADDRHASHRMADDR[channel][0] = smnRegRead (pkgno, mpuno, umcno, umcchno, 0xDC, BusNumberBase);
  gAddrData->ADDRHASHRMADDR[channel][1] = smnRegRead (pkgno, mpuno, umcno, umcchno, 0xE0, BusNumberBase);
  gAddrData->ADDRHASHRMADDR[channel][2] = smnRegRead (pkgno, mpuno, umcno, umcchno, 0xE4, BusNumberBase);
  IDS_HDT_CONSOLE (MAIN_FLOW, "\t\tAddrHashRM-xDC\t\tChannel %x n0 = %08x n1 = %08x n2 = %08x\n",
                   channel, gAddrData->ADDRHASHRMADDR[channel][0], gAddrData->ADDRHASHRMADDR[channel][1], gAddrData->ADDRHASHRMADDR[channel][2]);

}

/*********************************************************************************
 * Name: AmdRasDxeSspInit
 *
 * Description
 *   Entry point of the AMD RAS SSP DXE driver
 *   Perform the configuration init, resource reservation, early post init
 *   and install all the supported protocol
 *
 * Input
 *   ImageHandle : EFI Image Handle for the DXE driver
 *   SystemTable : pointer to the EFI system table
 *
 * Output
 *   EFI_SUCCESS : Module initialized successfully
 *   EFI_ERROR   : Initialization failed (see error for more details)
 *
 *********************************************************************************/
EFI_STATUS
EFIAPI
AmdRasSspDxeInit (
  IN       EFI_HANDLE         ImageHandle,
  IN       EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS          Status = EFI_SUCCESS;
  EFI_HANDLE          Handle = NULL;
  EFI_EVENT           ExitBootServicesEvent;

  DEBUG((EFI_D_ERROR, "[RAS] SSP AGESA RAS DXE driver entry\n"));

  AmdRasPolicyInit();

  CollectDimmMap();

  CollectCpuMap();

  Handle = ImageHandle;
  Status = gBS->InstallProtocolInterface (
                  &Handle,
                  &gAmdRasInitDataProtocolGuid,
                  EFI_NATIVE_INTERFACE,
                  mAmdRasPolicy
                  );
  if (EFI_ERROR (Status)) {
    return (Status);
  }

  //
  // Register the event handling function
  //
  Status = gBS->CreateEventEx (
                  EVT_NOTIFY_SIGNAL,
                  TPL_NOTIFY,
                  NbioErrThresInit,
                  NULL,
                  &gEfiEventReadyToBootGuid,
                  &ExitBootServicesEvent
                  );


  return (Status);
}

VOID
NbioErrThresInit(
  IN EFI_EVENT  Event,
  IN VOID       *Context
)
{
#if 0
  UINT8                 Die;
  UINT8                 DieBusNum;
  UINT16                VendorID;
  UINTN                 PciAddress;
  PARITY_CONTROL_0_REG  ParityControl0;

  //Init reset value
  ParityControl0.Fields.ParityUCPThreshold = 1;
  ParityControl0.Fields.ParityCorrThreshold = 1;

  //Read pcd setting
  if (mAmdRasPolicy->NbioDeferredErrThreshEn) {
    ParityControl0.Fields.ParityUCPThreshold = mAmdRasPolicy->NbioDeferredErrThreshCount;
    DEBUG ((EFI_D_ERROR, "[RAS]NBIO Deferred Error Threshold : %d\n", ParityControl0.Fields.ParityUCPThreshold));
  }
  if (mAmdRasPolicy->NbioCorrectedErrThreshEn) {
    ParityControl0.Fields.ParityCorrThreshold = mAmdRasPolicy->NbioCorrectedErrThreshCount;
    DEBUG ((EFI_D_ERROR, "[RAS]NBIO Corrected Error Threshold : %d\n", ParityControl0.Fields.ParityCorrThreshold));
  }

  //Register Error handler per Die.
  for (Die = 0; Die < MAX_NBIO_SUPPORT; Die++) {
    PciAddress = ((Die + 24) << 15) + 0x000;
    VendorID = PciRead16 (PciAddress);
    if (VendorID != AMD_VENDOR_ID) {
      continue;
    }

    PciAddress = ((Die + 24) << 15) + (DF_CFGADDRESSCNTL_FUNC << 12) + DF_CFGADDRESSCNTL_OFFSET;
    DieBusNum = PciRead8 (PciAddress);

    DEBUG ((EFI_D_ERROR, "[RAS]Bus: 0x%0x, Parity Control 0 : 0x%08x\n", DieBusNum, ParityControl0.Value));
    RasSmnWrite(DieBusNum, RAS_PARITY_CONTROL_0, &ParityControl0.Value);
  }
#endif
}

EFI_STATUS
AmdRasPolicyInit(VOID)
{
  EFI_STATUS          Status = EFI_SUCCESS;

  //
  //  Allocate memory and Initialize for Data block
  //
  Status = gBS->AllocatePool (
                  EfiReservedMemoryType,
                  sizeof (AMD_RAS_POLICY),
                  (VOID **)&mAmdRasPolicy
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }
  ZeroMem (mAmdRasPolicy, sizeof (AMD_RAS_POLICY));

  mAmdRasPolicy->PFEHEnable = PcdGetBool(PcdAmdCcxCfgPFEHEnable);
  mAmdRasPolicy->MceSwSmiData = PcdGet8(PcdMceSwSmiData);
  mAmdRasPolicy->McaErrThreshEn = PcdGetBool(PcdMcaErrThreshEn);

  if (PcdGet16 (PcdMcaErrThreshCount) == 0xFFFF)  {
    //Use default setting
    if (PcdGetBool(PcdAmdCcxCfgPFEHEnable)) {
      PcdSet16(PcdMcaErrThreshCount, 0x0FFE);
    } else {
      PcdSet16(PcdMcaErrThreshCount, 0x0FF5);
    }
  }
  mAmdRasPolicy->McaErrThreshCount = PcdGet16(PcdMcaErrThreshCount);

  mAmdRasPolicy->NbioCorrectedErrThreshEn = PcdGetBool(PcdNbioCorrectedErrThreshEn);
  mAmdRasPolicy->NbioCorrectedErrThreshCount = PcdGet16(PcdNbioCorrectedErrThreshCount);
  mAmdRasPolicy->NbioDeferredErrThreshEn = PcdGetBool(PcdNbioDeferredErrThreshEn);
  mAmdRasPolicy->NbioDeferredErrThreshCount = PcdGet16(PcdNbioDeferredErrThreshCount);

  //FCH software SMI command port
  mAmdRasPolicy->SwSmiCmdPortAddr = MmioRead16((ACPI_MMIO_BASE + PMIO_BASE + FCH_PMIOA_REG6A));

  return Status;
}

EFI_STATUS
CollectDimmMap(VOID)
{
  EFI_STATUS    Status = EFI_SUCCESS;
  AMD_FABRIC_TOPOLOGY_SERVICES2_PROTOCOL *FabricTopology;
  UINTN     NumberOfInstalledProcessors;
  UINTN     NumberOfRootBridgesOnDie;
  UINTN     TotalNumberOfDie;
  UINTN     BusNumberBase;
  UINTN     socketId;
  UINTN     dieId;
  UINTN     channelId;
  UINTN     channelIdInSystem;

  Status = gBS->AllocatePool (
      EfiReservedMemoryType,  // IN EFI_MEMORY_TYPE PoolType
      sizeof (ADDR_DATA),     // IN UINTN Size
      &gAddrData               // OUT VOID **Buffer
      );
  if (EFI_ERROR (Status)) {
    ASSERT_EFI_ERROR (Status);
    return Status;
  }
  ZeroMem (gAddrData, sizeof (ADDR_DATA));

  NumberOfInstalledProcessors = 0;
  TotalNumberOfDie = 0;
  NumberOfRootBridgesOnDie = 0;
  BusNumberBase = 0;

  Status = gBS->LocateProtocol(&gAmdFabricTopologyServices2ProtocolGuid, NULL, (VOID **) &FabricTopology);
  FabricTopology->GetSystemInfo (FabricTopology, &NumberOfInstalledProcessors, NULL, NULL, NULL, NULL);

  for (socketId = 0; socketId < NumberOfInstalledProcessors; socketId++) {
    FabricTopology->GetProcessorInfo (FabricTopology, socketId, &TotalNumberOfDie, NULL);
    for (dieId = 0; dieId < TotalNumberOfDie; dieId++) {
      FabricTopology->GetRootBridgeInfo (FabricTopology, socketId, dieId, NumberOfRootBridgesOnDie, NULL, &BusNumberBase, NULL, NULL, NULL, NULL);
      for (channelId = 0; channelId < UMC_PER_DIE; channelId++) {
        IDS_HDT_CONSOLE (MAIN_FLOW, "\nsocket %x die %x channel %x pci bus = %x\n", socketId, dieId, channelId, BusNumberBase);
        retrieve_regs (socketId, dieId, channelId, 0, BusNumberBase);
        channelIdInSystem = convert_to_addr_trans_index (socketId, dieId, channelId, 0);

        // UMC0CHx00000000 [DRAM CS Base Address] (BaseAddr)
        // - _umc0_ch0_cs[3:0]_aliasSMN; UMC0CHx0000_000[[C,8,4,0]]; UMC0CH=0005_0000h
        // - _umc1_ch0_cs[3:0]_aliasSMN; UMC1CHx0000_000[[C,8,4,0]]; UMC1CH=0015_0000h
        // Figure out how many chip select is enabled in a channel
        gAddrData->TOTAL_NUM_RANKS_PER_UMCCH_ADDR_TRANS[channelIdInSystem] = (((smnRegRead (socketId, dieId, channelId, 0, 0x4, BusNumberBase)) & 0x1)) +
                                                      ((smnRegRead (socketId, dieId, channelId, 0, 0x0, BusNumberBase)) & 0x1) +
                                                      ((smnRegRead (socketId, dieId, channelId, 0, 0x8, BusNumberBase)) & 0x1) +
                                                      ((smnRegRead (socketId, dieId, channelId, 0, 0xC, BusNumberBase)) & 0x1) ;
        //IDS_HDT_CONSOLE (MAIN_FLOW, "\t\tTotal chip select enabled in this channel = %x\n", gAddrData->TOTAL_NUM_RANKS_PER_UMCCH_ADDR_TRANS[channelIdInSystem]);

        // Mark enabled chip select in bit position in RANK_ENABLE_PER_UMCCH_ADDR_TRANS
        gAddrData->RANK_ENABLE_PER_UMCCH_ADDR_TRANS[channelIdInSystem] =  ((((smnRegRead (socketId, dieId, channelId, 0, 0xC, BusNumberBase)) & 0x1)) << 3) |
                                                   ((((smnRegRead (socketId, dieId, channelId, 0, 0x8, BusNumberBase)) & 0x1)) << 2) |
                                                   ((((smnRegRead (socketId, dieId, channelId, 0, 0x4, BusNumberBase)) & 0x1)) << 1) |
                                                   ((smnRegRead (socketId, dieId, channelId, 0, 0x0, BusNumberBase)) & 0x1);
        //IDS_HDT_CONSOLE (MAIN_FLOW, "\t\tChip select enabled in this channel (bit position) = %x\n", gAddrData->RANK_ENABLE_PER_UMCCH_ADDR_TRANS[channelIdInSystem]);
      }
    }
  }

  //Save Memory Address Data pointer to Amd Ras Policy
  mAmdRasPolicy->AddrData = gAddrData;

  return Status;
}

EFI_STATUS
CollectCpuMap(VOID)
{
  AMD_CORE_TOPOLOGY_SERVICES_PROTOCOL           *CoreTopologyServices;
  AMD_CORE_TOPOLOGY_SERVICES_V2_PROTOCOL        *CoreTopology2Services;
  AMD_FABRIC_TOPOLOGY_SERVICES2_PROTOCOL        *FabricTopologyServices;
  APOB_CCD_LOGICAL_TO_PHYSICAL_MAP_TYPE_STRUCT   ApobCcdLogToPhysMap;
  APOB_CCX_LOGICAL_TO_PHYSICAL_MAP_TYPE_STRUCT   ApobCcxLogToPhysMap;
  APOB_TYPE_HEADER                              *ApobEntry;
  CPU_INFO      *RasCpuMap;
  UINT32        ApobInstanceId;
  UINT32        Index;
  UINTN         SocketLoop;
  UINTN         DieLoop;
  UINTN         CcdLoop;
  UINTN         ComplexLoop;
  UINTN         CoreLoop;
  UINTN         ThreadLoop;
  UINTN         NumberOfSockets;
  UINTN         NumberOfSystemDies;
  UINTN         NumberOfDies;
  UINTN         NumberOfCcds;
  UINTN         NumberOfComplexes;
  UINTN         NumberOfCores;
  UINTN         NumberOfThreads;
  UINTN         SystemDieCount;
  EFI_STATUS    Status = EFI_SUCCESS;

  CoreTopologyServices = NULL;
  CoreTopology2Services = NULL;
  NumberOfComplexes = 0;
  NumberOfCores = 0;
  NumberOfThreads = 0;

  Status = gBS->LocateProtocol (&gAmdFabricTopologyServices2ProtocolGuid, NULL, &FabricTopologyServices);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  if (gBS->LocateProtocol (&gAmdCoreTopologyServicesV2ProtocolGuid, NULL, &CoreTopology2Services) != EFI_SUCCESS) {
    Status = gBS->LocateProtocol (&gAmdCoreTopologyServicesProtocolGuid, NULL, &CoreTopologyServices);
    if (EFI_ERROR (Status)) {
      return Status;
    }
  }

  //
  //  Allocate memory and Initialize for Data block
  //
  Status = gBS->AllocatePool (
                  EfiReservedMemoryType,
                  sizeof (CPU_INFO) * RAS_MAX_CORES,
                  (VOID **)&RasCpuMap
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }
  ZeroMem (RasCpuMap, sizeof (CPU_INFO) * RAS_MAX_CORES);

  Status = FabricTopologyServices->GetSystemInfo (FabricTopologyServices, &NumberOfSockets, &NumberOfSystemDies, NULL, NULL, NULL);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  SystemDieCount = 0;
  Index = 0;
  NumberOfCcds = 0;
  for (SocketLoop = 0; SocketLoop < NumberOfSockets; SocketLoop++) {
    Status = FabricTopologyServices->GetProcessorInfo (FabricTopologyServices, SocketLoop, &NumberOfDies, NULL);
    if (EFI_ERROR (Status)) {
      return Status;
    }
    for (DieLoop = 0; DieLoop < NumberOfDies; DieLoop++) {
      SystemDieCount++;
      if (CoreTopology2Services != NULL) {
        Status = CoreTopology2Services->GetCoreTopologyOnDie (CoreTopology2Services, SocketLoop, DieLoop, &NumberOfCcds, &NumberOfComplexes, &NumberOfCores, &NumberOfThreads);
        if (EFI_ERROR (Status)) {
          return Status;
        }
      } else if (CoreTopologyServices != NULL) {
        Status = CoreTopologyServices->GetCoreTopologyOnDie (CoreTopologyServices, SocketLoop, DieLoop, &NumberOfComplexes, &NumberOfCores, &NumberOfThreads);
        if (EFI_ERROR (Status)) {
          return Status;
        }
      }

      ApobInstanceId = ((UINT32) SocketLoop << 8) | (UINT32) DieLoop;
      if (CoreTopology2Services != NULL) {
        Status = AmdPspGetApobEntryInstance (APOB_CCX, APOB_CCD_LOGICAL_TO_PHYSICAL_MAP_TYPE, ApobInstanceId, FALSE, &ApobEntry);
        if (EFI_ERROR (Status)) {
          return Status;
        }
        CopyMem (&ApobCcdLogToPhysMap, ApobEntry, sizeof (APOB_CCD_LOGICAL_TO_PHYSICAL_MAP_TYPE_STRUCT));
      } else {
        Status = AmdPspGetApobEntryInstance (APOB_CCX, APOB_CCX_LOGICAL_TO_PHYSICAL_MAP_TYPE, ApobInstanceId, FALSE, &ApobEntry);
        if (EFI_ERROR (Status)) {
          return Status;
        }
        CopyMem (&ApobCcxLogToPhysMap, ApobEntry, sizeof (APOB_CCX_LOGICAL_TO_PHYSICAL_MAP_TYPE_STRUCT));

        NumberOfCcds = 1;
        ApobCcdLogToPhysMap.CcdMap[0].PhysCcdNumber = 0;
        ApobCcdLogToPhysMap.CcdMap[1].PhysCcdNumber = CCX_NOT_PRESENT;
        for (ComplexLoop = 0; ComplexLoop < CCX_MAX_COMPLEXES_PER_DIE; ComplexLoop++) {
          ApobCcdLogToPhysMap.CcdMap[0].ComplexMap[ComplexLoop].PhysComplexNumber = ApobCcxLogToPhysMap.ComplexMap[ComplexLoop].PhysComplexNumber;
          for (CoreLoop = 0; CoreLoop < CCX_MAX_CORES_PER_COMPLEX; CoreLoop++) {
            ApobCcdLogToPhysMap.CcdMap[0].ComplexMap[ComplexLoop].CoreInfo[CoreLoop].PhysCoreNumber =
              ApobCcxLogToPhysMap.ComplexMap[ComplexLoop].CoreInfo[CoreLoop].PhysCoreNumber;
            for (ThreadLoop = 0; ThreadLoop < CCX_MAX_THREADS_PER_CORE; ThreadLoop++) {
              ApobCcdLogToPhysMap.CcdMap[0].ComplexMap[ComplexLoop].CoreInfo[CoreLoop].IsThreadEnabled[ThreadLoop] =
                ApobCcxLogToPhysMap.ComplexMap[ComplexLoop].CoreInfo[CoreLoop].IsThreadEnabled[ThreadLoop];
            }
          }
        }
      }

      for (CcdLoop = 0; CcdLoop < NumberOfCcds; CcdLoop++) {
        if (ApobCcdLogToPhysMap.CcdMap[CcdLoop].PhysCcdNumber == CCX_NOT_PRESENT) {
          return EFI_NOT_FOUND;
        }
        for (ComplexLoop = 0; ComplexLoop < NumberOfComplexes; ComplexLoop++) {
          if (ApobCcdLogToPhysMap.CcdMap[CcdLoop].ComplexMap[ComplexLoop].PhysComplexNumber == CCX_NOT_PRESENT) {
            return EFI_NOT_FOUND;
          }
          for (CoreLoop = 0; CoreLoop < NumberOfCores; CoreLoop++) {
            if (ApobCcdLogToPhysMap.CcdMap[CcdLoop].ComplexMap[ComplexLoop].CoreInfo[CoreLoop].PhysCoreNumber == CCX_NOT_PRESENT) {
              return EFI_NOT_FOUND;
            }
            if (Index == RAS_MAX_CORES) {
              return EFI_BUFFER_TOO_SMALL;                //Should not be here
            }
            RasCpuMap[Index].ProcessorNumber = Index;    //CPU Logic Number
            RasCpuMap[Index].SocketId = (UINT8)(SocketLoop & 0xFF);
            RasCpuMap[Index].DieId = (CoreTopology2Services != NULL) ? (UINT8)(CcdLoop & 0xFF) : (UINT8)(DieLoop & 0xFF);
            RasCpuMap[Index].CcxId = (UINT8)(ComplexLoop & 0xFF);
            RasCpuMap[Index].CoreId = (UINT8)(CoreLoop & 0xFF);
            RasCpuMap[Index].ThreadID = 0;
            Index++;
            if (NumberOfThreads > 1) {
              if (Index == RAS_MAX_CORES) {
                return EFI_BUFFER_TOO_SMALL;
              }
              RasCpuMap[Index].ProcessorNumber = Index; //CPU Logic Number
              RasCpuMap[Index].SocketId = (UINT8)(SocketLoop & 0xFF);
              RasCpuMap[Index].DieId = (CoreTopology2Services != NULL) ? (UINT8)(CcdLoop & 0xFF) : (UINT8)(DieLoop & 0xFF);
              RasCpuMap[Index].CcxId = (UINT8)(ComplexLoop & 0xFF);
              RasCpuMap[Index].CoreId = (UINT8)(CoreLoop & 0xFF);
              RasCpuMap[Index].ThreadID = 1;
              Index++;
            }
          }
        }
      }
    }
  }

  mAmdRasPolicy->TotalNumberOfProcessors = Index;

  //Update Ras CPU map pointer to AMD RAS Policy buffer.
  mAmdRasPolicy->RasCpuMap = RasCpuMap;

  return (Status);
}


