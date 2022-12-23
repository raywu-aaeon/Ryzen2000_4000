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

/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */
#include <Library/AmdBaseLib.h>
#include <Library/IdsLib.h>
#include <Library/RasZpBaseLib.h>
#include <Library/PciLib.h>
#include <Filecode.h>

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */
#define FILECODE LIBRARY_RASZPBASELIB_RASZPBASELIB_FILECODE


/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U R E S
 *----------------------------------------------------------------------------------------
 */

/// Fabric Indirect Config Access Address 3 Register
typedef union {
  /// Bitfields of Fabric Indirect Config Access Address 3 Register
  struct {
    UINT32 CfgRegInstAccEn:1;          ///< CfgRegInstAccEn
    UINT32 :1;                         ///< Reserved
    UINT32 IndCfgAccRegNum:9;          ///< IndCfgAccRegNum
    UINT32 IndCfgAccFuncNum:3;         ///< IndCfgAccFuncNum
    UINT32 SixtyFourBitRegEn:1;        ///< SixtyFourBitRegEn
    UINT32 :1;                         ///< Reserved
    UINT32 CfgRegInstID:8;             ///< CfgRegInstID
    UINT32 :8;                         ///< Reserved
  } Field;
  UINT32  Value;
} FABRIC_IND_CFG_ACCESS_ADDR_REGISTER;

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *                          E X P O R T E D    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------*/
/**
 *
 *
 *
 */
UINT64 
pow_ras (
  UINTN   input,
  UINTN   exp
  )
{
  UINT64  value;
  UINTN   i;

  value = 1;

  if (0 == exp) {
  } else {
    for (i = 0; i < exp; i++) {
      value *= input;
    }
  }
  return value;
}

/*------------------------------------------------------------------
 Function: getBits64
 Purpose: A helper function to get abit range from a uint64
 Inputs:
   low bit number
   high bit number
   the data
 Outputs:
   the requested bits, right justified
 *------------------------------------------------------------------*/
UINT64
getBits64 (
  UINT32 lowBit,
  UINT32 highBit,
  UINT64 data
  )
{
  UINT64    mask;
  mask = (((UINT64) 1) << (highBit - lowBit + ((UINT64) 1))) - ((UINT64) 1);
  return (UINT32) ((data >> lowBit) & mask);
}

/*------------------------------------------------------------------
 Function: getBits
 Purpose: A helper function to get abit range from a uint32
 Inputs:
   low bit number
   high bit number
   the data
 Outputs:
   the requested bits, right justified
 *------------------------------------------------------------------*/
UINT32
getBits (
  UINT32 lowBit,
  UINT32 highBit,
  UINT32 data
  )
{
  UINT32 mask;
  mask = (1 << (highBit - lowBit + 1)) - 1;
  return ((data >> lowBit) & mask);
}

/*------------------------------------------------------------------
 Function: getBit
 Purpose: A helper function to get a specific bit from a uint32
 Inputs:
   bit number
   the data
 Outputs:
   the requested bit, right justified
 *------------------------------------------------------------------*/
UINT32
getBit (
  UINT32 bit,
  UINT32 data
  )
{
  return ((data >> bit) & 0x1);
}

/*------------------------------------------------------------------
 Function: getDfReg
 Purpose: Get a DF register
 Inputs: An instanceID (-1 for a broadcast read),
   a nodeID (for the PCIe bus/device),
   and a register address (function in bits 12:10)
 Outputs: The requested register
 *------------------------------------------------------------------*/
UINT32 
getDfReg (
  UINT32 instanceId,
  UINT32 nodeId,
  UINT32 regAddr
  )
{
  UINT32                               RegisterValue;
  PCI_ADDR                             PciAddr;
  FABRIC_IND_CFG_ACCESS_ADDR_REGISTER  FICAA3;

  PciAddr.AddressValue = 0;
  PciAddr.Address.Device = nodeId + 0x18;   // 0x18 = PCIE device number of socket 0 die 0

  FICAA3.Value = 0;   // Variable initiate
  if ((instanceId & 0xFF) != FABRIC_REG_ACC_BC) {
    FICAA3.Field.CfgRegInstAccEn = 1;
  }

  PciAddr.Address.Function = FICAA3_FUNC;
  PciAddr.Address.Register = FICAA3_REG;
  FICAA3.Field.IndCfgAccRegNum = ((UINT32) (regAddr & 0x3ff)) >> 2;
  FICAA3.Field.IndCfgAccFuncNum = ((UINT32) (regAddr >> 10 )) & 7;
  FICAA3.Field.CfgRegInstID = (UINT32) instanceId;
  PciWrite32 (PciAddr.AddressValue, FICAA3.Value);

  PciAddr.Address.Function = FICAD3_LO_FUNC;
  PciAddr.Address.Register = FICAD3_LO_REG;
  RegisterValue = PciRead32 (PciAddr.AddressValue);
  return RegisterValue;
}

/*------------------------------------------------------------------
 Function: getDfRegSystemFabricIdMask
 Purpose: Get the DF::SystemFabricIdMask register
 Inputs: An instanceID (CS) and a nodeID (for the PCIe bus/device)
 Outputs: The requested register
 *------------------------------------------------------------------*/
UINT32
getDfRegSystemFabricIdMask (
  UINT32 nodeId
  )
{
  return (getDfReg (BCAST, nodeId, DF_SYSFABIDMASK_ADDR));
}

/*------------------------------------------------------------------
 Function: getDfRegFabricBlkInstanceCnt
 Purpose: Get the DF::FabricBlockInstanceCount register
 Inputs: An instanceID (CS) and a nodeID (for the PCIe bus/device)
 Outputs: The requested register
 *------------------------------------------------------------------*/
UINT32 
getDfRegFabricBlkInstanceCnt (
  UINT32  nodeId
  )
{
  return (getDfReg (BCAST, nodeId, DF_FABBLKINSTCNT_ADDR));
}

/*------------------------------------------------------------------
 Function: getDfRegFabricBlkInstInfo3
 Purpose: Get the DF::FabricBlockInstanceInformation3 register
 Inputs: An instanceID (CS) and a nodeID (for the PCIe bus/device)
 Outputs: The requested register
 *------------------------------------------------------------------*/
UINT32
getDfRegFabricBlkInstInfo3 (
  UINT32 instanceId,
  UINT32 nodeId
  )
{
  return (getDfReg (instanceId, nodeId, DF_FABBLKINFO3_ADDR));
}

/*------------------------------------------------------------------
 Function: getDfRegDramOffset
 Purpose: Get the DF::DramOffset[n] register
 Inputs: An instanceID (CS), a nodeID (for the PCIe bus/device)
   and a register number (1 or 2)
 Outputs: The requested register
 *------------------------------------------------------------------*/
UINT32
getDfRegDramOffset (
  UINT32 instanceId,
  UINT32 nodeId,
  UINT32 regNum
  )
{
  return (getDfReg (instanceId, nodeId, DF_DRAMOFFSET0_ADDR + (4*regNum)));
}

/*------------------------------------------------------------------
 Function: getDfRegDramBase
 Purpose: Get the DF::DramBaseAddress register
 Inputs: An instanceID (CS), a nodeID (for the PCIe bus/device)
   and a register number (0 through 15)
 Outputs: The requested register
 *------------------------------------------------------------------*/
UINT32
getDfRegDramBase (
  UINT32 instanceId,
  UINT32 nodeId,
  UINT32 regNum
  )
{
  return (getDfReg (instanceId, nodeId, DF_DRAMBASE0_ADDR + (8*regNum)));
}

/*------------------------------------------------------------------
 Function: getDfRegDramLimit
 Purpose: Get the DF::DramLimitAddress register
 Inputs: An instanceID (CS), a nodeID (for the PCIe bus/device)
   and a register number (0 through 15)
 Outputs: The requested register
 *------------------------------------------------------------------*/
UINT32
getDfRegDramLimit (
  UINT32 instanceId,
  UINT32 nodeId,
  UINT32 regNum
  )
{
  return (getDfReg (instanceId, nodeId, DF_DRAMLIMIT0_ADDR + (8*regNum)));
}

/*------------------------------------------------------------------
 Function: getDfRegDramHoleCtrl
 Purpose: Get the DF::DramHoleControl register
 Inputs: An instanceID (CS) and a nodeID (for the PCIe bus/device)
 Outputs: The requested register
 *------------------------------------------------------------------*/
UINT32
getDfRegDramHoleCtrl (
  UINT32 instanceId,
  UINT32 nodeId
  )
{
  return (getDfReg (instanceId, nodeId, DF_DRAMHOLECTRL_ADDR));
}

/*----------------------------------------------------------------------------------------*/
/**
 * Convert socket/die/UMC number to the Nth UMC in the system (the same as Nth channel in the system,
 * since one channel per UMC on ZP)
 * The input parameter umc_chan_num is fixed to 0 on ZP
 *
 * @param[in] pkg_no            Socket ID (0..1)
 * @param[in] mpu_no            Die ID (0..3)
 * @param[in] umc_inst_num      UMC ID (0..1)
 * @param[in] umc_chan_num      always = 0 in ZP
 * @retval                      Nth channel in the system
 *----------------------------------------------------------------------------------------*/
UINTN
convert_to_addr_trans_index (
  UINTN  pkg_no,
  UINTN  mpu_no,
  UINTN  umc_inst_num,
  UINTN  umc_chan_num
  )
{
  UINTN    U_CH;
  UINTN    M_U_CH;

  U_CH = ((CHANNEL_PER_UMC * umc_inst_num) + umc_chan_num);
  M_U_CH = ((CHANNEL_PER_UMC * UMC_PER_DIE) * mpu_no) + U_CH;
  
  return (((CHANNEL_PER_UMC * UMC_PER_DIE * DIE_PER_SOCKET) * pkg_no) + M_U_CH);
}

BOOLEAN
internal_bit_wise_xor (
  UINT32  inp
  )
{
  BOOLEAN   t;
  UINT32    i;

  t = 0;
  for (i = 0; i < 32; i++) {
    t = t ^ ((inp >> i) & 0x1);
  }
  
  return t;
}

UINT32 
smnRegRead (
  UINTN   socket,
  UINTN   die,
  UINTN   umc,
  UINTN   ch,
  UINTN   offset,
  UINTN   BusNumberBase
  )
{
  UINTN   pciAddress;
  UINT32  smnIndex;
  UINT32  value;

  pciAddress = (BusNumberBase << 20) + NB_SMN_INDEX_2;
  smnIndex = ((UINT32) umc ? 0x100000 : 0) + 0x50000 + (UINT32) offset;
  PciWrite32 (pciAddress, smnIndex);
  pciAddress = (BusNumberBase << 20) + NB_SMN_DATA_2;
  value = PciRead32 (pciAddress);
  return value;
}

/*----------------------------------------------------------------------------------------*/
/**
 *  
 *----------------------------------------------------------------------------------------*/
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
  )
{
  if(SEC==3) {
    //IDS_HDT_CONSOLE (MAIN_FLOW, "ERROR: SEC value cannot be 3\n");
    ASSERT (FALSE);
  }
     
  //if addrhash is enabled, we can get bank after gettting row and col
  //if(((addrhashbank0 & 0x1) == 0) && ((addrhashbank1 & 0x1) == 0) && ((addrhashbank2 & 0x1) == 0) &&
  //    ((addrhashbank3 & 0x1) == 0) && ((addrhashbank4 & 0x1) == 0)) {
  //  if (numbankbits == 3) {
  //    *Bank = ((ChannelAddr >> (bank0 + 5)) & 1) | (((ChannelAddr >> (bank1 + 5)) & 1) << 1) |
  //      (((ChannelAddr >> (bank2 + 5)) & 1) << 2);
  //  } else if (numbankbits == 4) {
  //    *Bank = ((ChannelAddr >> (bank0 + 5)) & 1) | (((ChannelAddr >> (bank1 + 5)) & 1) << 1) |
  //      (((ChannelAddr >> (bank2 + 5)) & 1) << 2) | (((ChannelAddr >> (bank3 + 5)) & 1) << 3);
  //  } else {
  //    *Bank = ((ChannelAddr >> (bank0 + 5)) & 1) | (((ChannelAddr >> (bank1 + 5)) & 1) << 1) |
  //      (((ChannelAddr >> (bank2 + 5)) & 1) << 2) | (((ChannelAddr >> (bank3 + 5)) & 1) << 3) |
  //      (((ChannelAddr >> (bank4 + 5)) & 1) << 4);
  //  }
  //}   // if addr hash is disabled
  if (numbankbits == 3) {
    *Bank = ((ChannelAddr >> (bank0 + 5)) & 1) | (((ChannelAddr >> (bank1 + 5)) & 1) << 1) |
      (((ChannelAddr >> (bank2 + 5)) & 1) << 2);

  } else if (numbankbits == 4) {
    *Bank = ((ChannelAddr >> (bank0 + 5)) & 1) | (((ChannelAddr >> (bank1 + 5)) & 1) << 1) |
      (((ChannelAddr >> (bank2 + 5)) & 1) << 2) | (((ChannelAddr >> (bank3 + 5)) & 1) << 3);

  } else {
    *Bank = ((ChannelAddr >> (bank0 + 5)) & 1) | (((ChannelAddr >> (bank1 + 5)) & 1) << 1) |
      (((ChannelAddr >> (bank2 + 5)) & 1) << 2) | (((ChannelAddr >> (bank3 + 5)) & 1) << 3) |
      (((ChannelAddr >> (bank4 + 5)) & 1) << 4);
  }

  *Col = ((ChannelAddr >> (((COL0REG >> 0) & 0xf) + 2)) & 0x1) |
    (((ChannelAddr >> (((COL0REG >> 4) & 0xf) + 2)) & 0x1) << 1) |
    (((ChannelAddr >> (((COL0REG >> 8) & 0xf) + 2)) & 0x1) << 2) |
    (((ChannelAddr >> (((COL0REG >> 12) & 0xf) + 2)) & 0x1) << 3) |
    (((ChannelAddr >> (((COL0REG >> 16) & 0xf) + 2)) & 0x1) << 4);

  if(numcolbits >= 6) {
    *Col |= (((ChannelAddr >> (((COL0REG >> 20) & 0xf) + 2)) & 0x1) << 5);
  }
  if(numcolbits >= 7) {
    *Col |= (((ChannelAddr >> (((COL0REG >> 24) & 0xf) + 2)) & 0x1) << 6);
  }
  if(numcolbits >= 8) {
    *Col |= (((ChannelAddr >> (((COL0REG >> 28) & 0xf) + 2)) & 0x1) << 7);
  }
  if(numcolbits >= 9) {
    *Col |= (((ChannelAddr >> (((COL1REG >> 0) & 0xf) + 8)) & 0x1) << 8);
  }
  if(numcolbits >= 10) {
    *Col |= (((ChannelAddr >> (((COL1REG >> 4) & 0xf) + 8)) & 0x1) << 9);
  }
  if(numcolbits >= 11) {
    *Col |= (((ChannelAddr >> (((COL1REG >> 8) & 0xf) + 8)) & 0x1) << 10);
  }
  if(numcolbits >= 12) {
    *Col |= (((ChannelAddr >> (((COL1REG >> 12) & 0xf) + 8)) & 0x1) << 11);
  }
  if(numcolbits >= 13) {
    *Col |= (((ChannelAddr >> (((COL1REG >> 16) & 0xf) + 8)) & 0x1) << 12);
  }
  if(numcolbits >= 14) {
    *Col |= (((ChannelAddr >> (((COL1REG >> 20) & 0xf) + 8)) & 0x1) << 13);
  }
  if(numcolbits >= 15) {
    *Col |= (((ChannelAddr >> (((COL1REG >> 24) & 0xf) + 8)) & 0x1) << 14);
  }
  if(numcolbits >= 16) {
    *Col |= (((ChannelAddr >> (((COL1REG >> 28) & 0xf) + 8)) & 0x1) << 15);
  }

  *Row = (UINT32) (((ChannelAddr >> (row_lo0 + 12)) & (pow_ras (2, numrowlobits) - 1)) |
                   (((ChannelAddr >> (row_hi0 + 24)) & (pow_ras (2, numrowhibits) - 1)) << numrowlobits));

  //We will need to adjust row taking into account the InvertMSBsE/O for that Pr/Sec rank
  //Row =  Row[Msb] ^ InvertMsbE/O of Pri/SEC[1]<<Msb| Row[Msb-1] ^ InvertMsbE/O of Pri/SEC[0]<<Msb-1| Row & (2^(total number of row bits-2)-1)

  if(numrowhibits == 0) {
    *Row = ((((*Row >> (numrowlobits - 1)) & 1) ^ ((cs % 2) ? (SEC ? ((invertmsbsosec >> 1) & 1) : ((invertmsbso >> 1) & 1)) :
                                                   (SEC ? ((invertmsbsesec >> 1) & 1) : ((invertmsbse >> 1) & 1)))) << (numrowlobits - 1)) |
      ((((*Row >> (numrowlobits - 2)) & 1) ^ ((cs % 2) ? (SEC ? ((invertmsbsosec >> 0) & 1) : ((invertmsbso >> 0) & 1)) :
                                              (SEC? ((invertmsbsesec >> 0) & 1) : ((invertmsbse >> 0) & 1)))) << (numrowlobits - 2)) |
      (*Row & ((pow_ras (2, numrowlobits - 2)) - 1));
  } else {

    *Row = ((((*Row >> (numrowlobits + numrowhibits - 1)) & 1 ) ^ ((cs % 2) ? (SEC ? ((invertmsbsosec >> 1) & 1) : ((invertmsbso >> 1) & 1)) :
                                                                   (SEC ? ((invertmsbsesec >> 1) & 1) : ((invertmsbse >> 1) & 1)))) << (numrowlobits + numrowhibits - 1)) |
      ((((*Row >> (numrowlobits + numrowhibits - 2)) & 1 ) ^ ((cs % 2) ? (SEC ? ((invertmsbsosec >> 0) & 1) : ((invertmsbso >> 0) & 1)) :
                                                              (SEC ? ((invertmsbsesec >> 0) & 1) : ((invertmsbse >> 0) & 1)))) << (numrowlobits + numrowhibits - 2)) |
      (*Row & ((pow_ras (2, numrowlobits + numrowhibits - 2)) - 1));
  }

  if ((addrhashbank0 & 0x1) || (addrhashbank1 & 0x1) || (addrhashbank2 & 0x1) || (addrhashbank3 & 0x1) || (addrhashbank4 & 0x1)) {
    //if (numbankbits == 3) {
    //  *Bank = (ChannelAddr >> (bank0 + 5) & 1) | ((ChannelAddr >> (bank1 + 5) & 1) << 1) | ((ChannelAddr >> (bank2 + 5) & 1) << 2);
    //
    //} else if (numbankbits == 4) {
    //  *Bank = (ChannelAddr >> (bank0 + 5) & 1) | ((ChannelAddr >> (bank1 + 5) & 1) << 1) |
    //    ((ChannelAddr >> (bank2 + 5) & 1) << 2) | ((ChannelAddr >> (bank3 + 5) & 1) << 3);
    //} else {
    //  *Bank = (ChannelAddr >> (bank0 + 5) & 1) | ((ChannelAddr >> (bank1 + 5) & 1) << 1) |
    //    ((ChannelAddr >> (bank2 + 5) & 1) << 2) | ((ChannelAddr >> (bank3 + 5) & 1) << 3) |
    //    ((ChannelAddr >> (bank4 + 5) & 1) << 4);
    //}

    gAddrData->addrhash[0] = ((internal_bit_wise_xor(*Col & ((addrhashbank0 >> 1) & 0x1fff))) 
                  ^ (internal_bit_wise_xor(*Row & ((addrhashbank0 >> 14) & 0x3ffff)))) & (addrhashbank0 & 1);

    gAddrData->addrhash[1] = ((internal_bit_wise_xor(*Col & ((addrhashbank1 >> 1) & 0x1fff))) 
                  ^ (internal_bit_wise_xor(*Row & ((addrhashbank1 >> 14) & 0x3ffff)))) & (addrhashbank1 & 1);

    gAddrData->addrhash[2] = ((internal_bit_wise_xor(*Col & ((addrhashbank2 >> 1) & 0x1fff))) 
                  ^ (internal_bit_wise_xor(*Row & ((addrhashbank2 >> 14) & 0x3ffff)))) & (addrhashbank2 & 1);

    gAddrData->addrhash[3] = ((internal_bit_wise_xor(*Col & ((addrhashbank3 >> 1) & 0x1fff))) 
                  ^ (internal_bit_wise_xor(*Row & ((addrhashbank3 >> 14) & 0x3ffff)))) & (addrhashbank3 & 1);

    gAddrData->addrhash[4] = ((internal_bit_wise_xor(*Col & ((addrhashbank4 >> 1) & 0x1fff))) 
                  ^ (internal_bit_wise_xor(*Row & ((addrhashbank4 >> 14) & 0x3ffff)))) & (addrhashbank4 & 1);
  

    if (numbankbits == 3) {
      *Bank = (((addrhashbank0 & 0x1) == 1) ? (gAddrData->addrhash[0] ^ (*Bank & 1)) : (*Bank & 1)) |
        ((((addrhashbank1 & 1) == 1) ? (gAddrData->addrhash[1] ^ ((*Bank >> 1) & 1)) : ((*Bank >> 1) & 1)) << 1) |
        ((((addrhashbank2 & 1) == 1) ? (gAddrData->addrhash[2] ^ ((*Bank >> 2) & 1)) : ((*Bank >> 2) & 1)) << 2);

    } else if (numbankbits == 4) {
      *Bank = (((addrhashbank0 & 1) == 1) ? (gAddrData->addrhash[0] ^ (*Bank & 1)) : (*Bank & 1)) |
        ((((addrhashbank1 & 1) == 1) ? (gAddrData->addrhash[1] ^ ((*Bank >> 1) & 1)) : ((*Bank >> 1) & 1)) << 1) |
        ((((addrhashbank2 & 1) == 1) ? (gAddrData->addrhash[2] ^ ((*Bank >> 2) & 1)) : ((*Bank >> 2) & 1)) << 2) |
        ((((addrhashbank3 & 1) == 1) ? (gAddrData->addrhash[3] ^ ((*Bank >> 3) & 1)) : ((*Bank >> 3) & 1)) << 3);

    } else {
      *Bank = (((addrhashbank0 & 1) == 1) ? (gAddrData->addrhash[0] ^ (*Bank & 1)) : (*Bank & 1)) |
        ((((addrhashbank1 & 1) == 1) ? (gAddrData->addrhash[1] ^ ((*Bank >> 1) & 1)) : ((*Bank >> 1) & 1)) << 1) |
        ((((addrhashbank2 & 1) == 1) ? (gAddrData->addrhash[2] ^ ((*Bank >> 2) & 1)) : ((*Bank >> 2) & 1)) << 2) |
        ((((addrhashbank3 & 1) == 1) ? (gAddrData->addrhash[3] ^ ((*Bank >> 3) & 1)) : ((*Bank >> 3) & 1)) << 3) |
        ((((addrhashbank4 & 1) == 1) ? (gAddrData->addrhash[4] ^ ((*Bank >> 4) & 1)) : ((*Bank >> 4) & 1)) << 4);
    }
  }

  if(!SEC) {
    if (numcsbits == 0) {
      *Rankmul = 0;

    } else if (numcsbits == 1) {
      *Rankmul = (ChannelAddr >> (rm0 + 12)) & 1;

    } else if (numcsbits == 2) {
      *Rankmul = ((ChannelAddr >> (rm0 + 12)) & 1) | (((ChannelAddr >> (rm1 + 12)) & 1) << 1);

    } else {
      *Rankmul = ((ChannelAddr >> (rm0 + 12)) & 1) | (((ChannelAddr >> (rm1 + 12)) & 1) << 1) | (((ChannelAddr >> (rm2 + 12)) & 1) << 2);
    }
  } else {
    if (numcsbits == 0) {
      *Rankmul = 0;

    } else if (numcsbits == 1) {
      *Rankmul = (ChannelAddr>> (rm0sec + 12)) & 1;

    } else if (numcsbits == 2) {
      *Rankmul = ((ChannelAddr >> (rm0sec + 12)) & 1) | (((ChannelAddr >> (rm1sec + 12)) & 1) << 1);

    } else {
      *Rankmul = ((ChannelAddr >> (rm0sec + 12)) & 1) | (((ChannelAddr >> (rm1sec + 12)) & 1) << 1) | (((ChannelAddr >> (rm2sec + 12)) & 1) << 2);
    }
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * Convert normalized address to chip select, row, column, bank, rankmul
 * 
 * ChannelAddr expected to be passed from the caller should be till lsb=0 and only msb=39 is considered
 * no fancy 39:4 version
 * pkg_no: socket number
 * mpu_no: die number 
 *
 *----------------------------------------------------------------------------------------*/
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
  )
{
  //Need to check the validity of the NA vs dct number vs node number
  UINT32  CSBase=0, CSMask=0,CSBasesec=0, CSMasksec=0;
  UINT8   Bank=0,Rankmul=0;
  UINT32  Row=0;
  UINT16  Col=0;
  UINT8   SEC = 0;

  UINT64  temp=0; 
  UINT8   cs=0 ;

  BOOLEAN CSEn=0,CSEnsec=0;
  UINT8   Chipselect=0;
  UINT8   noofbank=0, noofrm=0, noofrowlo=0, noofrowhi=0, noofcol=0, noofbg=0, bank0=0, bank1=0, bank2=0,bank3=0,bank4=0;
  UINT8   numrowlobits=0, numrowhibits=0, numcolbits=0, numcsbits=0,  numbankbits=0,numbgbits=0;
  UINT8   row_lo0=0, row_hi0=0, rm0=0, rm1=0,rm2=0, chan=0, invertmsbse=0, invertmsbso=0;
  UINT8   rm0sec=0, rm1sec=0,rm2sec=0, chansec=0, invertmsbsesec=0, invertmsbsosec=0  ;
  UINT32  COL0REG=0, COL1REG=0;
  UINT32  addrhashbank0=0,addrhashbank1=0,addrhashbank2=0,addrhashbank3=0,addrhashbank4=0;
  UINT32  addrhashbankpc=0,addrhashbankpc2=0, addrhashnormaddr0=0, addrhashnormaddr1=0;
  UINT8   bankgroupen=0, vcm_en =0;
  UINTN   channelId;
  UINT32  InputAddr;

  // channelId: channel ID of system
  umc_chan_num = 0;   // umc_chan_num = 0 in ZP
  channelId = convert_to_addr_trans_index(pkg_no, mpu_no, umc_inst_num, umc_chan_num);
  
  //get_highest_possible_addr_bit(pkg_no, mpu_no, umc_inst_num, umc_chan_num);
         
  //read out the addrhash* registers here
  addrhashbank0 = gAddrData->ADDRHASHBANK0 [channelId];
  addrhashbank1 = gAddrData->ADDRHASHBANK1 [channelId];
  addrhashbank2 = gAddrData->ADDRHASHBANK2 [channelId];
  addrhashbank3 = gAddrData->ADDRHASHBANK3 [channelId];
  addrhashbank4 = gAddrData->ADDRHASHBANK4 [channelId];
  addrhashbankpc = gAddrData->ADDRHASHBANKPC[channelId];   //nhu, useless, 01/31
  addrhashbankpc2 = gAddrData->ADDRHASHBANKPC2[channelId]; //nhu, useless, 01/31
  addrhashnormaddr0 = gAddrData->ADDRHASHNORMADDR[channelId][0];
  addrhashnormaddr1 = gAddrData->ADDRHASHNORMADDR[channelId][1];

  for (cs = 0; cs < 4; ++cs) {    // nhu CSBASESEC[][y], retrieve_regs just save register data to [3:0], need to change to cs < 4
    CSBase = gAddrData->CSBASE[channelId][cs]; 
    CSMask = gAddrData->CSMASK[channelId][cs >> 1];

    //Secondary decoder stuff for each primary
    CSBasesec = gAddrData->CSBASESEC[channelId][cs];
    CSMasksec = gAddrData->CSMASKSEC[channelId][cs >> 1]; 

    // UMC0CHx00000000 [DRAM CS Base Address][31:1]: Base Address[39:9], shift error address right 8 bit to match BaseAddr
    InputAddr = (ChannelAddr >> 8) & 0xffffffff;

	//Read out *RAMCFG*
    temp = gAddrData->CONFIGDIMM[channelId][cs >> 1];
    CSEn = (temp >> (cs & 0x1)) & 1;

    //Secodnary decoder stuff
    //[25:24]  of CONFIGDIMM is the cssec [1:0]
    CSEnsec = (cs & 0x1) ? ((temp >> 25) & 0x1) : ((temp >> 24) & 0x1);

    if ((CSEn && ((InputAddr & ~CSMask) == (CSBase & ~CSMask))) ||
        (CSEnsec && ((InputAddr & ~CSMasksec) == (CSBasesec & ~CSMasksec)))) {

      // Hashing
      // Dealing with cshash..
      Chipselect = 0 ;
      if (gAddrData->ADDRHASHNORMADDR[channelId][0] & 0x1) {
        Chipselect = ((internal_bit_wise_xor ((gAddrData->ADDRHASHNORMADDR[channelId][0] >> 1) & (ChannelAddr >> 9))) ^ (cs & 0x1));
      } else {
        Chipselect = (cs & 0x1);
      }

      if (gAddrData->ADDRHASHNORMADDR[channelId][1] & 0x1) {
        Chipselect |= (((internal_bit_wise_xor((gAddrData->ADDRHASHNORMADDR[channelId][1] >> 1) & (ChannelAddr>>9))) ^ ((cs >> 1) & 0x1)) << 1);
      } else {
        Chipselect |= ((cs >> 1) & 0x1) << 1;
      }
      // Hashing end

      SEC = (CSEn && ((InputAddr & ~CSMask) == (CSBase & ~CSMask))) ? 0 : 
        (CSEnsec && ((InputAddr & ~CSMasksec) == (CSBasesec & ~CSMasksec))) ? 1 : 3;
      InputAddr = 0;

      noofbank = (temp >> 4) & 0x3;
      noofrm  = (temp >> 6) & 0x3;
      noofrowlo = (temp >> 8) & 0xf; 
      noofrowhi = (temp >> 12) & 0xf; 
      noofcol = (temp >> 16) & 0xf;
      noofbg = (temp >> 20) & 0x3;

	  // Read out *BANK_SEL*
      temp = gAddrData->BANKSELDIMM[channelId][cs >> 1]; 
	  bank0 = temp & 0xf;
	  bank1 = (temp >> 4) & 0xf;
	  bank2 = (temp >> 8) & 0xf;
	  bank3 = (temp >> 12) & 0xf;
	  bank4 = (temp >> 16) & 0xf;

      break;
    }   //csen inputaddr loop
  }   //cs loop
  
  IDS_HDT_CONSOLE (MAIN_FLOW, "noofbank = %d, noofrm = %d, noofrwolo = %d, noofrowhi = %d, noofcol = %d, noofbg = %d\n",
                   noofbank, noofrm, noofrowlo, noofrowhi, noofcol, noofbg);

  if (((gAddrData->RANK_ENABLE_PER_UMCCH_ADDR_TRANS[channelId] >> cs) & 0x1) == 0) {
    IDS_HDT_CONSOLE (MAIN_FLOW, "ERROR: Rank is out of bounds\n");
  }

	//Read out *ROW_SEL*
  temp = gAddrData->ROWSELDIMM[channelId][cs >> 1];
  row_lo0 = (temp >> 0) & 0xf;
  row_hi0 = (temp >> 4) & 0xf;

  //Read out *COL0_SEL*
  COL0REG = gAddrData->COL0SELDIMM[channelId][cs >> 1];

  //Read out *COL1_SEL*
  COL1REG = gAddrData->COL1SELDIMM[channelId][cs >> 1];

  //Read out *RM_SEL*
  temp = gAddrData->RMSELDIMM[channelId][cs >> 1];
  rm0 = (temp >> 0) & 0xf; 
  rm1 = (temp >> 4) & 0xf; 
  rm2 = (temp >> 8) & 0xf;
  //[15:12] reserved in ZP.chan = (temp >> 12) & 0xf;
  invertmsbse = (temp >> 16) & 0x3;
  invertmsbso = (temp >> 18) & 0x3;

  temp = gAddrData->RMSELDIMMSEC[channelId][cs >> 1];
  rm0sec = (temp >> 0) & 0xf; 
  rm1sec = (temp >> 4) & 0xf; 
  rm2sec = (temp >> 8) & 0xf;
  //chansec = (temp>> 12) & 0xf;
  invertmsbsesec = (temp >> 16) & 0x3;
  invertmsbsosec = (temp >> 18) & 0x3;

  numrowlobits = noofrowlo + 10;
  numrowhibits = noofrowhi;
  numcolbits = noofcol + 5;
  numcsbits = noofrm; 
  numbankbits = (noofbank == 2) ? 5 : (noofbank == 1) ? 4 : 3;    // UMC0CHx00000030 [DRAM Address Configuration][21:20]
  //nhu numbgbits = (UINT32) pow_ras (2, noofbg);
  numbgbits = noofbg;

  //Let us see if we need to swizzle or not
  temp = gAddrData->CTRLREG[channelId][cs >> 1]; 
  vcm_en = (temp >> 13) & 0x1;    //nhu vcm_en = DDR4eEn?
  bankgroupen = (temp >> 5) & 0x1;
  IDS_HDT_CONSOLE (MAIN_FLOW, "RowLoBits = %d, RowHiBits = %d, ColBits = %d, CsBits = %d, BankBits = %d, BangGpBits = %d\n",
                   numrowlobits, numrowhibits, numcolbits, numcsbits, numbankbits, numbgbits);

  NormalizedToBankAddrMap(ChannelAddr, CSMask, &Bank, &Row, &Col, &Rankmul, numbankbits, bank4, bank3, bank2, bank1, bank0, 
      numrowlobits, numrowhibits, numcolbits, row_lo0, row_hi0, COL0REG, COL1REG, numcsbits, rm0, rm1, rm2, chan,  vcm_en, 
      numbgbits, bankgroupen, invertmsbse, invertmsbso, rm0sec, rm1sec, rm2sec, chansec, invertmsbsesec, invertmsbsosec, 
      CSMasksec, SEC, cs, addrhashbank0,addrhashbank1,addrhashbank2,addrhashbank3,addrhashbank4,addrhashbankpc,addrhashbankpc2, 
      addrhashnormaddr0, addrhashnormaddr1);
      
  //if((DRAMTYPE == 0) || (DRAMTYPE == 5)) {
  //  if ((NormAddr & ((pow_ras (2, VALIDHI[channelId]) - 1) >> 3)) != (ChannelAddr & ((pow_ras (2, VALIDHI[channelId]) - 1) >> 3))) {
  //    //nhuif(ASSERT_UMC_ADDR_TRANS){
  //    //nhu  printf ("File of coredump is %s and line of coredump is %d\n",__FILE__,__LINE__); exit(1);}
  //    //nhuelse
  //    //nhu  printf ("ERROR: Given NormAddr_39_3=%jx, Backward NormAddr_39_3=%jx\n\n",
  //    //nhu      (ChannelAddr & ((uint64_t)pow_ras(2,VALIDHI[channelId])-1) )>>3,(NormAddr & ((uint64_t)pow_ras(2,VALIDHI[channelId])-1))>>3);
  //  }
  //}
       
  *cs_num = Chipselect;
  *bank = Bank;
  *row = Row;
  *col = Col;
  *rankmul = Rankmul;
       
  // Check if the outputs respect the config
  if (Bank >= ((noofbank == 2) ? 32 : ((noofbank == 1) ? 16 : 8))) {
    IDS_HDT_CONSOLE (MAIN_FLOW, "ERROR: Bank of the Given NormAddr is out of bounds\n");
  }

  if (Row >= (UINT32) (pow_ras (2, (noofrowlo + 10 + noofrowhi)))) {
    IDS_HDT_CONSOLE (MAIN_FLOW, "ERROR: Row of the Given NormAddr is out of bounds\n");
  }

  if (Col >= (UINT16)(pow_ras (2, (noofcol + 5)))) {
    IDS_HDT_CONSOLE (MAIN_FLOW, "ERROR: Col of the Given NormAddr is out of bounds\n");
  }
}

/*------------------------------------------------------------------
 Function: checkDramHit

 Purpose: Lookup a system address in the DRAM address map.

 Parameters (all are input only)
   sysAddr (ulong)
     The address to be converted.
     The user must remove all VMGuard key indices from the system address.
   ccmInstanceId (uint)
     An instance ID of a CCM that we will look up the map.
 Returns:
   The destination (CS) fabric ID

 Side Effects:
   None:

 Limitations:
   - Does not support non-power-of-2 channels (not used on ZP)

 *------------------------------------------------------------------*/
UINT32
checkDramHit (
  UINT64  sysAddr,
  UINT32  ccmInstanceId
  )
{
  UINT64 dramBaseAddr;
  UINT64 dramLimitAddr;

  UINT32 dramBaseReg;
  UINT32 dramLimitReg;
  UINT32 systemFabricIdReg;

  UINT32  addrRngVal;
  UINT32  dstFabricId;
  UINT32  intLvAddrSel;
  UINT32  intLvAddrBit;
  UINT32  intLvNumDies;
  UINT32  intLvNumChan;
  UINT32  firstDieIdBit;
  UINT32  firstSocketIdBit;
  UINT32  csId;
  UINT32  numSocketsInterleaved;
  UINT32  numDieInterleaved=0;
  UINT32  numChanInterleaved=0;
  UINT32  numInterleaveBits=0;
  UINT32  hashEnabled;
  UINT32  socketIdShift;
  UINT32  socketIdMask;
  UINT32  dieIdMask;
  UINT32  dieIdShift;
  UINT32  addrMapNum;
  UINT32  nodeId;

  nodeId = 0;

  for (addrMapNum=0; addrMapNum < NUM_DRAM_MAPS; addrMapNum++)
  {
    dramBaseReg = getDfRegDramBase(ccmInstanceId, nodeId, addrMapNum);
    addrRngVal = getBit (ADDRRNGVAL, dramBaseReg);
    if (addrRngVal == 0) {
      continue;
    }
    dramLimitReg = getDfRegDramLimit (ccmInstanceId, nodeId, addrMapNum);
    dramBaseAddr = getBits (DRAMBASEADDRLO, DRAMBASEADDRHI, dramBaseReg);
    dramBaseAddr = dramBaseAddr << 28;

    dramLimitAddr = getBits (DRAMLIMITADDRLO, DRAMLIMITADDRHI, dramLimitReg);
    dramLimitAddr = dramLimitAddr << 28;
    dramLimitAddr |= ((UINT64) 0x0FFFFFFF);

    if ((sysAddr >= dramBaseAddr) && (sysAddr <= dramLimitAddr)) {
      systemFabricIdReg = getDfRegSystemFabricIdMask (nodeId);
      socketIdShift = getBits (SOCKETIDSHIFTLO, SOCKETIDSHIFTHI, systemFabricIdReg);
      socketIdMask = getBits (SOCKETIDMASKLO, SOCKETIDMASKHI, systemFabricIdReg);
      dieIdShift = getBits (DIEIDSHIFTLO, DIEIDSHIFTHI, systemFabricIdReg);
      dieIdMask = getBits (DIEIDMASKLO, DIEIDMASKHI, systemFabricIdReg);
      
      // hit, now figure out the DstFabricId.
      intLvAddrSel = getBits (INTLVADDRSELLO, INTLVADDRSELHI, dramBaseReg);
      //assert (getBit(2, intLvAddrSel) == 0);
      intLvAddrBit = (getBit (1, (UINT32) intLvAddrSel) ? (getBit (0, (UINT32) intLvAddrSel) ? 11 : 10) : (getBit (0, (UINT32) intLvAddrSel) ? 9 : 8));

      intLvNumChan = getBits (INTLVNUMCHANLO, INTLVNUMCHANHI, dramBaseReg);
      //assert (intLvNumChan != 4);
      //assert (intLvNumChan != 6);
      //assert (intLvNumChan <= 8);
      // If we are using address hashing, the interleave address bit must be 8 or 9.
      //assert ((intLvNumChan != 8) || (intLvAddrSel == 0) || (intLvAddrSel == 1));
      if (intLvNumChan == 8) {
        hashEnabled = TRUE;
      } else {
        hashEnabled = FALSE;
      }
      numChanInterleaved = 1;   // For compiler error
      numDieInterleaved = 1;    // For compiler error
      switch (intLvNumChan) {
        case 0:
          numChanInterleaved = 1;
          numInterleaveBits = 0;
          break;
        case 1:
        case 8:
          numChanInterleaved = 2;
          numInterleaveBits = 1;
          break;
        case 3:
          numChanInterleaved = 4;
          numInterleaveBits = 2;
          break;
        case 5:
          numChanInterleaved = 8;
          numInterleaveBits = 3;
          break;
        case 7:
          numChanInterleaved = 16;
          numInterleaveBits = 4;
          break;
        //default:
          //assert(0);
      }

      intLvNumDies = getBits (INTLVNUMDIESLO, INTLVNUMDIESHI, dramLimitReg);
      //assert (intLvNumDies != 3);
      switch (intLvNumDies) {
        case 0:
          numDieInterleaved = 1;
          break;
        case 1:
          numDieInterleaved = 2;
          numInterleaveBits += 1;
          break;
        case 2:
          numDieInterleaved = 4;
          numInterleaveBits += 2;
          break;
        case 3:
          numDieInterleaved = 8;
          numInterleaveBits += 3;
          break;
        //default:
          //assert(0);
      }

      numSocketsInterleaved = getBit(INTLVNUMSKTS, dramLimitReg) + 1;
      numInterleaveBits += (numSocketsInterleaved - 1);
      //assert (numInterleaveBits <= 4);

      dstFabricId = getBits (DSTFABRICIDLO, DSTFABRICIDHI, dramLimitReg);

      // Calculate the CSID that we take from the address.
      firstDieIdBit = intLvAddrBit;
      if (numChanInterleaved > 1) {
        if (hashEnabled) {
          // [hashAddrBit] = XOR of sysAddr{intLvAddrBit, 12, 18, 21, 30} 
          dstFabricId += (getBit (intLvAddrBit, (UINT32) sysAddr) ^
                          getBit (12, (UINT32) sysAddr) ^
                          getBit (18, (UINT32) sysAddr) ^
                          getBit (21, (UINT32) sysAddr) ^
                          getBit (30, (UINT32) sysAddr));
          firstDieIdBit ++;
        } else {
          // firstDieIdBit += log2 (numChanInterleaved);
          switch (numChanInterleaved) {
          case 2:
            firstDieIdBit += 1;
            break;
          case 4:
            firstDieIdBit += 2;
            break;
          case 8:
            firstDieIdBit += 3;
            break;
          case 16:
            firstDieIdBit += 4;
            break;
          }
          dstFabricId += (UINT32) getBits64 (intLvAddrBit, firstDieIdBit - 1, sysAddr); 
        }
      }

      firstSocketIdBit = firstDieIdBit;
      if (numDieInterleaved > 1) {
        // firstSocketIdBit += log2(numDieInterleaved);
        switch (numDieInterleaved) {
        case 2:
          firstSocketIdBit += 1;
          break;
        case 4:
          firstSocketIdBit += 2;
          break;
        case 8:
          firstSocketIdBit += 3;
          break;
        }
        csId = (UINT32) getBits64 (firstDieIdBit, firstSocketIdBit - 1, sysAddr);
        dstFabricId |= (csId << dieIdShift);
      }
      if (numSocketsInterleaved > 1) {
        csId = (UINT32) getBits64 (firstSocketIdBit, firstSocketIdBit + numSocketsInterleaved - 1, sysAddr);
        dstFabricId |= (csId << socketIdShift);
      }
    
      return (dstFabricId);
    }
  }
  //assert(0); // missed in address maps.
  return(0);
}

/*------------------------------------------------------------------
 Function: calcSysAddr

 Purpose: Denormalize an address from a memory controller into a
   system address.

 Parameters (all are input only)
   normAddr (ulong)
     The address to be converted
   mySocketNum (uint):
     This socket number within the system where this normalized
     address was found.
     Valid range (on ZP): 0-1
   myDieNum (uint):
     This die number within the socket where this normalized
     address was found.
     Valid range (on ZP): 0-3
   myChannelNum (uint):
     This channel number within the die where this normalized
     address was found.
     Valid range (on ZP): 0-1
 Returns:
   A system address (ulong)

 Side Effects:
   None:

 Limitations:
   - Does not support non-power-of-2 channels (not used on ZP)
   - The system address returned will not have any VMGuard key information
   - When the UMC address is being used for system functions
     e.g. PSP private area, CC6 save address); the algorithm will
    give you the system address - which is actually a E820 hole in
    the memory. The components are accessing this through a
    different address (the 'magic' or 'privileged' region).
    We could expand this algorithm to detect these ranges and
    change it to a 'magic' address; but it wasn't clear what
    the expectations were).

 *------------------------------------------------------------------*/
UINT64 
calcSysAddr (
  UINT64  normAddr,
  UINT32  mySocketNum,
  UINT32  myDieNum,
  UINT32  myChannelNum
  )
{
  UINT64  hiAddrOffset;
  UINT64  dramBaseAddr;
  UINT64  dramLimitAddr;
  UINT64  dramHoleBase;
  UINT64  preBaseSysAddr;
  UINT64  sysAddr;
  UINT64  preNormAddr;
  UINT64  deIntLvAddr;
  UINT64  tempAddrA, tempAddrB, tempAddrC;

  UINT32  systemFabricIdReg;
  UINT32  dramBaseReg;
  UINT32  dramLimitReg;

  UINT32  socketIdShift;
  UINT32  socketIdMask;
  UINT32  dieIdMask;
  UINT32  dieIdShift;
  UINT32  numDFInstances;
  UINT32  nodeId;
  UINT32  csInstanceId;
  UINT32  csFabricId;
  //UINT32  myDieType;
  UINT32  base;
  UINT32  intLvAddrSel;
  UINT32  intLvAddrBit;
  UINT32  intLvNumDies;
  UINT32  intLvNumChan;
  UINT32  numSocketsInterleaved;
  UINT32  numDieInterleaved=0;
  UINT32  numChanInterleaved=0;
  UINT32  numInterleaveBits=0;
  UINT32  firstSocketIdBit;
  UINT32  firstDieIdBit;
  UINT32  csId=0;
  UINT32  csMask;
  UINT32  holeEn;
  UINT32  hiAddrOffsetEn;
  UINT32  addrRngVal;
  UINT32  hashEnabled;
  UINT32  hashedBit;

  ASSERT (mySocketNum <= 2);
  ASSERT (myDieNum <= 4);
  ASSERT (myChannelNum <= 2);

  nodeId = (mySocketNum * 4) + myDieNum;

  // Detect some information about the system
  //myDieType = getBits (MYDIETYPELO, MYDIETYPEHI, getDfRegSystemCfg (nodeId));
  systemFabricIdReg = getDfRegSystemFabricIdMask (nodeId);
  socketIdShift = getBits (SOCKETIDSHIFTLO, SOCKETIDSHIFTHI, systemFabricIdReg);
  socketIdMask = getBits (SOCKETIDMASKLO, SOCKETIDMASKHI, systemFabricIdReg);
  dieIdShift = getBits (DIEIDSHIFTLO, DIEIDSHIFTHI, systemFabricIdReg);
  dieIdMask = getBits (DIEIDMASKLO, DIEIDMASKHI, systemFabricIdReg);
  numDFInstances = getBits (BLKINSTCOUNTLO, BLKINSTCOUNTHI, getDfRegFabricBlkInstanceCnt (nodeId));

  // Find the matching CS
  // This is a bit of "magic" (requires one to "know" the methodology
  // for attaching CS->UMC rather than programmatically determining it).
  // It is safe to assume that the UMC number matches the CS sequence
  // (the second UMC will be attached to the second CS that you find
  // in the search) and will be on the same socket/die/offset.
  // CS instance IDs can be detected by scanning (from instance number 0
  // to numDFInstances) and pulling out those that have
  // DF::FabricBlockInstanceInformation0[InstanceType] == CS.
  // The number you find should equal DF::DieComponentMapB[myDieType][CSCount]
  // (do a broadcast read for this). Note: This is the last broadcast read of the
  // algorithm. All future accesses are instance-only reads to the targeted CS.

  // BOZO: finish this, for now, we're just using CsInstanceID = channel number (correct on ZP)
  csInstanceId = myChannelNum;

  // Once you have the CS instance ID, now get the FabricID:
  csFabricId = getBits(BLOCKFABRICIDLO, BLOCKFABRICIDHI, getDfRegFabricBlkInstInfo3 (csInstanceId, nodeId));
  IDS_HDT_CONSOLE (MAIN_FLOW, "csInstanceId = %d, csFabricId = %x\n", csInstanceId, csFabricId);

  // Read the CS offset registers and determine whether this
  // address was part of base/limit register 0, 1, or 2.
  // Since base 2 is only used in tri-channel mappings, which the
  // algorithm doesn't implement, this skips that.
  hiAddrOffsetEn = getBit (HIADDROFFSETEN, getDfRegDramOffset (csInstanceId, nodeId, 1));
  hiAddrOffset = getBits (HIADDROFFSETLO, HIADDROFFSETHI, getDfRegDramOffset (csInstanceId, nodeId, 1));
  hiAddrOffset = hiAddrOffset << 28;
  IDS_HDT_CONSOLE (MAIN_FLOW, "hiAddrOffsetEn[1] = %d, hiAddrOffset[1] = 0x%016lX\n", hiAddrOffsetEn, hiAddrOffset);
  if (hiAddrOffsetEn && (normAddr >= hiAddrOffset)) {
    base = 1;
  } else {
    base = 0;
  }

  // Now set up variables from the CS base/limit registers
  dramBaseReg = getDfRegDramBase (csInstanceId, nodeId, base);
  dramLimitReg = getDfRegDramLimit (csInstanceId, nodeId, base);
  IDS_HDT_CONSOLE (MAIN_FLOW, "dramBaseReg = 0x%08X, dramLimitReg = 0x%08X\n", dramBaseReg, dramLimitReg);

  addrRngVal = getBit (ADDRRNGVAL, dramBaseReg);
  ASSERT (addrRngVal == 1);

  if (base == 0) {
    hiAddrOffset = 0;
  } else {
    hiAddrOffset = getBits (HIADDROFFSETLO, HIADDROFFSETHI, getDfRegDramOffset (csInstanceId, nodeId, base));
    hiAddrOffset = hiAddrOffset << 28;
  }
  IDS_HDT_CONSOLE (MAIN_FLOW, "hiAddrOffset = 0x%016lX\n", hiAddrOffset);

  dramBaseAddr = getBits (DRAMBASEADDRLO, DRAMBASEADDRHI, dramBaseReg);
  dramBaseAddr = dramBaseAddr << 28;
  IDS_HDT_CONSOLE (MAIN_FLOW, "dramBaseAddr = 0x%016lX\n", dramBaseAddr);

  dramLimitAddr = getBits (DRAMLIMITADDRLO, DRAMLIMITADDRHI, dramLimitReg);
  dramLimitAddr = dramLimitAddr << 28;
  dramLimitAddr |= ((UINT64) 0x0FFFFFFF);
  IDS_HDT_CONSOLE (MAIN_FLOW, "dramLimitAddr = 0x%016lX\n", dramLimitAddr);

  holeEn = getBit (LGCYMMIOHOLEEN, dramBaseReg);
  dramHoleBase = getBits (DRAMHOLEBASELO, DRAMHOLEBASEHI, getDfRegDramHoleCtrl (csInstanceId, nodeId));
  dramHoleBase = dramHoleBase << 24;
  IDS_HDT_CONSOLE (MAIN_FLOW, "holeEn = %d, dramHoleBase = 0x%016lX\n", holeEn, dramHoleBase);

  intLvAddrSel = getBits (INTLVADDRSELLO, INTLVADDRSELHI, dramBaseReg);
  intLvAddrBit = (getBit (1, intLvAddrSel) ? (getBit (0, intLvAddrSel) ? 11 : 10) : (getBit (0, intLvAddrSel) ? 9 : 8));

  intLvNumChan = getBits (INTLVNUMCHANLO, INTLVNUMCHANHI, dramBaseReg);
  // If we are using address hashing, the interleave address bit must be 8 or 9.
  //ASSERT ((intLvNumChan != 8) || (intLvAddrSel == 0) || (intLvAddrSel == 1));
  if (intLvNumChan == 8) {
    hashEnabled = TRUE;
  } else {
    hashEnabled = FALSE;
  }
  switch (intLvNumChan) {
    case 0:
      numChanInterleaved = 1;
      numInterleaveBits = 0;
      break;
    case 1:
    case 8:
      numChanInterleaved = 2;
      numInterleaveBits = 1;
      break;
    case 3:
      numChanInterleaved = 4;
      numInterleaveBits = 2;
      break;
    case 5:
      numChanInterleaved = 8;
      numInterleaveBits = 3;
      break;
    case 7:
      numChanInterleaved = 16;
      numInterleaveBits = 4;
      break;
    default:
      numChanInterleaved = 1;
      numInterleaveBits = 0;
      break;
  }

  intLvNumDies = getBits (INTLVNUMDIESLO, INTLVNUMDIESHI, dramLimitReg);
  switch (intLvNumDies) {
    case 0:
      numDieInterleaved = 1;
      break;
    case 1:
      numDieInterleaved = 2;
      numInterleaveBits += 1;
      break;
    case 2:
      numDieInterleaved = 4;
      numInterleaveBits += 2;
      break;
    case 3:
      numDieInterleaved = 8;
      numInterleaveBits += 3;
      break;
  }

  numSocketsInterleaved = getBit (INTLVNUMSKTS, dramLimitReg) + 1;
  numInterleaveBits += (numSocketsInterleaved - 1);
  ASSERT (numInterleaveBits <= 4);

  IDS_HDT_CONSOLE (MAIN_FLOW, "intLvAddrBit = %d, numSocketsInterleaved = %d, numDieInterleaved = %d, numChanInterleaved = %d, numInterleaveBits = %d, hashEnabled = %d\n",
                   intLvAddrBit, numSocketsInterleaved, numDieInterleaved, numChanInterleaved, numInterleaveBits, hashEnabled);

  // Subtract the offset
  preNormAddr = normAddr - hiAddrOffset;
  IDS_HDT_CONSOLE (MAIN_FLOW, "preNormAddr = 0x%016lX\n", preNormAddr);

  // Account for interleaving bits
  deIntLvAddr = preNormAddr;
  if (numInterleaveBits > 0) {
    // Calculate the CSID that is part of the de-normalized address.
    csId = 0;
    firstDieIdBit = 0;
    if (numChanInterleaved > 1) {
      //firstDieIdBit = log2(numChanInterleaved); // not supporting tri-channel here.
      switch (numChanInterleaved) {
      case 2:
        firstDieIdBit = 1;
        break;
      case 4:
        firstDieIdBit = 2;
        break;
      case 8:
        firstDieIdBit = 3;
        break;
      case 16:
        firstDieIdBit = 4;
        break;
      }
      csMask = (1 << firstDieIdBit) - 1;
      csId = csFabricId & csMask;
    }
    firstSocketIdBit = firstDieIdBit;
    if (numDieInterleaved > 1) {
      //firstSocketIdBit = firstDieIdBit + log2(numDieInterleaved);
      switch (numDieInterleaved) {
      case 2:
        firstSocketIdBit = firstDieIdBit + 1;
        break;
      case 4:
        firstSocketIdBit = firstDieIdBit + 2;
        break;
      case 8:
        firstSocketIdBit = firstDieIdBit + 3;
        break;
      }
      csId |= (((csFabricId & dieIdMask) >> dieIdShift) << firstDieIdBit);
    }
    if (numSocketsInterleaved > 1) {
      csId |= (((csFabricId & socketIdMask) >> socketIdShift) << firstSocketIdBit);
    }
    IDS_HDT_CONSOLE (MAIN_FLOW, "numDieInterleaved = %d, numChanInterleaved = %d\n", numDieInterleaved, numChanInterleaved);
    IDS_HDT_CONSOLE (MAIN_FLOW, "csId = 0x%x, firstSocketIdBit = %d, firstDieIdBit = %d\n", csId, firstSocketIdBit, firstDieIdBit);

    // the pre-interleaved address bit consists of:
    //      XXXXXXIIIYYYYY
    //  where III is the ID for this CS, and XXXXXXYYYYY are the address bits from the post-interleaved
    //  numInterleaveBits has been calculated to tell us how many "I" bits there are.
    //  intLvAddrBit tells us how many "Y" bits there are (were "I" starts)
    tempAddrA = getBits64 (0, (intLvAddrBit -1), preNormAddr);
    tempAddrB = ((UINT64)csId << intLvAddrBit);
    tempAddrC = getBits64 (intLvAddrBit, 63, preNormAddr);
    tempAddrC = tempAddrC << (intLvAddrBit + numInterleaveBits);
    deIntLvAddr = tempAddrA | tempAddrB | tempAddrC;
  }
  IDS_HDT_CONSOLE (MAIN_FLOW, "deIntLvAddr = 0x%016lX\n", deIntLvAddr);

  // Add in the base.
  preBaseSysAddr = deIntLvAddr + dramBaseAddr;
  IDS_HDT_CONSOLE (MAIN_FLOW, "preBaseSysAddr = 0x%016lX\n", preBaseSysAddr);

  // Account for the DRAM hole
  if (holeEn && (preBaseSysAddr >= dramHoleBase)) {
    IDS_HDT_CONSOLE (MAIN_FLOW, "dramHoleBase = 0x%016lX, adjust = 0x%016lX\n", dramHoleBase, ((((UINT64) 1) << 32) - dramHoleBase));
    sysAddr = preBaseSysAddr + ((((UINT64) 1) << 32) - dramHoleBase);
  } else {
    sysAddr = preBaseSysAddr;
  }
  IDS_HDT_CONSOLE (MAIN_FLOW, "sysAddr = 0x%016lX\n", sysAddr);

  // Adjust for the hashing (if enabled)
  if (hashEnabled) {
    // deIntLvAddr[hashAddrBit] = XOR of deIntLvAddr{12, 18, 21, 30} and csId[0]
    hashedBit = getBit (12, (UINT32) sysAddr) ^
                getBit (18, (UINT32) sysAddr) ^
                getBit (21, (UINT32) sysAddr) ^
                getBit (30, (UINT32) sysAddr) ^
                getBit (0, csId);
    if (hashedBit != getBit (intLvAddrBit, (UINT32) sysAddr)) {
      sysAddr ^= (((UINT64) 1) << intLvAddrBit);
    }
    IDS_HDT_CONSOLE (MAIN_FLOW, "hashedBit= %d, sysAddr = 0x%016lX\n", hashedBit, sysAddr);
  }

  // Check that you didn't go over the pair limit
  ASSERT (sysAddr <= dramLimitAddr);
  return (sysAddr);
}

/*------------------------------------------------------------------
 Function: calcNormAddr

 Purpose: Normalize a system address into a memory controller
   (normalized) system address.

 Parameters (all are input only)
   sysAddr (ulong)
     The address to be converted.
     The user must remove all VMGuard key indices from the system address.
 Returns:
   A normalized address (ulong)

 Side Effects:
   None:

 Limitations:
   - Does not support non-power-of-2 channels (not used on ZP)

 *------------------------------------------------------------------*/
NORMALIZED_ADDRESS 
calcNormAddr (
  UINT64 sysAddr
  )
{
  UINT64  hiAddrOffset;
  UINT64  dramBaseAddr;
  UINT64  dramLimitAddr;
  UINT64  dramHoleBase;
  UINT64  postHoleSysAddr;
  UINT64  preIntlvSysAddr;
  UINT64  intLvAddr;
  UINT64  tempAddrA;
  UINT64  tempAddrB;

  UINT32  systemFabricIdReg;
  UINT32  dramBaseReg;
  UINT32  dramLimitReg;

  UINT32  socketIdShift;
  UINT32  socketIdMask;
  UINT32  dieIdMask;
  UINT32  dieIdShift;
  UINT32  nodeId;
  UINT32  ccmInstanceId;
  UINT32  csInstanceId;
  UINT32  csFabricId;
  UINT32  base;
  UINT32  intLvAddrSel;
  UINT32  intLvAddrBit;
  UINT32  intLvNumDies;
  UINT32  intLvNumChan;
  UINT32  numInterleaveBits;
  UINT32  holeEn;
  UINT32  hiAddrOffsetEn;
  UINT32  addrRngVal;
  NORMALIZED_ADDRESS    normalizedAddress;

  numInterleaveBits = 0;
  nodeId = 0;

  // Detect some information about the system
  systemFabricIdReg = getDfRegSystemFabricIdMask (nodeId);
  socketIdShift = getBits (SOCKETIDSHIFTLO, SOCKETIDSHIFTHI, systemFabricIdReg);
  socketIdMask = getBits (SOCKETIDMASKLO, SOCKETIDMASKHI, systemFabricIdReg);
  dieIdShift = getBits (DIEIDSHIFTLO, DIEIDSHIFTHI, systemFabricIdReg);
  dieIdMask = getBits (DIEIDMASKLO, DIEIDMASKHI, systemFabricIdReg);

  // BOZO: Find a CCM instance ID;
  ccmInstanceId = 2;    // InstanceId, CCM0 = 2, CCM1 = 3

  // Find the channel...
  csFabricId = checkDramHit (sysAddr, ccmInstanceId);
  IDS_HDT_CONSOLE (MAIN_FLOW, "csFabricId = %08x\n", csFabricId);

  // convert the dstFabricId to a CS instance ID and nodeId.
  nodeId = (((csFabricId & socketIdMask) >> socketIdShift) * 4) + ((csFabricId & dieIdMask) >> dieIdShift);
  csInstanceId = csFabricId & ~(socketIdMask | dieIdMask);

  // Check if it hits on DRAM mapping register 0 or 1 in the CS.
  dramBaseReg = getDfRegDramBase(csInstanceId, nodeId, 1);    // Mapping register 1
  dramBaseAddr = getBits(DRAMBASEADDRLO, DRAMBASEADDRHI, dramBaseReg);
  dramBaseAddr = dramBaseAddr << 28;
  addrRngVal = getBit(ADDRRNGVAL, dramBaseReg);
  if (addrRngVal && (sysAddr >= dramBaseAddr)) {
    base = 1;
  } else {
    base = 0;
  }

  // Now set up variables from the CS base/limit registers
  dramBaseReg = getDfRegDramBase(csInstanceId, nodeId, base);
  dramLimitReg = getDfRegDramLimit(csInstanceId, nodeId, base);

  addrRngVal = getBit(ADDRRNGVAL, dramBaseReg);

  dramBaseAddr = getBits(DRAMBASEADDRLO, DRAMBASEADDRHI, dramBaseReg);
  dramBaseAddr = dramBaseAddr << 28;

  dramLimitAddr = getBits(DRAMLIMITADDRLO, DRAMLIMITADDRHI, dramLimitReg);
  dramLimitAddr = dramLimitAddr << 28;
  dramLimitAddr |= ((UINT64) 0x0FFFFFFF);

  holeEn = getBit(LGCYMMIOHOLEEN, dramBaseReg);
  dramHoleBase = getBits(DRAMHOLEBASELO, DRAMHOLEBASEHI, getDfRegDramHoleCtrl(csInstanceId, nodeId));
  dramHoleBase = dramHoleBase << 24;

  intLvAddrSel = getBits(INTLVADDRSELLO, INTLVADDRSELHI, dramBaseReg);
  intLvAddrBit = (getBit(1, intLvAddrSel) ? (getBit(0, intLvAddrSel) ? 11 : 10) : (getBit(0, intLvAddrSel) ? 9 : 8));

  intLvNumChan = getBits(INTLVNUMCHANLO, INTLVNUMCHANHI, dramBaseReg);
  switch (intLvNumChan) {
    case 0:
      numInterleaveBits = 0;
      break;
    case 1:
    case 8:
      numInterleaveBits = 1;
      break;
    case 3:
      numInterleaveBits = 2;
      break;
    case 5:
      numInterleaveBits = 3;
      break;
    case 7:
      numInterleaveBits = 4;
      break;
    //default:
    //  assert(0);
  }

  intLvNumDies = getBits(INTLVNUMDIESLO, INTLVNUMDIESHI, dramLimitReg);
  switch (intLvNumDies) {
    case 0:
      break;
    case 1:
      numInterleaveBits+=1;
      break;
    case 2:
      numInterleaveBits+=2;
      break;
    //default:
      //assert(0);
  }

  numInterleaveBits += getBit(INTLVNUMSKTS, dramLimitReg);

  // Account for the DRAM hole
  if (holeEn && (sysAddr >= dramHoleBase)) {
    postHoleSysAddr = sysAddr - ((((UINT64) 1) << 32) - dramHoleBase);
  } else {
    postHoleSysAddr = sysAddr;
  }

  // Subtract the base.
  preIntlvSysAddr = postHoleSysAddr - dramBaseAddr;

  // Account for intereleaving bits
  intLvAddr = preIntlvSysAddr;
  if (numInterleaveBits > 0) {
    // the system address bit consists of:
    //      XXXXXXIIIYYYYY
    //  where III is the ID for this CS, and XXXXXXYYYYY are the address bits used in the
    //  normalized address.
    //  numInterleaveBits has been calculated to tell us how many "I" bits there are.
    //  intLvAddrBit tells us how many "Y" bits there are (were "I" starts)
    tempAddrA = getBits64(0, (intLvAddrBit -1), preIntlvSysAddr);
    tempAddrB = getBits64((intLvAddrBit + numInterleaveBits), 63, preIntlvSysAddr);
    tempAddrB = tempAddrB << intLvAddrBit;
    intLvAddr = tempAddrA | tempAddrB;
  }

  if (base == 0) {
    hiAddrOffset = 0;
  } else {
    hiAddrOffsetEn = getBit (HIADDROFFSETEN, getDfRegDramOffset (csInstanceId, nodeId, 1));
    hiAddrOffset = getBits (HIADDROFFSETLO, HIADDROFFSETHI, getDfRegDramOffset (csInstanceId, nodeId, 1));
    hiAddrOffset = hiAddrOffset << 28;
  }

  // Add the offset
  normalizedAddress.normalizedAddr = intLvAddr + hiAddrOffset;
  normalizedAddress.normalizedSocketId = (UINT8) ((csFabricId & socketIdMask) >> socketIdShift);
  normalizedAddress.normalizedDieId = (UINT8) ((csFabricId & dieIdMask) >> dieIdShift);
  normalizedAddress.normalizedChannelId = (UINT8) (csFabricId & ~(socketIdMask | dieIdMask));
  normalizedAddress.reserved = 0;

  return (normalizedAddress);
}

/**
 * RasSmnRead - Read SMN register
 *
 * @param[in] IohcBus     - IOHC (Node) bus number
 * @param[in] SmnAddress  - Register SMN address
 * @param[in] Value       - Pointer to register value
 *
 */
VOID
RasSmnRead (
  IN       UINT32              IohcBus,
  IN       UINT32              SmnAddress,
  IN       UINT32              *Value
  )
{
  UINT32    RegIndex;
  UINTN     PciAddress;

  RegIndex = SmnAddress;
  PciAddress = ((UINTN)IohcBus << 20) + NB_SMN_INDEX_2;
  PciWrite32 (PciAddress, RegIndex);
  PciAddress = ((UINTN)IohcBus << 20) + NB_SMN_DATA_2;
  *Value = PciRead32 (PciAddress);
}

VOID
RasSmnWrite (
  IN       UINT32              IohcBus,
  IN       UINT32              SmnAddress,
  IN       UINT32              *Value
  )
{
  UINT32    RegIndex;
  UINTN     PciAddress;

  RegIndex = SmnAddress;
  PciAddress = ((UINTN)IohcBus << 20) + NB_SMN_INDEX_2;
  PciWrite32 (PciAddress, RegIndex);
  PciAddress = ((UINTN)IohcBus << 20) + NB_SMN_DATA_2;
  PciWrite32 (PciAddress, *Value);
}

VOID
RasSmnRW (
  IN       UINT32              IohcBus,
  IN       UINT32              SmnAddress,
  IN       UINT32              AndMask,
  IN       UINT32              OrMask
  )
{
  UINT32    RegValue;

  RasSmnRead (IohcBus, SmnAddress, &RegValue);
  RegValue &= AndMask;
  RegValue |= OrMask;
  RasSmnWrite (IohcBus, SmnAddress, &RegValue);
}

/**
 * RasSmnRead8 - Read SMN register in Byte
 *
 * @param[in] IohcBus     - IOHC (Node) bus number
 * @param[in] SmnAddress  - Register SMN address
 * @param[in] Value8      - Pointer to register value
 *
 */
VOID
RasSmnRead8 (
  IN       UINT32              IohcBus,
  IN       UINT32              SmnAddress,
  IN       UINT8               *Value8
  )
{
  UINT32    RegIndex;
  UINTN     PciAddress;

  RegIndex = SmnAddress & 0xFFFFFFFC;
  PciAddress = ((UINTN)IohcBus << 20) + NB_SMN_INDEX_2;
  PciWrite32 (PciAddress, RegIndex);
  PciAddress = ((UINTN)IohcBus << 20) + NB_SMN_DATA_2;
  *Value8 = PciRead8 (PciAddress + SmnAddress & 0x3);
}

VOID
RasSmnWrite8 (
  IN       UINT32              IohcBus,
  IN       UINT32              SmnAddress,
  IN       UINT8               *Value8
  )
{
  UINT32    RegIndex;
  UINTN     PciAddress;

  RegIndex = SmnAddress & 0xFFFFFFFC;
  PciAddress = ((UINTN)IohcBus << 20) + NB_SMN_INDEX_2;
  PciWrite32 (PciAddress, RegIndex);
  PciAddress = ((UINTN)IohcBus << 20) + NB_SMN_DATA_2;
  PciWrite8 (PciAddress + (UINTN) (SmnAddress & 0x3), *Value8);
}

VOID
RasSmnRW8 (
  IN       UINT32              IohcBus,
  IN       UINT32              SmnAddress,
  IN       UINT8               AndMask,
  IN       UINT8               OrMask
  )
{
  UINT8    RegValue;

  RasSmnRead8 (IohcBus, SmnAddress, &RegValue);
  RegValue &= AndMask;
  RegValue |= OrMask;
  RasSmnWrite8 (IohcBus, SmnAddress, &RegValue);
}

