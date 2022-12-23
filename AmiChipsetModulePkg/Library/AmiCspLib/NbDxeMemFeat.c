//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

/** @file NbDxeMemFeat.c
    This file contains generic NB code that is common between
    various components such as NB DXE etc

**/

#include <Library/DramMap.h>
#include <Library/MemSmmLib.h>
#include <Protocol/SmmBase.h>
#include <Protocol/SmmCpuIo.h>
#include <Library/NbCspLib.h>

UINT64  MmioBase = 0;
UINT64  ReadMsr (UINT32 Msr);

EFI_SMM_SYSTEM_TABLE    *mSmst;

/**
    Check if Vtd is supported.

    @param VOID

    @retval TRUE  Vtd is supported
    @retval FALSE Vtd is not supported
**/

BOOLEAN
NbCheckVtdSupport (
  IN    VOID
)
{
/**** PORTING REQUIRED ****
    Please check the datasheet of the chipset for the register to know
    if Vtd is supported or not
**** PORTING REQUIRED ****/
    return FALSE;
}


/**
    Lock and unlock Pavpc

    @param Mode               TRUE: Lock Pavpc; FALSE: Unlock Pavpc

    @retval EFI_UNSUPPORTED   This function is not supported
    @retval EFI_SUCCESS       Success to lock/unlock Pavpc

**/

EFI_STATUS
NbLockPavpc (
  IN    BOOLEAN Mode
)
{
/**** PORTING REQUIRED ****
    Please check the datasheet of the chipset for the register to know
    how to lock and unlock Pavpc.
    If it is not supported by the chip, please return EFI_UNSUPPORTED.
**** PORTING REQUIRED ****/
    return EFI_UNSUPPORTED;
}

/*----------------------------------------------------------------------------------------*/
/**
 *  LibAgesaSmmMemRead
 *  Description
 *      SMM Memory Read Access
 *
 * @param[in]       SmmIo           Pointer to SMM CPU IO interface
 * @param[in]       AccessWidth     Access width
 * @param[in]       Address         Memory address
 * @param[out]      Value           Pointer to data buffer
 *
 */
/*----------------------------------------------------------------------------------------*/

VOID
LibAgesaSmmMemRead (
  IN    EFI_SMM_CPU_IO_INTERFACE    *SmmIo,
  IN    EFI_SMM_IO_WIDTH            AccessWidth,
  IN    UINT64                      Address,
  OUT   VOID                        *Value
)
{
    SmmIo->Mem.Read (SmmIo, AccessWidth, Address, 1, Value);
}

/*----------------------------------------------------------------------------------------*/
/**
 *  LibAgesaSmmMemWrite
 *  Description
 *      SMM Memory Write
 *
 * @param[in]       SmmIo           Pointer to SMM CPU IO interface
 * @param[in]       AccessWidth     Access width
 * @param[in]       Address         Memory address
 * @param[out]      Value           Pointer to data buffer
 *
 */
/*----------------------------------------------------------------------------------------*/

VOID
LibAgesaSmmMemWrite (
  IN    EFI_SMM_CPU_IO_INTERFACE    *SmmIo,
  IN    EFI_SMM_IO_WIDTH            AccessWidth,
  IN    UINT64                      Address,
  IN    VOID                        *Value
  )
{
    SmmIo->Mem.Write (SmmIo, AccessWidth, Address, 1, Value);
}


/*----------------------------------------------------------------------------------------*/
/**
 *  Set_PCI
 *  Description
 *      Sets the value at given Bus, Device, Function and Offset
 *
 * @param[in]       Bus           Bus
 * @param[in]       Device        Device (mostly 24)
 * @param[in]       Function      Function
 * @param[in]       Foffset       Offset
 * @param[out]      Value         Value
 *
 */
/*----------------------------------------------------------------------------------------*/

VOID
SetPci (
  IN    UINT32  Bus,
  IN    UINT32  Device,
  IN    UINT32  Function,
  IN    UINT32  Foffset,
  IN    UINT64  Value
)
{
    UINT32  AddressValue;

    //AddressValue = MAKE_SBDFO (0, Bus, Device, Function, Foffset);
    AddressValue = ((UINT32)1 << 31) + (Bus << 16) + (Device << 11) +
     (Function << 8) + (Foffset & 0xFC) + ((Foffset & 0xF00) << (24 - 8));
    AddressValue |= (UINT32) MmioBase;
    LibAgesaSmmMemWrite (&mSmst->SmmIo, 2, AddressValue, &Value);
}

/*----------------------------------------------------------------------------------------*/
/**
 *  Get_PCI
 *  Description
 *      Reads the value at given Bus, Device, Function and Offset
 *
 * @param[in]       Bus           Bus
 * @param[in]       Device        Device (mostly 24)
 * @param[in]       Function      Function
 * @param[in]       Foffset       Offset
 *
 */
/*----------------------------------------------------------------------------------------*/

UINT64
GetPci (
  IN    UINT32  Bus,
  IN    UINT32  Device,
  IN    UINT32  Function,
  IN    UINT32  Foffset
)
{
    UINT32  AddressValue;
    UINT64  Value;

    //AddressValue = MAKE_SBDFO (0, Bus, Device, Function, Foffset);
    AddressValue = ((UINT32)1 << 31) + (Bus << 16) + (Device << 11) +
     (Function << 8) + (Foffset & 0xFC) + ((Foffset & 0xF00) << (24 - 8));
    AddressValue |= (UINT32) MmioBase;
    LibAgesaSmmMemRead (&mSmst->SmmIo, 2, AddressValue, &Value);
    return Value;
}

/*----------------------------------------------------------------------------------------*/
/**
 *  CSInterleavingBitSwap
 *  Description
 *      Function returns a normalized address after adjusting for possible bit swapping
 *      by CS Interleaving.
 *
 * @param[in]       addr                addr
 * @param[in]       CSMask              CSMask)
 * @param[in]       hiBit               hiBit
 * @param[in]       lowBit              lowBit
 *
 */
/*----------------------------------------------------------------------------------------*/

UINT64
CsInterleavingBitSwap(
  IN    UINT64  Addr,
  IN    UINT64  CsMask,
  IN    UINT8   HiBit,
  IN    UINT8   LowBit
)
{
    UINT64  Mask;

    // Bits are swapped if the lower CSMask bits are zeros.
    // hiBit, lowBit indicate the LSB at the start of the range of bits that
    // take part in the swap an depend on the DimmAddrMap.
    // Sanity check the CSMask
    Mask = (CsMask >> LowBit & 0x7) ^ 0x7;
    return (Mask ? (Addr & ~(Mask << HiBit) & ~(Mask << LowBit)) |
     (((Addr >> HiBit) & Mask) << LowBit) |
     (((Addr >> LowBit) & Mask) << HiBit) : Addr);
}

/*----------------------------------------------------------------------------------------*/
/**
 *  AddrToBankSwizzle
 *  Description
 *      Function returns a DRAM device bank address after adjusting for possible
 *      remapping by bank swizzling. See D18F2x94[BankSwizzleMode]
 *
 * @param[in]       swizzle     swizzle
 * @param[in]       addr        addr)
 * @param[in]       bankbit     bankbit
 * @param[in]       offset      offset
 *
 */
/*----------------------------------------------------------------------------------------*/

UINT8
AddrToBankSwizzle (
  IN    BOOLEAN Swizzle,
  IN    UINT64  Addr,
  IN    UINT8   BankBit,
  IN    UINT8   Offset
)
{
    // BankBit indicates the LSB at the start of the range of bits that
    // are mapped to the DRAM device bank address and depends on the DimmAddrMap.
    if (!Swizzle)
        return (UINT8) (((Addr >> BankBit) & 0x7));
    else
    {
        return ((UINT8) ((((Addr >> BankBit) & 1) ^ ((Addr >> (BankBit + 3 + Offset)) & 1) ^
         ((Addr >> (BankBit + 6 + Offset)) & 1)) |
         ((((Addr >> (BankBit + 1)) & 1) ^ ((Addr >> (BankBit + 4 + Offset)) & 1) ^
         ((Addr >> (BankBit + 7 + Offset)) & 1)) << 1) |
         ((((Addr >> (BankBit + 2)) & 1) ^ ((Addr >> (BankBit + 5 + Offset)) & 1) ^
         ((Addr >> (BankBit + 8 + Offset)) & 1)) << 2)));
    }
}

/*----------------------------------------------------------------------------------------*/
/**
 *  BankSwapAddr
 *  Description
 *      Function returns a normalized address after adjusting for possible bit swapping
 *      by CS Interleaving.
 *
 * @param[in]       BankSwap            BankSwap
 * @param[in]       addr                addr
 * @param[in]       DctSelBankSwap      DctSelBankSwap
 *
 */
/*----------------------------------------------------------------------------------------*/

UINT64
BankSwapAddr
(
  IN    BOOLEAN BankSwap,
  IN    UINT64  Addr,
  IN    BOOLEAN DctSelBankSwap
  )
{
    if (BankSwap)
    {
        if (DctSelBankSwap)
        {
            // [10:8] swapped with [15:13]
            Addr = ((((Addr >> 8) & 0x7) << 13) | (((Addr >> 13) & 0x7) << 8) | (Addr & ~(0xE700)));
        }
        else
        {
            // [11:9] swapped with [15:13]
            Addr = ((((Addr >> 9) & 0x7) << 13) | (((Addr >> 13) & 0x7) << 9) | (Addr & ~(0xEE00)));
        }
    }
    return Addr;
}

/*----------------------------------------------------------------------------------------*/
/**
 *  BankSwizzleToAddr
 *  Description
 *      Function returns a normalized DRAM addresss after adjusting for possible
 *      remapping by bank swizzlling. See D18F2x[1,0]94[BankSwizzleMode]
 *
 * @param[in]       swizzle     swizzle
 * @param[in]       addr        addr
 * @param[in]       bank        bank
 * @param[in]       bankbit     bankbit
 * @param[in]       offset      offset
 *
 */
/*----------------------------------------------------------------------------------------*/

UINT64
BankSwizzleToAddr
(
  IN    BOOLEAN Swizzle,
  IN    UINT64  Addr,
  IN    UINT8   Bank,
  IN    UINT8   BankBit,
  IN    UINT8   Offset
)
{
    // Recreate the normalized address; Note: A == A ^ B ^ B
    if (!Swizzle)
        Addr |= Bank << BankBit;
    else
    {
        Addr |= (((Bank & 1) ^ ((Addr >> (BankBit + 3 + Offset)) & 1) ^ ((Addr >> (BankBit + 6 + Offset)) & 1)) |
         ((((Bank >> 1) & 1) ^ ((Addr >> (BankBit + 4 + Offset)) & 1) ^ ((Addr >> (BankBit + 7 + Offset)) & 1)) << 1) |
         ((((Bank >> 2) & 1) ^ ((Addr >> (BankBit + 5 + Offset)) & 1) ^ ((Addr >> (BankBit + 8 + Offset)) & 1)) << 2)
         ) << BankBit;
    }
    return Addr;
}

/*----------------------------------------------------------------------------------------*/
/**
 *  NormalizedToBankAddrMap
 *  Description
 *      This function converst the given physical address into DIMM specific info
 *
 * @param[in]       ChannelAddr         ChannelAddr
 * @param[in]       CSMask              CSMask)
 * @param[in]       DimmAddrMap         DimmAddrMap
 * @param[in]       BankSwap            BankSwap
 * @param[in]       DctSelBankSwap      DctSelBankSwap
 * @param[in]       BankSwizzleMode     BankSwizzleMode
 * @param[in, out]  *Bank               Bank
   @param[in, out]  *Row                Row
   @param[in, out]  *Col                Col
 *
 */
/*----------------------------------------------------------------------------------------*/

VOID
NormalizedToBankAddrMap (
  IN        UINT64  ChannelAddr,
  IN        UINT64  CsMask,
  IN        UINT8   DimmAddrMap,
  IN        BOOLEAN BankSwap,
  IN        BOOLEAN DctSelBankSwap,
  IN        BOOLEAN BankSwizzleMode,
  IN OUT    UINT8   *Bank,
  IN OUT    UINT32  *Row,
  IN OUT    UINT16  *Col
)
{
    UINT64  Addr = 0;

    ChannelAddr = BankSwapAddr (BankSwap, ChannelAddr, DctSelBankSwap);

    // BankSwizzleMode is calculated on the normalized addr
    // Select Row/Col based on the CS interleave adjustment tables
    switch (DimmAddrMap)
    {
        case 0x1:
            *Bank = AddrToBankSwizzle (BankSwizzleMode, ChannelAddr, 13, 0);
            Addr = CsInterleavingBitSwap (ChannelAddr, CsMask, 28, !BankSwap ? 16 : (DctSelBankSwap ? 11 : 12));
            *Row = (UINT32)(((Addr >> 18) & 0x3FF) | (((Addr >> 16) & 0x3) << 10));
            *Col = (UINT16)((Addr >> 3) & 0x3FF);
            break;
        case 0x2:
            *Bank = AddrToBankSwizzle (BankSwizzleMode, ChannelAddr, 13, 0);
            Addr = CsInterleavingBitSwap (ChannelAddr, CsMask, 29, !BankSwap ? 16 : (DctSelBankSwap ? 11 : 12));
            *Row = (UINT32) (((Addr >> 18) & 0x7FF) | (((Addr >> 16) & 0x3) << 11));
            *Col = (UINT8)((Addr >> 3) & 0x3FF);
            break;
        case 0x5:
            *Bank = AddrToBankSwizzle (BankSwizzleMode, ChannelAddr, 13, 0);
            Addr = CsInterleavingBitSwap (ChannelAddr, CsMask, 30, !BankSwap ? 16 : (DctSelBankSwap ? 11 : 12));
            *Row = (UINT32) (((Addr >> 18) & 0xFFF) | (((Addr >> 16) & 0x3) << 12));
            *Col = (UINT8) ((Addr >> 3) & 0x3FF);
            break;
        case 0x7:
            *Bank = AddrToBankSwizzle (BankSwizzleMode, ChannelAddr, 13, 0);
            Addr = CsInterleavingBitSwap (ChannelAddr, CsMask, 31, !BankSwap ? 16 : (DctSelBankSwap ? 11 : 12));
            *Row = (UINT32) (((Addr >> 18) & 0x1FFF) | (((Addr >> 16) & 0x3) << 13));
            *Col = (UINT8) ((Addr >> 3) & 0x3FF);
            break;
        case 0xA:
            *Bank = AddrToBankSwizzle (BankSwizzleMode, ChannelAddr, 13, 0);
            Addr = CsInterleavingBitSwap (ChannelAddr, CsMask, 32, !BankSwap ? 16 : (DctSelBankSwap ? 11 : 12));
            *Row = (UINT32) (((Addr >> 18) & 0x3FFF) | (((Addr >> 16) & 0x3) << 14));
            *Col = (UINT8)((Addr >> 3) & 0x3FF);
            break;
        case 0xB:
            *Bank = AddrToBankSwizzle (BankSwizzleMode, ChannelAddr, 14, 0);
            Addr = CsInterleavingBitSwap (ChannelAddr, CsMask, 33, !BankSwap ? 17 : (DctSelBankSwap ? 11 : 12));
            *Row = (UINT32) (((Addr >> 18) & 0x7FFF) | (((Addr >> 17) & 0x1) << 15));
            *Col = (UINT8) (((Addr >> 3) & 0x3FF) | (((Addr >> 13) & 0x1) << 11));
            break;
        default:
            break;
    }
}

/*----------------------------------------------------------------------------------------*/
/**
 *  PlatformTranslateSysAddrToCs
 *  Description
 *      This function converst the given physical address into DIMM specific info
 *
 * @param[in]       SysAddr         SysAddr
 * @param[out]      CSFound         CSFound)
 * @param[out]      NodeID          NodeID
 * @param[out]      ChannelSelect   ChannelSelect
 * @param[out]      ChipSelect      ChipSelect
 * @param[out]      Bank            Bank
 * @param[out]      Row             Row
 * @param[out]      Col             Col
 *
 */
/*----------------------------------------------------------------------------------------*/

VOID
PlatformTranslateSysAddrToCS (
  IN    UINT64  SysAddr,
  OUT   BOOLEAN *CsFound,
  OUT   UINT8   *NodeID,
  OUT   UINT8   *ChannelSelect,
  OUT   UINT8   *ChipSelect,
  OUT   UINT8   *Bank,
  OUT   UINT32  *Row,
  OUT   UINT16  *Col
)
{
    UINT32  Node;
    UINT32  Range;
    UINT32  Cs;
    UINT32  DctRange;
    UINT32  Offset;
    UINT64  Temp;
    BOOLEAN DramEn;
    UINT64  DramBase;
    UINT64  DramLimit;
    UINT64  DramBaseSysAddr;
    UINT64  DramLimitSysAddr;
    UINT64  DramHoleBase;
    UINT64  DramHoleOffset;
    UINT64  DctBaseAddr;
    UINT64  DctLimitAddr;
    BOOLEAN DramMemHoistValid;
    BOOLEAN DctSelBankSwap;
    BOOLEAN DctAddrVal;
    BOOLEAN LgcyMmioHoleEn;
    UINT32  DctSel;
    UINT64  ChannelOffset;
    UINT64  ChannelAddr;
    UINT64  CsBase;
    UINT64  CsMask;
    BOOLEAN CsEn;
    UINT64  InputAddr;
    BOOLEAN BankSwizzleMode;
    BOOLEAN BankSwap;
    UINT8   DimmAddrMap;

    *CsFound = FALSE;
    // Loop to determine the dram range
    for (Node = 0; Node < NUM_NODES; ++Node)
    {
        for (Range = 0; Range < NUM_NODES; ++Range)
        {
            // Extract variables from Dram Base
            Offset = 0x40 + (Range << 3);
            Temp = GetPci (BUS_0, (DEVICE_24 + Node), FUNCTION_1, Offset);
            DramEn = (Temp & 0x3) > 0 ? TRUE : FALSE;
            if (!DramEn)
                continue;

            DramBase = (((UINT64)GetPci (BUS_0, (DEVICE_24 + Node), FUNCTION_1,
                                  Offset + 0x100) & 0xFF) << 40) |
                                  ((Temp & 0xFFFF0000) << 8);

            // Extract variables from Dram Limit
            Temp = GetPci (BUS_0, (DEVICE_24 + Node), FUNCTION_1, Offset + 4);
            *NodeID = (UINT8)(Temp & 0x7);
            DramLimit = (((UINT64)GetPci (BUS_0, (DEVICE_24 + Node), FUNCTION_1,
                                   Offset + 0x104) & 0xFF) << 40) |
                                   ((Temp << 8) | 0xFFFFFF);

            // For compatiblity with DRAM C6 Storage, extract variables from the per-node DRAM Base/Limit System Address
            Temp = GetPci (BUS_0, (DEVICE_24 + *NodeID), FUNCTION_1, 0x120);
            DramBaseSysAddr = (Temp & 0x1FFFFF) << 27;

            // Extract variables from Dram Limit
            Temp = GetPci (BUS_0, (DEVICE_24 + *NodeID), FUNCTION_1, 0x124);
            DramLimitSysAddr = ((Temp & 0x1FFFFF) << 27) | 0x7FFFFFF;

            if ((DramEn && DramBase <= SysAddr && SysAddr <= DramLimitSysAddr))
            {
                // Extract variables from D18F1xF0
                Temp = GetPci (BUS_0, (DEVICE_24 + *NodeID), FUNCTION_1, 0xF0);
                DramHoleOffset = (Temp & 0xFF80) << 16;
                DramMemHoistValid = (Temp & 0x2) > 0 ? TRUE : FALSE;
                DramHoleBase = ((Temp >> 24) & 0xFF) << 24;
                
                // Address belongs to this node based on DramBase/Limit,
                // but is in the memory hole so it doesn't map to DRAM
                if (DramMemHoistValid && DramHoleBase <= SysAddr && SysAddr < 0x100000000)
                    return;

                // Extract variables from D18F2x114
                Temp = GetPci (BUS_0, (DEVICE_24 + *NodeID), FUNCTION_2, 0x114);
                DctSelBankSwap = ((Temp >> 9) & 0x1) > 0 ? TRUE : FALSE;

                // Single Channel
                DctAddrVal = FALSE;
                for (DctRange = 0; DctRange < 4; ++DctRange)
                {
                    // Extract variables from F2x2[1,0][8,0]
                    Temp = GetPci (BUS_0, (DEVICE_24 + *NodeID), FUNCTION_1,
                            0x200 + 8 * DctRange);
                    DctAddrVal = (Temp & 0x1) > 0 ? TRUE : FALSE;
                    if (!DctAddrVal)
                        continue;

                    DctBaseAddr = (((Temp >> 11) & 0x1FFF) << 27);
                    DctSel = (UINT32) ((Temp >> 4) & 0x7);
                    LgcyMmioHoleEn = ((Temp >> 1) & 0x1) > 0 ? TRUE : FALSE;
                    
                    // Extract variables from F2x2[1,0][C,4]
                    Temp = GetPci (BUS_0, (DEVICE_24 + *NodeID), FUNCTION_1,
                            0x204 + 8 * DctRange);
                    DctLimitAddr = (((Temp >> 11) & 0x1FFF) << 27);

                    if (DctAddrVal)
                        break;
                }

                *ChannelSelect = 0;
                ChannelOffset = 0;
                if (DramMemHoistValid && (SysAddr >= 0x100000000))
                    ChannelOffset = DramHoleOffset;
                else
                    ChannelOffset = DramBase;

                // Remove hoisting offset and normalize to DRAM bus addresses
                ChannelAddr = SysAddr - ChannelOffset;

                // Set DctCfgSel = ChannelSelect
                SetPci (BUS_0, (DEVICE_24 + *NodeID), FUNCTION_1, 0x10C, *ChannelSelect);

                // Determine the Chip Select
                for (Cs = 0; Cs < NUM_CS_PER_CHANNEL; ++Cs)
                {
                    // Obtain the CS Base from D18F2x[1,0][4C:40]
                    Offset = 0x40 + (Cs << 2);
                    Temp = GetPci (BUS_0, (DEVICE_24 + *NodeID), FUNCTION_2, Offset);
                    CsEn = (Temp & 0x1) > 0 ? TRUE : FALSE;
                    CsBase = (((Temp >> 19) & 0xFFF) << 27) | (((Temp >> 5) & 0x3FF) << 11);

                    // Obtain the CS Mask from D18F2x[64:60]
                    Offset = 0x60 + ((Cs >> 1) << 2);
                    Temp = GetPci (BUS_0, (DEVICE_24 + *NodeID), FUNCTION_2, Offset);
                    CsMask = (((Temp >> 19) & 0xFFF) << 27) | (((Temp >> 5) & 0x3FF) << 11);

                    // Adjust the Channel Addr for easy comparison
                    InputAddr = (((ChannelAddr >> 27) & 0xFFF) << 27) |
                     (((ChannelAddr >> 11) & 0x3FF) << 11);

                    if (CsEn && (InputAddr & ~CsMask) == (CsBase & ~CsMask))
                    {
                        *CsFound = TRUE;
                        *ChipSelect = (UINT8)Cs;

                        // Extract variables from D18F2x80
                        DimmAddrMap = (UINT8) ((((UINT64)GetPci (BUS_0, (DEVICE_24 + *NodeID),
                                                          FUNCTION_2, 0x80)) >> ((*ChipSelect >> 1) * 4)) & 0xF);

                        // Extract variables from the CS Mask
                        Offset = 0x60 + ((*ChipSelect >> 1) << 2);

                        // Extract variables from D18F2x94
                        BankSwizzleMode = ((GetPci (BUS_0, DEVICE_24 + *NodeID, FUNCTION_2,
                                             0x94) >> 22) & 0x1) > 0 ? TRUE : FALSE;

                        // Extract variables from D18F2xA8
                        BankSwap = ((GetPci (BUS_0, DEVICE_24 + *NodeID, FUNCTION_2,
                                      0xA8) >> 20) & 0x1) > 0 ? TRUE : FALSE;

                        // Determine the Bank, Row, and Col
                        NormalizedToBankAddrMap (ChannelAddr, CsMask, DimmAddrMap, BankSwap, DctSelBankSwap, BankSwizzleMode, Bank, Row, Col);

                        // Sanity check outputs
                        return;
                    }
                }
            }
        }
    }
    return;
}

/*----------------------------------------------------------------------------------------*/
/**
 *  TranslateSysAddrToCS
 *  Description
 *      This function converst the given physical address into DIMM specific info
 *
 * @param[in]       AmdDimmInfo       AmdDimmInfo
 *
 */
/*----------------------------------------------------------------------------------------*/

EFI_STATUS
TranslateSysAddrToCs (
  IN    AMD_IDENTIFY_DIMM   *AmdDimmInfo
)
{
    BOOLEAN ChipSelectFound = FALSE;

    //
    // Get the MmioBase address to access extended config info
    //
    MmioBase = ReadMsr (0xC0010058);
    MmioBase &= 0x000000FFFFF00000;

    PlatformTranslateSysAddrToCs (AmdDimmInfo->MemoryAddress, &ChipSelectFound,
     &AmdDimmInfo->SocketId, &AmdDimmInfo->MemChannelId, &AmdDimmInfo->ChipSelect,
     &AmdDimmInfo->Bank, &AmdDimmInfo->Row, &AmdDimmInfo->Column);

    AmdDimmInfo->DimmId = AmdDimmInfo->ChipSelect / 2;
    AmdDimmInfo->ChipSelect %= 2;

    if (!ChipSelectFound)
        return EFI_NOT_FOUND;
    else
        return EFI_SUCCESS;
}

/**
    Get the information of the DIMM location indicated by MemoryAddr

    @param MemoryAddr         The system address to convert
    @param NbAddressDecode    Pointer to the buffer used to store NB_ADDRESS_DECODE

    @retval EFI_UNSUPPORTED   This function is not supported
    @retval EFI_SUCCESS       Success to get the information of DIMM location

**/

EFI_STATUS
NbGetDimmLocInfo (
  IN CONST  UINTN               MemoryAddr,
  OUT       NB_ADDRESS_DECODE   *NbAddressDecode
)
{
    AMD_IDENTIFY_DIMM   DimmInfo;
    EFI_STATUS          Status;

/**** PORTING REQUIRED ****
    Please check if MRC supports memory address decode.
    If it is not supported by MRC, please return EFI_UNSUPPORTED.
**** PORTING REQUIRED ****/
    DimmInfo.MemoryAddress = (UINT64)MemoryAddr;
    Status = TranslateSysAddrToCs (&DimmInfo);

    NbAddressDecode->ChannelNumber = (UINT8) DimmInfo.MemChannelId;
    NbAddressDecode->DimmNumber = (UINT8) DimmInfo.DimmId;
    NbAddressDecode->Rank = (UINT8) DimmInfo.ChipSelect;
    NbAddressDecode->Bank = (UINT8) DimmInfo.Bank;
    NbAddressDecode->Ras = (UINT16) DimmInfo.Row;
    NbAddressDecode->Cas = (UINT16) DimmInfo.Column;

    return Status;
}


//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
