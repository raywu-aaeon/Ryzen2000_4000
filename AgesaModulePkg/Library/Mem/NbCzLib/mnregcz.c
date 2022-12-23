/* $NoKeywords:$ */
/**
 * @file
 *
 * mnregcz.c
 *
 * Common Northbridge register related functions for CZ
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/NB/CZ)
 * @e \$Revision: 325208 $ @e \$Date: 2015-08-26 10:05:40 +0800 (Wed, 26 Aug 2015) $
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

/*
 *----------------------------------------------------------------------------
 *                                MODULES USED
 *
 *----------------------------------------------------------------------------
 */

#include <Library/BaseMemoryLib.h>
#include "AGESA.h"
//#include "AdvancedApi.h"
#include "Library/AmdBaseLib.h"
#include "Library/IdsLib.h"
#include <Library/PciLib.h>
#include "Ids.h"
#include "OptionMemory.h"
#include "mm.h"
#include "mn.h"
#include "mncz.h"
#include "mnreg.h"
#include "mnpmu.h"
#include "mport.h"
#include "merrhdl.h"
#include "Library/AmdHeapLib.h"
#include "cpuRegisters.h"
#include "Filecode.h"
CODE_GROUP (G3_DXE)
RDATA_GROUP (G3_DXE)


#define FILECODE LIBRARY_MEM_NBCZLIB_MNREGCZ_FILECODE

/*----------------------------------------------------------------------------
 *                          DEFINITIONS AND MACROS
 *
 *----------------------------------------------------------------------------
 */
#define BC_FIELDS   4

#define PMU_SMB_MEM_PS0_START   0x23
#define PMU_SMB_MEM_PS1_START   0x37

/*----------------------------------------------------------------------------
 *                           TYPEDEFS AND STRUCTURES
 *
 *----------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------
 *                        PROTOTYPES OF LOCAL FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */

// Pad name, Pad instance, Chiplet number, Group number, Pad number
STATIC CONST DDR_CHIP_TO_PAD_ENTRY ROMDATA ChipToPadTableCZ[] = {
  {MEMCKE0, 2, 0, 0, 3},
  {MEMCKE0, 3, 0, 0, 2},
  {MEMCKE0, 0, 0, 0, 1},
  {MEMCKE0, 1, 0, 0, 0},
  {MEMADD0, 14, 0, 2, 11},
  {MEMADD0, 15, 0, 2, 10},
  {MEMADD0, 12, 0, 2, 9},
  {MEMBANK0, 2, 0, 2, 8},
  {MEMADD0, 8, 0, 2, 7},
  {MEMADD0, 7, 0, 2, 6},
  {MEMADD0, 11, 0, 2, 5},
  {MEMADD0, 9, 0, 2, 4},
  {MEMCLK0_L, 2, 1, 0, 3},
  {MEMCLK0_H, 2, 1, 0, 2},
  {MEMCLK0_L, 0, 1, 0, 1},
  {MEMCLK0_H, 0, 1, 0, 0},
  {MEMADD0, 5, 1, 1, 9},
  {MEMADD0, 6, 1, 1, 8},
  {MEMADD0, 2, 1, 1, 7},
  {MEMADD0, 1, 1, 1, 6},
  {MEMADD0, 3, 1, 1, 5},
  {MEMADD0, 4, 1, 1, 4},
  {MEMCLK0_L, 3, 2, 0, 3},
  {MEMCLK0_H, 3, 2, 0, 2},
  {MEMCLK0_L, 1, 2, 0, 1},
  {MEMCLK0_H, 1, 2, 0, 0},
  {MEMADD0, 10, 2, 1, 7},
  {MEMBANK0, 0, 2, 1, 6},
  {MEMADD0, 0, 2, 1, 5},
  {MEMBANK0, 1, 2, 1, 4},
  {MEMCS0_L, 6, 2, 2, 11},
  {MEMCS0_L, 4, 2, 2, 10},
  {MEMCS0_L, 2, 2, 2, 9},
  {MEMCS0_L, 0, 2, 2, 8},
  {MEMADD0, 13, 3, 0, 3},
  {MEMCAS0_L, 0, 3, 0, 2},
  {MEMWE0_L, 0, 3, 0, 1},
  {MEMRAS0_L, 0, 3, 0, 0},
  {MEMODT0, 3, 3, 1, 7},
  {MEMODT0, 1, 3, 1, 6},
  {MEMODT0, 0, 3, 1, 5},
  {MEMODT0, 2, 3, 1, 4},
  {MEMCS0_L, 7, 3, 2, 11},
  {MEMCS0_L, 5, 3, 2, 10},
  {MEMCS0_L, 3, 3, 2, 9},
  {MEMCS0_L, 1, 3, 2, 8},
  {MEMDQ, 7, 0, 1, 7},
  {MEMDQ, 6, 0, 1, 6},
  {MEMDQ, 5, 0, 1, 5},
  {MEMDQ, 4, 0, 1, 4},
  {MEMDQ, 3, 0, 0, 3},
  {MEMDQ, 2, 0, 0, 2},
  {MEMDQ, 1, 0, 0, 1},
  {MEMDQ, 0, 0, 0, 0},
  {MEMDQS, 0, 0, 2, 10},
  {MEMDQS, 0, 0, 2, 8},
  {MEMDQS, 0, 0, 2, 11},
  {MEMDQS, 0, 0, 3, 9},
  {MEMDQ_L, 0, 0, 0, 0},
  {MEMDQ_H, 0, 0, 1, 4},
  {MEMDQS_L, 0, 0, 2, 11},
  {MEMDQS_H, 0, 0, 2, 8},
  {MEMADD_A14, 14, 0, 2, 11},
  {MEMADD_A15, 15, 0, 2, 10},
  {MEMADD_A13, 13, 3, 0, 3},
  {MEMADD_UNUSED, 0, 1, 1, 11},
  {MEMADD_UNUSED, 0, 1, 1, 10}
};

/*----------------------------------------------------------------------------
 *                            EXPORTED FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */
/*-----------------------------------------------------------------------------*/
/**
 *      This function matches the SOC_LOGICAL_ID with certain criteria to
 *      determine if it is supported by this NBBlock.
 *
 *     @param[in]       *LogicalIdPtr - Pointer to the SOC_LOGICAL_ID
 *
 *     @return          TRUE -  This node is a CZ.
 *     @return          FALSE - This node is not a CZ.
 *
 */
BOOLEAN
MemNIsIdSupportedCZ (
  IN       SOC_LOGICAL_ID *LogicalIdPtr
  )
{
  if (((LogicalIdPtr->Family & AMD_FAMILY_15_CZ) != 0)
      && ((LogicalIdPtr->Revision & AMD_REV_F15_ALL) != 0)) {
    return TRUE;
  } else {
    return FALSE;
  }
}

/*----------------------------------------------------------------------------
 *                              LOCAL FUNCTIONS
 *
 *----------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------*/
/**
 *
 *   This function gets or sets a value to a bit field in a PCI register.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]   FieldName - Bit Field to be programmed
 *     @param[in]   InputValue - Value to be programmed
 *     @param[in]   IsSet - Indicates if the function will set or get
 *
 *     @return      value read, if the function is used as a "get"
 */

UINT32
MemNCmnGetSetFieldCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 IsSet,
  IN       UINTN FieldName,
  IN       UINT32 InputValue
  )
{
  BF_LOCATION *BfLoc;
  PCI_ADDR PciAddr;
  UINT32 Address;
  UINT32 ReadAddress;
  UINT32 SaveAddress;
  UINT32 HiBit;
  UINT32 LoBit;
  UINT32 Mask;
  BOOLEAN IsLinked;
  BOOLEAN IsMemPstate;
  BOOLEAN WholeRegAccess;
  UINTN  RegIndex;
  UINT32 Value;
  UINT32 Field;
  BF_NAME_ENC BfNameEnc;

  BOOLEAN HasMoreInstances;
  UINT8   i;
  UINT8   Limit;
  CONST UINT8   BroadcastBit[BC_FIELDS] =  {8, 12, 20, 24};
  CONST UINT32  BroadcastMask[BC_FIELDS] = {0x00000F00, 0x0000F000, 0x00F00000, 0x03000000};
  UINT8   BroadcastIndex[BC_FIELDS];
  UINT8   BroadcastBase[BC_FIELDS];
  UINT8   BroadcastLimit[BC_FIELDS];
  UINT8   PadTabIdx;
  UINT8   PadTabIdxPredict;
  BOOLEAN UseGroup;
  BOOLEAN UsePadTab;
  BOOLEAN UnrollNextField;

  Field = InputValue;
  Value = 0;
  BfNameEnc.FieldName = (BIT_FIELD_NAME)FieldName;
  FieldName = BfNameEnc.Parse.Index;
  PadTabIdx = GET_SIZE_OF (ChipToPadTableCZ);
  UseGroup = FALSE;
  UsePadTab = FALSE;

  ASSERT ((FieldName < RegIdLimit));

  if (NBPtr->NBRegTable[FieldName] != 0) {
    //======================================================================
    // Obtain register address and bit field location
    //======================================================================
    //
    if (FieldName < BFEndOfList) {
      BfLoc = (BF_LOCATION *) &(NBPtr->NBRegTable[FieldName]);
      RegIndex = BfLoc->RegIndex;
      HiBit = BfLoc->HiBit;
      LoBit = BfLoc->LoBit;
      IsMemPstate = (BOOLEAN) BfLoc->MemPstate;
      IsLinked = (BOOLEAN) BfLoc->Linked;
      if ((HiBit - LoBit) < 31) {
        WholeRegAccess = FALSE;
      } else {
        WholeRegAccess = TRUE;
      }
      SaveAddress = Address = NBPtr->NBRegTable[RegIndex];
    } else {
      RegIndex = FieldName;
      WholeRegAccess = TRUE;
      HiBit = 31;
      LoBit = 0;
      IsMemPstate = FALSE;
      IsLinked = FALSE;
      SaveAddress = Address = NBPtr->NBRegTable[RegIndex];
    }

    ASSERT ((HiBit < 32) && (LoBit <= HiBit));    // Only support 32 bit registers

    //======================================================================
    // Prepare broadcast matrix for Phy registers
    //======================================================================
    //
    if (RegIndex > DctPhyRegRangeStart) {
      //IDS_HDT_CONSOLE (MEM_SETREG, "~                   [+] BF enum: %x\n", FieldName);
      for (i = 0; i < BC_FIELDS; i++) {
        Limit = (UINT8) ((Address & BroadcastMask[i]) >> BroadcastBit[i]);
        if (Limit == 0) {
          // This field has single instance, skip unrolling
          BroadcastBase[i] = BroadcastLimit[i] = 0;
        } else if (((BfNameEnc.FieldName & 0xFFFF0000) == 0xFFFF0000) || ((Address & BroadcastMask[i]) == BroadcastMask[i])) {
          // When SW broadcast is disabled or HW broadcast is specified, set base = limit
          BroadcastBase[i] = BroadcastLimit[i] = Limit;
        } else {
          // SW broadcast by default
          // The value of a potential broadcasting field (BroadcastMask) is always seen as the SW limit if not HW broadcasted
          // Be sure to wrap it up with PER_INSTANCE as 'Direct' if it's non-zero and not intended to be SW broadcasted
          BroadcastBase[i] = 0;
          BroadcastLimit[i] = Limit;

          // Check override for each field separately
          switch (i) {
          case 0:
            // For Dimm, DLL, NBPs dependent registers:
            // When PER_DIMM or PER_NB_PS macro is used, select instance specified by macro
            if (BfNameEnc.Parse.DLNPlus1 != 0) {
              BroadcastBase[i] = BroadcastLimit[i] = (UINT8) BfNameEnc.Parse.DLNPlus1 - 1;
              ASSERT ((BfNameEnc.Parse.DLNPlus1 < (4 + 1)) || (BfNameEnc.Parse.DLNPlus1 == (8 + 1)));  // Only support up to 4 instances
            }
            break;
          case 1:
            // For ABYTE and DBYTE type, initialize ChipToPadTable index for translation
            if ((Address & 0x000E0000) == 0x00000000 && BfNameEnc.Parse.PadName != 0) {
              PadTabIdx = 0;
              UseGroup = (Limit <= 4);
              UsePadTab = TRUE;
            }
            break;
          case 2:
            if ((Address & 0x000F0000) == 0x00010000) {
              // For DBYTE type, chiplet controls byte lane:
              // When PER_DATA_BYTE macro is used, select instance specified by macro
              if (BfNameEnc.Parse.PadIdxPlus1 != 0) {
                BroadcastBase[i] = BroadcastLimit[i] = (UINT8) BfNameEnc.Parse.PadIdxPlus1 - 1;
                ASSERT ((BfNameEnc.Parse.PadIdxPlus1 < (10 + 1)));  // Only support up to 9 instances
              }
            }
            break;
          case 3:
            // No SW broadcast to multiple Mem P-state copies
            // For MemPstate dependent registers:
            if (BfNameEnc.Parse.MemPsPlus1 == 0) {
              // Access current MemPstate by default
              BroadcastBase[i] = BroadcastLimit[i] = (UINT8) NBPtr->MemPstate;
            } else if (BfNameEnc.Parse.MemPsPlus1 < 3) {
              // PER_MEM_PS macro is used, select MemPs specified by macro
              BroadcastBase[i] = BroadcastLimit[i] = (UINT8) BfNameEnc.Parse.MemPsPlus1 - 1;
            }
            break;
          default:
            ASSERT (FALSE);
            break;
          }

          ASSERT (BroadcastBase[i] <= BroadcastLimit[i]);
          ASSERT (BroadcastLimit[i] <= Limit);

          // Use HW broadcast instead of SW broadcast when writing whole register
          if (WholeRegAccess && (BroadcastLimit[i] == Limit) && (BroadcastBase[i] == 0)) {
            BroadcastBase[i] = BroadcastLimit[i] = (UINT8) (BroadcastMask[i] >> BroadcastBit[i]);
          }
        }
        // Initialize Index at Base for below unrolling loop
        BroadcastIndex[i] = BroadcastBase[i];
      }
    }

    //======================================================================
    // Get/Set register/field
    //======================================================================
    //
    HasMoreInstances = FALSE;     // One instance by default
    do {
      if (RegIndex > DctPhyRegRangeStart) {
        // Unroll broadcast fields for partial write only
        UnrollNextField = TRUE;

        // Search ChipToPadTable
        while (PadTabIdx < GET_SIZE_OF (ChipToPadTableCZ)) {
          if (BfNameEnc.Parse.PadName == ChipToPadTableCZ[PadTabIdx].PadName) {
            if (((Address & 0x000F0000) == 0x00010000) || (BfNameEnc.Parse.PadIdxPlus1 == 0) || (BfNameEnc.Parse.PadIdxPlus1 == (UINT8) (ChipToPadTableCZ[PadTabIdx].Instance + 1))) {
              BroadcastIndex[1] = BroadcastLimit[1] = UseGroup ? ChipToPadTableCZ[PadTabIdx].Group : ChipToPadTableCZ[PadTabIdx].PadNum;
              if ((Address & 0x000F0000) == 0x00000000) {
                // Only use table chiplet for ABYTE. DBYTE chiplets are byte lanes.
                BroadcastIndex[2] = BroadcastLimit[2] = (UINT8) ChipToPadTableCZ[PadTabIdx].Chiplet;
              }
              UnrollNextField = !UnrollNextField;
              PadTabIdx++;
              // Check if there're any more target pads in the table
              for (PadTabIdxPredict = PadTabIdx; PadTabIdxPredict < GET_SIZE_OF (ChipToPadTableCZ); PadTabIdxPredict ++) {
                if (BfNameEnc.Parse.PadName == ChipToPadTableCZ[PadTabIdxPredict].PadName) {
                  break;
                }
              }
              if (PadTabIdxPredict == GET_SIZE_OF (ChipToPadTableCZ)) {
                // table index wraps around
                // No more target pads. Unroll the next field.
                PadTabIdx = 0;
                UnrollNextField = !UnrollNextField;
              }
              break;
            }
          }
          PadTabIdx++;
        }
        // Unroll each broadcast field
        for (i = 0; i < BC_FIELDS; i++) {
          // Increment any one broadcast field by 1 in each run until all fields unrolled
          Address = (Address & (~BroadcastMask[i])) | ((UINT32) BroadcastIndex[i] << BroadcastBit[i]);
          if (UnrollNextField) {
            if (BroadcastIndex[i] < BroadcastLimit[i]) {
              BroadcastIndex[i]++;
              UnrollNextField = FALSE;
            } else {
              BroadcastIndex[i] = BroadcastBase[i];
            }
          }
        }

        HasMoreInstances = !UnrollNextField;
        if (!IsSet || !WholeRegAccess) {
          ReadAddress = Address;
          if (BfNameEnc.Parse.Direct == 1) {
            ReadAddress = MEM_PS_PER_INSTANCE (NBPtr->MemPstate, SaveAddress);
          }
          // Use instance 0 when reading hardware broadcast registers.
          for (i = 0; i < BC_FIELDS; i++) {
            if ((ReadAddress & BroadcastMask[i]) == BroadcastMask[i]) {
              ReadAddress &= ~BroadcastMask[i];
              // For broadcast chiplet address, do read from the ABYTE instance
              if ((ReadAddress & 0xF0000) == 0x60000 || (ReadAddress & 0xF0000) == 0xF0000) {
                ReadAddress &= 0xFFF0FFFF;
              }
            }
          }

          MemNCmnGetSetFieldCZ (NBPtr, 1, RegDctAddlOffset, ReadAddress);
          Value = MemNCmnGetSetFieldCZ (NBPtr, 0, RegDctAddlData, 0);
          IDS_HDT_CONSOLE (MEM_GETREG, "~R F2_9C_%x = %x\n", ReadAddress, Value);
          if (!IsSet) {
            Address = ReadAddress;
            HasMoreInstances = FALSE;
          }
        } else {
          Value = Field;
        }
      } else if (RegIndex > NbRegRangeStart) {
        ASSERT ((Address & 0xFFFF0000) == 0);       // NB_REG address only has 16 bits
        PciAddr.AddressValue = Address;
        PciAddr.Address.Device = NBPtr->PciAddr.Address.Device;
        PciAddr.Address.Bus = NBPtr->PciAddr.Address.Bus;
        PciAddr.Address.Segment = NBPtr->PciAddr.Address.Segment;
        Address = PciAddr.AddressValue;
        if (IsMemPstate) {
          PciAddr.AddressValue |= (NBPtr->MemPstate << 11);
        }
        if (!(WholeRegAccess && IsSet)) {
          Value = PciRead32 (PciAddr.AddressValue);
          if ((FieldName != RegDctAddlData) && (FieldName != RegDctAddlOffset)) {
            IDS_HDT_CONSOLE (MEM_GETREG, "~R F%d_%03x", (Address >> 12) & 0xF, Address & 0xFFF);
            if (IsMemPstate) {
              IDS_HDT_CONSOLE (MEM_GETREG, "_mp[%d]", NBPtr->MemPstate);
            }
            IDS_HDT_CONSOLE (MEM_GETREG, " = %x\n", Value);
          }
        } else {
          Value = Field;
        }
      } else {
        IDS_HDT_CONSOLE (MEM_SETREG, "RegIndex %d out of range. BF Enum = %d\n", RegIndex, FieldName);
        ASSERT (FALSE);
      }

      if (IsSet) {
        if (!WholeRegAccess) {
          Mask = (((UINT32)1 << (HiBit - LoBit + 1)) - 1);
          Value &= ~(Mask << LoBit);
          Value |= (Field & Mask) << LoBit;
        }

        if (RegIndex > DctPhyRegRangeStart) {
          if (BfNameEnc.Parse.Direct == 1) {
            Address = MEM_PS_PER_INSTANCE (NBPtr->MemPstate, SaveAddress);
            HasMoreInstances = FALSE;
          }
          ASSERT (!NBPtr->IsSupported[ScrubberEn]);   // Phy CSR write is not allowed after scrubber is enabled
          MemNCmnGetSetFieldCZ (NBPtr, 1, RegDctAddlData, Value);
          MemNCmnGetSetFieldCZ (NBPtr, 1, RegDctAddlOffset, Address | DCT_ACCESS_WRITE);
          IDS_HDT_CONSOLE (MEM_SETREG, "~W F2_9C_%x [%d:%d] = %x\n", Address, HiBit, LoBit, Field);
        } else if (RegIndex > NbRegRangeStart) {
          PciAddr.AddressValue = Address;
          if (IsMemPstate) {
            PciAddr.AddressValue |= (NBPtr->MemPstate << 11);
          }
          PciWrite32 (PciAddr.AddressValue, Value);
          if ((FieldName != RegDctAddlData) && (FieldName != RegDctAddlOffset)) {
            IDS_HDT_CONSOLE (MEM_SETREG, "~W F%d_%03x", (Address >> 12) & 0xF, Address & 0xFFF);
            if (IsMemPstate) {
              IDS_HDT_CONSOLE (MEM_SETREG, "_mp[%d]", NBPtr->MemPstate);
            }
            IDS_HDT_CONSOLE (MEM_SETREG, " [%d:%d] = %x\n", HiBit, LoBit, Field);
            //IDS_HDT_CONSOLE (MEM_SETREG, ", BF enum: %x\n", FieldName);
          }
        } else {
          ASSERT (FALSE);
        }
        if (IsLinked) {
          MemNCmnGetSetFieldCZ (NBPtr, 1, FieldName + 1, InputValue >> (HiBit - LoBit + 1));
        }
      } else if (!WholeRegAccess) {
        Value = Value >> LoBit;
        Value &= (((UINT32)1 << (HiBit - LoBit + 1)) - 1);
        IDS_HDT_CONSOLE (MEM_GETREG, "~R        Subfield [%d:%d] = %x\n", HiBit, LoBit, Value);
        if (IsLinked) {
          Value |= MemNCmnGetSetFieldCZ (NBPtr, 0, FieldName + 1, 0) << (HiBit - LoBit + 1);
        }
      }
    } while (HasMoreInstances);
  } else {
    IDS_HDT_CONSOLE (MEM_UNDEF_BF, "\t\tUndefined BF enum: %x\n", FieldName);
  }
  return Value;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function is used by families that use a separate DctCfgSel bit to
 *     select the current DCT which will be accessed by function 2.
 *     NOTE:  This function must be called BEFORE the NBPtr->Dct variable is
 *     updated.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]       *Dct     - Pointer to ID of the target DCT
 *
 */

BOOLEAN
MemNDctCfgSelectCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       VOID *Dct
  )
{
  // Set the DctCfgSel to new DCT
  MemNCmnGetSetFieldCZ (NBPtr, 1, BFDctCfgSel, *(UINT8 *) Dct);

  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *   This function sets the current DCT to work on.
 *   Should be called before accessing a certain DCT
 *   All data structures will be updated to point to the current DCT
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]   Dct - ID of the target DCT
 *
 */

VOID
MemNSwitchDctCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 Dct
  )
{
  ASSERT (NBPtr->DctCount > Dct);
  //
  // Set the DctCfgSel to new DCT
  //
  NBPtr->FamilySpecificHook[DCTSelectSwitch] (NBPtr, &Dct);
  NBPtr->Dct = Dct;
  NBPtr->MCTPtr->Dct = NBPtr->Dct;
  NBPtr->DCTPtr = &(NBPtr->MCTPtr->DctData[NBPtr->Dct]);
  NBPtr->PsPtr = &(NBPtr->PSBlock[NBPtr->Dct]);
  NBPtr->DctCachePtr = &(NBPtr->DctCache[NBPtr->Dct]);

  MemNSwitchChannelNb (NBPtr, NBPtr->Channel);
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function initializes bit field translation table
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in,out]   NBRegTable[]  - Pointer to the bit field data structure
 *
 */

VOID
MemNInitNBRegTableCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN OUT   TSEFO NBRegTable[]
  )
{
  ALLOCATE_HEAP_PARAMS AllocHeapParams;
  LOCATE_HEAP_PTR LocHeap;

  // ---------------------------------------------------------------------------
  // Allocate heap for NB register table
  // ---------------------------------------------------------------------------

  // If NBRegTable for this family exists, use it
  LocHeap.BufferHandle = GENERATE_MEM_HANDLE (ALLOC_NB_REG_TABLE, NbRegTabCZ, 0, 0);
  if (HeapLocateBuffer (&LocHeap, &(NBPtr->MemPtr->StdHeader)) == AGESA_SUCCESS) {
    NBPtr->NBRegTable = (TSEFO *) LocHeap.BufferPtr;
    return;   // skip populating NBRegTable since it already exists.
  }

  // Allocate new buffer for NBRegTable if it has not been allocated
  AllocHeapParams.RequestedBufferSize = sizeof (TSEFO) * (RegIdLimit);
  AllocHeapParams.BufferHandle = GENERATE_MEM_HANDLE (ALLOC_NB_REG_TABLE, NbRegTabCZ, 0, 0);
  AllocHeapParams.Persist = HEAP_SYSTEM_MEM;
  if (AGESA_SUCCESS != HeapAllocateBuffer (&AllocHeapParams, &(NBPtr->MemPtr->StdHeader))) {
    ASSERT (FALSE); // NB and Tech Block Heap allocate error
    return;   // Exit with error
  }
  // Initialize buffer with 0s
  SetMem (AllocHeapParams.BufferPtr, AllocHeapParams.RequestedBufferSize, 0);

  NBPtr->NBRegTable = (TSEFO *)AllocHeapParams.BufferPtr;
  NBRegTable = NBPtr->NBRegTable;

  // ---------------------------------------------------------------------------
  // FUNCTION 1
  // ---------------------------------------------------------------------------
  REG_DEF (NBRegTable, RegDramBase0, _FN (1, 0x40));
  _BF_DEF (NBRegTable, RegDramBase0, BFDramBaseReg0, 31, 0);
  REG_DEF (NBRegTable, RegDramLimit0, _FN (1, 0x44));
  _BF_DEF (NBRegTable, RegDramLimit0, BFDramLimitReg0, 31, 0);
  REG_DEF (NBRegTable, RegDramBaseHi0, _FN (1, 0x140));
  _BF_DEF (NBRegTable, RegDramBaseHi0, BFDramBaseHiReg0, 31, 0);
  REG_DEF (NBRegTable, RegDramLimitHi0, _FN (1, 0x144));
  _BF_DEF (NBRegTable, RegDramLimitHi0, BFDramLimitHiReg0, 31, 0);

  REG_DEF (NBRegTable, RegDramHoleAddr, _FN (1, 0xF0));
  _BF_DEF (NBRegTable, RegDramHoleAddr, BFDramHoleBase, 31, 24);
  _BF_DEF (NBRegTable, RegDramHoleAddr, BFDramHoleOffset, 15,  7);
  _BF_DEF (NBRegTable, RegDramHoleAddr, BFDramMemHoistValid,  1,  1);
  _BF_DEF (NBRegTable, RegDramHoleAddr, BFDramHoleValid,  0,  0);

  REG_DEF (NBRegTable, RegDctCfgSel, _FN (1, 0x10C));
  _BF_DEF (NBRegTable, RegDctCfgSel, BFDctCfgBcEn,  7,  7);
  _BF_DEF (NBRegTable, RegDctCfgSel, BFDctCfgSel,  2,  0);

  REG_DEF (NBRegTable, RegDramBaseSysAddr, _FN (1, 0x120));
  _BF_DEF (NBRegTable, RegDramBaseSysAddr, BFDramBaseAddr, 20,  0);

  REG_DEF (NBRegTable, RegDramLimitSysAddr, _FN (1, 0x124));
  _BF_DEF (NBRegTable, RegDramLimitSysAddr, BFDramLimitAddr, 20,  0);

  REG_DEF (NBRegTable, RegDramCtlrBase0, _FN (1, 0x200));
  _BF_DEF (NBRegTable, RegDramCtlrBase0, BFDctBaseReg0, 31, 0);
  _BF_DEF (NBRegTable, RegDramCtlrBase0, BFLgcyMmioHoleEn0, 1, 1);
  REG_DEF (NBRegTable, RegDramCtlrBase1, _FN (1, 0x208));
  _BF_DEF (NBRegTable, RegDramCtlrBase1, BFDctBaseReg1, 31, 0);
  _BF_DEF (NBRegTable, RegDramCtlrBase1, BFLgcyMmioHoleEn1, 1, 1);
  REG_DEF (NBRegTable, RegDramCtlrBase2, _FN (1, 0x210));
  _BF_DEF (NBRegTable, RegDramCtlrBase2, BFDctBaseReg2, 31, 0);
  _BF_DEF (NBRegTable, RegDramCtlrBase2, BFLgcyMmioHoleEn2, 1, 1);
  REG_DEF (NBRegTable, RegDramCtlrBase3, _FN (1, 0x218));
  _BF_DEF (NBRegTable, RegDramCtlrBase3, BFDctBaseReg3, 31, 0);
  _BF_DEF (NBRegTable, RegDramCtlrBase3, BFLgcyMmioHoleEn3, 1, 1);

  REG_DEF (NBRegTable, RegDramCtlrLimit0, _FN (1, 0x204));
  _BF_DEF (NBRegTable, RegDramCtlrLimit0, BFDctLimitReg0, 31, 0);
  _BF_DEF (NBRegTable, RegDramCtlrLimit0, BFDctIntLvEn0, 3, 0);
  REG_DEF (NBRegTable, RegDramCtlrLimit1, _FN (1, 0x20C));
  _BF_DEF (NBRegTable, RegDramCtlrLimit1, BFDctLimitReg1, 31, 0);
  _BF_DEF (NBRegTable, RegDramCtlrLimit1, BFDctIntLvEn1, 3, 0);
  REG_DEF (NBRegTable, RegDramCtlrLimit2, _FN (1, 0x214));
  _BF_DEF (NBRegTable, RegDramCtlrLimit2, BFDctLimitReg2, 31, 0);
  _BF_DEF (NBRegTable, RegDramCtlrLimit2, BFDctIntLvEn2, 3, 0);
  REG_DEF (NBRegTable, RegDramCtlrLimit3, _FN (1, 0x21C));
  _BF_DEF (NBRegTable, RegDramCtlrLimit3, BFDctLimitReg3, 31, 0);
  _BF_DEF (NBRegTable, RegDramCtlrLimit3, BFDctIntLvEn3, 3, 0);

  // Define old bit field names for UMA Allocation function
  _BF_DEF (NBRegTable, RegDramCtlrLimit0, BFDctSelIntLvEn, 3, 0);   // equivalent to F1x204[DctIntLvEn]
  _BF_DEF (NBRegTable, RegDramCtlrBase1, BFDctSelBaseAddr, 31, 11); // equivalent to F1x208[DctBaseAddr]
  _BF_DEF (NBRegTable, RegDramCtlrBase1, BFDctSelHi, 6, 4);         // equivalent to F1x208[DctSel]

  REG_DEF (NBRegTable, RegDctHiAddrOffset0, _FN (1, 0x240));
  _BF_DEF (NBRegTable, RegDctHiAddrOffset0, BFDctHighAddressOffsetReg0, 31, 0);
  REG_DEF (NBRegTable, RegDctHiAddrOffset1, _FN (1, 0x244));
  _BF_DEF (NBRegTable, RegDctHiAddrOffset1, BFDctHighAddressOffsetReg1, 31, 0);
  REG_DEF (NBRegTable, RegDctHiAddrOffset2, _FN (1, 0x248));
  _BF_DEF (NBRegTable, RegDctHiAddrOffset2, BFDctHighAddressOffsetReg2, 31, 0);
  REG_DEF (NBRegTable, RegDctHiAddrOffset3, _FN (1, 0x24C));
  _BF_DEF (NBRegTable, RegDctHiAddrOffset3, BFDctHighAddressOffsetReg3, 31, 0);

  // ---------------------------------------------------------------------------
  // FUNCTION 2
  // ---------------------------------------------------------------------------
  REG_DEF (NBRegTable, RegCSBaseAddr0, _FN (2, 0x40));
  _BF_DEF (NBRegTable, RegCSBaseAddr0, BFCSBaseAddr0Reg, 31, 0);
  REG_DEF (NBRegTable, RegCSBaseAddr1, _FN (2, 0x44));
  _BF_DEF (NBRegTable, RegCSBaseAddr1, BFCSBaseAddr1Reg, 31, 0);
  REG_DEF (NBRegTable, RegCSBaseAddr2, _FN (2, 0x48));
  _BF_DEF (NBRegTable, RegCSBaseAddr2, BFCSBaseAddr2Reg, 31, 0);
  REG_DEF (NBRegTable, RegCSBaseAddr3, _FN (2, 0x4C));
  _BF_DEF (NBRegTable, RegCSBaseAddr3, BFCSBaseAddr3Reg, 31, 0);

  REG_DEF (NBRegTable, RegCSMask0, _FN (2, 0x60));
  _BF_DEF (NBRegTable, RegCSMask0, BFCSMask0Reg, 31, 0);
  _BF_DEF (NBRegTable, RegCSMask0, BFRankDef0, 1, 0);
  REG_DEF (NBRegTable, RegCSMask1, _FN (2, 0x64));
  _BF_DEF (NBRegTable, RegCSMask1, BFCSMask1Reg, 31, 0);
  _BF_DEF (NBRegTable, RegCSMask0, BFRankDef1, 1, 0);

  REG_DEF (NBRegTable, RegDramCtl, _FN (2, 0x78));
  _BF_DEF (NBRegTable, RegDramCtl, BFDramSprLock, 30, 30);
  _BF_DEF (NBRegTable, RegDramCtl, BFAddrCmdTriEn, 17, 17);
  _BF_DEF (NBRegTable, RegDramCtl, BFDramType, 10, 8);
  _BF_DEF (NBRegTable, RegDramCtl, BFPtrInitReq, 4, 4);
  _BF_DEF (NBRegTable, RegDramCtl, BFGsyncDis, 2, 2);
  _BF_DEF (NBRegTable, RegDramCtl, BFChanVal, 0, 0);

  REG_DEF (NBRegTable, RegDramInit, _FN (2, 0x7C));
  _BF_DEF (NBRegTable, RegDramInit, BFAssertCke, 28, 28);

  REG_DEF (NBRegTable, RegDramBankAddr, _FN (2, 0x80));
  _BF_DEF (NBRegTable, RegDramBankAddr, BFDramBankAddrReg, 15, 0);

  REG_DEF (NBRegTable, RegDramMRS, _FN (2, 0x84));
  _BF_DEF (NBRegTable, RegDramMRS, BFPchgPDModeSel,  23,  23);
  _BF_DEF (NBRegTable, RegDramMRS, BFBurstCtrl,  1,  0);

  REG_DEF (NBRegTable, RegDramTmgLo, _FN (2, 0x88));
  _BF_DEF (NBRegTable, RegDramTmgLo, BFMemClkDis, 29, 24);

  REG_DEF (NBRegTable, RegDramTmgHi, _FN (2, 0x8C));
  _BF_DEF (NBRegTable, RegDramTmgHi, BFDisAutoRefresh, 18, 18);

  REG_DEF (NBRegTable, RegDramConfigLo, _FN (2, 0x90));
  _BF_DEF (NBRegTable, RegDramConfigLo, BFIdleCycLimit, 31, 28);
  _BF_DEF (NBRegTable, RegDramConfigLo, BFDisDllShutdownSR, 27, 27);
  _BF_DEF (NBRegTable, RegDramConfigLo, BFPendRefPaybackS3En, 25, 25);
  _BF_DEF (NBRegTable, RegDramConfigLo, BFStagRefEn, 24, 24);
  _BF_DEF (NBRegTable, RegDramConfigLo, BFForceAutoPchg, 23, 23);
  _BF_DEF (NBRegTable, RegDramConfigLo, BFDynPageCloseEn, 20, 20);
  _BF_DEF (NBRegTable, RegDramConfigLo, BFDimmEccEn, 19, 19);
  _BF_DEF (NBRegTable, RegDramConfigLo, BFPendRefPayback, 18, 18);
  _BF_DEF (NBRegTable, RegDramConfigLo, BFEnterSelfRef, 17, 17);
  _BF_DEF (NBRegTable, RegDramConfigLo, BFUnBuffDimm, 16, 16);
  _BF_DEF (NBRegTable, RegDramConfigLo, BFX4Dimm, 15, 12);
  _BF_DEF (NBRegTable, RegDramConfigLo, BFWrCrcEn, 9, 9);
  _BF_DEF (NBRegTable, RegDramConfigLo, BFParEn, 8, 8);
  _BF_DEF (NBRegTable, RegDramConfigLo, BFDataScrambleEn, 7, 7);
  _BF_DEF (NBRegTable, RegDramConfigLo, BFExitSelfRef,  1,  1);

  REG_DEF (NBRegTable, RegDramConfigHi, _FN (2, 0x94));
  _BF_DEF (NBRegTable, RegDramConfigHi, BFDphyMemPsSelEn, 31, 31);
  _BF_DEF (NBRegTable, RegDramConfigHi, BFBankGroupSwap, 29, 29);
  _BF_DEF (NBRegTable, RegDramConfigHi, BFDcqBypassMax, 28, 24);
  _BF_DEF (NBRegTable, RegDramConfigHi, BFOn3RdCasStallMode, 23, 23);
  _BF_DEF (NBRegTable, RegDramConfigHi, BFBankSwizzleMode, 22, 22);
  _BF_DEF (NBRegTable, RegDramConfigHi, BFSlowAccessMode, 20, 20);
  _BF_DEF (NBRegTable, RegDramConfigHi, BFPowerDownMode, 16, 16);
  _BF_DEF (NBRegTable, RegDramConfigHi, BFPowerDownEn, 15, 15);
  _BF_DEF (NBRegTable, RegDramConfigHi, BFDisDramInterface, 14, 14);
  _BF_DEF (NBRegTable, RegDramConfigHi, BFZqcsInterval, 12, 10);
  _BF_DEF (NBRegTable, RegDramConfigHi, BFMemClkFreqVal, 7, 7);
  _BF_DEF (NBRegTable, RegDramConfigHi, BFMemClkFreq, 4, 0);

  REG_DEF (NBRegTable, RegDctAddlOffset, _FN (2, 0x98));
  REG_DEF (NBRegTable, RegDctAddlData, _FN (2, 0x9C));

  REG_DEF (NBRegTable, RegDctTempThrottle, _FN (2, 0xA4));
  _BF_DEF (NBRegTable, RegDctTempThrottle, BFCmdThrottleMode, 14, 12);
  _BF_DEF (NBRegTable, RegDctTempThrottle, BFBwCapEn,  11, 11);
  _BF_DEF (NBRegTable, RegDctTempThrottle, BFODTSEn,  8, 8);
  _BF_DEF (NBRegTable, RegDctTempThrottle, BFODTSDoubleRefreshRate,  0, 0);

  REG_DEF (NBRegTable, RegDramCtlrMisc2, _FN (2, 0xA8));
  _BF_DEF (NBRegTable, RegDramCtlrMisc2, BFPerRankTimingEn, 31, 31);
  _BF_DEF (NBRegTable, RegDramCtlrMisc2, BFRefChCmdMgtDis, 29, 29);
  _BF_DEF (NBRegTable, RegDramCtlrMisc2, BFFastSelfRefEntryDis, 28, 28);
  _BF_DEF (NBRegTable, RegDramCtlrMisc2, BFCSMux67, 27, 27);
  _BF_DEF (NBRegTable, RegDramCtlrMisc2, BFCSMux45, 26, 26);
  _BF_DEF (NBRegTable, RegDramCtlrMisc2, BFOppWrEnhDis, 23, 23);
  _BF_DEF (NBRegTable, RegDramCtlrMisc2, BFPrtlChPDEnhEn, 22, 22);
  _BF_DEF (NBRegTable, RegDramCtlrMisc2, BFAggrPDEn, 21, 21);
  _BF_DEF (NBRegTable, RegDramCtlrMisc2, BFBankSwap, 20, 20);
  _BF_DEF (NBRegTable, RegDramCtlrMisc2, BFPDPhyPSDis, 19, 19);
  _BF_DEF (NBRegTable, RegDramCtlrMisc2, BFSubMemclkRegDly, 5, 5);
  _BF_DEF (NBRegTable, RegDramCtlrMisc2, BFExtendedParityEn, 4, 4);
  _BF_DEF (NBRegTable, RegDramCtlrMisc2, BFEffArbDis, 0, 0);

  REG_DEF (NBRegTable, RegTraceBufferCtlr, _FN (2, 0xC0));
  _BF_DEF (NBRegTable, RegTraceBufferCtlr, BFTraceModeEn,  0,  0);

  REG_DEF (NBRegTable, RegDramCtlrSelLo, _FN (2, 0x110));
  _BF_DEF (NBRegTable, RegDramCtlrSelLo, BFMemCleared, 10, 10);
  _BF_DEF (NBRegTable, RegDramCtlrSelLo, BFMemClrBusy,  9,  9);
  _BF_DEF (NBRegTable, RegDramCtlrSelLo, BFDramEnabled,  8,  8);
  _BF_DEF (NBRegTable, RegDramCtlrSelLo, BFDctSelIntLvAddr,  7,  6);
  _BF_DEF (NBRegTable, RegDramCtlrSelLo, BFDctDatIntLv,  5,  5);
  _BF_DEF (NBRegTable, RegDramCtlrSelLo, BFMemClrInit,  3,  3);
  _BF_DEF (NBRegTable, RegDramCtlrSelLo, BFBankSwapAddr8En,  2,  2);

  REG_DEF (NBRegTable, RegDramCtlrSelHi, _FN (2, 0x114));
  _BF_DEF (NBRegTable, RegDramCtlrSelHi, BFDctSelIntLvAddrHi,  9,  9);

  REG_DEF (NBRegTable, RegMctCfgLo, _FN (2, 0x118));
  _BF_DEF (NBRegTable, RegMctCfgLo, BFLockDramCfg, 19, 19);
  _BF_DEF (NBRegTable, RegMctCfgLo, BFCC6SaveEn, 18, 18);

  REG_DEF (NBRegTable, RegMctCfgHi, _FN (2, 0x11C));
  _BF_DEF (NBRegTable, RegMctCfgHi, BFMctCfgHiReg, 31, 0);
  _BF_DEF (NBRegTable, RegMctCfgHi, BFPrefIoDis, 13, 13);
  _BF_DEF (NBRegTable, RegMctCfgHi, BFPrefCpuDis, 12, 12);

  REG_DEF (NBRegTable, RegDqMappingDimm0Reg0, _FN (2, 0x140));
  _BF_DEF (NBRegTable, RegDqMappingDimm0Reg0, BFDQMappingDimm0Reg0, 31, 0);
  REG_DEF (NBRegTable, RegDqMappingDimm0Reg1, _FN (2, 0x144));
  _BF_DEF (NBRegTable, RegDqMappingDimm0Reg1, BFDQMappingDimm0Reg1, 31, 0);
  REG_DEF (NBRegTable, RegDqMappingDimm0Reg2, _FN (2, 0x148));
  _BF_DEF (NBRegTable, RegDqMappingDimm0Reg2, BFDQMappingDimm0Reg2, 31, 0);
  REG_DEF (NBRegTable, RegDqMappingDimm0Reg3, _FN (2, 0x14C));
  _BF_DEF (NBRegTable, RegDqMappingDimm0Reg3, BFDQMappingDimm0Reg3, 31, 0);

  REG_DEF (NBRegTable, RegDqMappingDimm1Reg0, _FN (2, 0x150));
  _BF_DEF (NBRegTable, RegDqMappingDimm1Reg0, BFDQMappingDimm1Reg0, 31, 0);
  REG_DEF (NBRegTable, RegDqMappingDimm1Reg1, _FN (2, 0x154));
  _BF_DEF (NBRegTable, RegDqMappingDimm1Reg1, BFDQMappingDimm1Reg1, 31, 0);
  REG_DEF (NBRegTable, RegDqMappingDimm1Reg2, _FN (2, 0x158));
  _BF_DEF (NBRegTable, RegDqMappingDimm1Reg2, BFDQMappingDimm1Reg2, 31, 0);
  REG_DEF (NBRegTable, RegDqMappingDimm1Reg3, _FN (2, 0x15C));
  _BF_DEF (NBRegTable, RegDqMappingDimm1Reg3, BFDQMappingDimm1Reg3, 31, 0);

  REG_DEF (NBRegTable, RegDqMappingDimm2Reg0, _FN (2, 0x160));
  _BF_DEF (NBRegTable, RegDqMappingDimm2Reg0, BFDQMappingDimm2Reg0, 31, 0);
  REG_DEF (NBRegTable, RegDqMappingDimm2Reg1, _FN (2, 0x164));
  _BF_DEF (NBRegTable, RegDqMappingDimm2Reg1, BFDQMappingDimm2Reg1, 31, 0);
  REG_DEF (NBRegTable, RegDqMappingDimm2Reg2, _FN (2, 0x168));
  _BF_DEF (NBRegTable, RegDqMappingDimm2Reg2, BFDQMappingDimm2Reg2, 31, 0);
  REG_DEF (NBRegTable, RegDqMappingDimm2Reg3, _FN (2, 0x16C));
  _BF_DEF (NBRegTable, RegDqMappingDimm2Reg3, BFDQMappingDimm2Reg3, 31, 0);

  REG_DEF (NBRegTable, RegDqMappingDimm3Reg0, _FN (2, 0x170));
  _BF_DEF (NBRegTable, RegDqMappingDimm3Reg0, BFDQMappingDimm3Reg0, 31, 0);
  REG_DEF (NBRegTable, RegDqMappingDimm3Reg1, _FN (2, 0x174));
  _BF_DEF (NBRegTable, RegDqMappingDimm3Reg1, BFDQMappingDimm3Reg1, 31, 0);
  REG_DEF (NBRegTable, RegDqMappingDimm3Reg2, _FN (2, 0x178));
  _BF_DEF (NBRegTable, RegDqMappingDimm3Reg2, BFDQMappingDimm3Reg2, 31, 0);
  REG_DEF (NBRegTable, RegDqMappingDimm3Reg3, _FN (2, 0x17C));
  _BF_DEF (NBRegTable, RegDqMappingDimm3Reg3, BFDQMappingDimm3Reg3, 31, 0);

  REG_DEF (NBRegTable, RegExtMctCfgLo, _FN (2, 0x1B0));

  REG_DEF (NBRegTable, RegExtMctCfgHi, _FN (2, 0x1B4));
  _BF_DEF (NBRegTable, RegExtMctCfgHi, BFFlushWrOnS3StpGnt, 27, 27);
  _BF_DEF (NBRegTable, RegExtMctCfgHi, BFEnSplitMctDatBuffers, 26, 26);

  REG_DEF (NBRegTable, RegZqToCsMap, _FN (2, 0x1B8));
  REG_DEF (NBRegTable, RegCkeToCsMap, _FN (2, 0x1BC));

  REG_DEF (NBRegTable, RegScrubRateCtl, _FN (2, 0x1C8));
  _BF_DEF (NBRegTable, RegScrubRateCtl, BFDramScrub, 4,  0);

  REG_DEF (NBRegTable, RegDramNbPstate0, _FN (2, 0x1F0));
  _BF_DEF (NBRegTable, RegDramNbPstate0, BFMaxLatency0, 31, 22);
  _BF_DEF (NBRegTable, RegDramNbPstate0, BFDataTxFifoWrDly0, 18, 16);

  REG_DEF (NBRegTable, RegDramNbPstate1, _FN (2, 0x1F4));
  _BF_DEF (NBRegTable, RegDramNbPstate1, BFMaxLatency1, 31, 22);
  _BF_DEF (NBRegTable, RegDramNbPstate1, BFDataTxFifoWrDly1, 18, 16);

  REG_DEF (NBRegTable, RegDramNbPstate2, _FN (2, 0x1F8));
  _BF_DEF (NBRegTable, RegDramNbPstate2, BFMaxLatency2, 31, 22);
  _BF_DEF (NBRegTable, RegDramNbPstate2, BFDataTxFifoWrDly2, 18, 16);

  REG_DEF (NBRegTable, RegDramNbPstate3, _FN (2, 0x1FC));
  _BF_DEF (NBRegTable, RegDramNbPstate3, BFMaxLatency3, 31, 22);
  _BF_DEF (NBRegTable, RegDramNbPstate3, BFDataTxFifoWrDly3, 18, 16);

  REG_DEF (NBRegTable, RegDdrDramTmg0, _FN (2, 0x200));
  _BF_DEF (NBRegTable, RegDdrDramTmg0, BFTras, 29, 24);
  _BF_DEF (NBRegTable, RegDdrDramTmg0, BFTrp, 20, 16);
  _BF_DEF (NBRegTable, RegDdrDramTmg0, BFTrcd, 12, 8);
  _BF_DEF (NBRegTable, RegDdrDramTmg0, BFTcl, 4, 0);

  REG_DEF (NBRegTable, RegDdrDramTmg1, _FN (2, 0x204));
  _BF_DEF (NBRegTable, RegDdrDramTmg1, BFTrtp, 27, 24);
  _BF_DEF (NBRegTable, RegDdrDramTmg1, BFFourActWindow, 21, 16);
  _BF_DEF (NBRegTable, RegDdrDramTmg1, BFTrrdL, 15, 12);
  _BF_DEF (NBRegTable, RegDdrDramTmg1, BFTrrd, 11, 8);
  _BF_DEF (NBRegTable, RegDdrDramTmg1, BFTrc, 6, 0);

  REG_DEF (NBRegTable, RegDdrDramTmg2, _FN (2, 0x208));
  _BF_DEF (NBRegTable, RegDdrDramTmg2, BFTxs, 29, 20);
  _BF_DEF (NBRegTable, RegDdrDramTmg2, BFTref, 15, 0);

  REG_DEF (NBRegTable, RegDdrDramTmg3, _FN (2, 0x20C));
  _BF_DEF (NBRegTable, RegDdrDramTmg3, BFTdllk, 30, 20);
  _BF_DEF (NBRegTable, RegDdrDramTmg3, BFTwtrL, 15, 12);
  _BF_DEF (NBRegTable, RegDdrDramTmg3, BFTwtr, 11, 8);
  _BF_DEF (NBRegTable, RegDdrDramTmg3, BFTcwl, 4, 0);

  REG_DEF (NBRegTable, RegDdrDramTmg4, _FN (2, 0x214));
  _BF_DEF (NBRegTable, RegDdrDramTmg4, BFTwrwrSdSc, 19, 16);
  _BF_DEF (NBRegTable, RegDdrDramTmg4, BFTwrwrSdDc, 11, 8);
  _BF_DEF (NBRegTable, RegDdrDramTmg4, BFTwrwrDd, 3, 0);

  REG_DEF (NBRegTable, RegDdrDramTmg5, _FN (2, 0x218));
  _BF_DEF (NBRegTable, RegDdrDramTmg5, BFTrdrdBan, 31, 30);
  _BF_DEF (NBRegTable, RegDdrDramTmg5, BFTrdrdSdSc, 27, 24);
  _BF_DEF (NBRegTable, RegDdrDramTmg5, BFTrdrdSdDc, 19, 16);
  _BF_DEF (NBRegTable, RegDdrDramTmg5, BFTwrrd, 11, 8);
  _BF_DEF (NBRegTable, RegDdrDramTmg5, BFTrdrdDd, 3, 0);

  REG_DEF (NBRegTable, RegDdrDramTmg6, _FN (2, 0x21C));
  _BF_DEF (NBRegTable, RegDdrDramTmg6, BFTrdrdSdScL, 31, 28);
  _BF_DEF (NBRegTable, RegDdrDramTmg6, BFTwrwrSdScL, 27, 24);
  _BF_DEF (NBRegTable, RegDdrDramTmg6, BFTrwtWB, 20, 16);
  _BF_DEF (NBRegTable, RegDdrDramTmg6, BFTrwtTO, 12, 8);

  REG_DEF (NBRegTable, RegDdrDramTmg7, _FN (2, 0x220));
  _BF_DEF (NBRegTable, RegDdrDramTmg7, BFTmod, 13, 8);
  _BF_DEF (NBRegTable, RegDdrDramTmg7, BFTmrd, 3, 0);

  REG_DEF (NBRegTable, RegDdrDramTmg8, _FN (2, 0x224));
  _BF_DEF (NBRegTable, RegDdrDramTmg8, BFTrcpage, 31, 24);
  _BF_DEF (NBRegTable, RegDdrDramTmg8, BFTzqcs, 11, 8);
  _BF_DEF (NBRegTable, RegDdrDramTmg8, BFTzqoper, 4, 0);

  REG_DEF (NBRegTable, RegDdrDramTmg9, _FN (2, 0x228));
  _BF_DEF (NBRegTable, RegDdrDramTmg9, BFTstag3, 31, 24);
  _BF_DEF (NBRegTable, RegDdrDramTmg9, BFTstag2, 23, 16);
  _BF_DEF (NBRegTable, RegDdrDramTmg9, BFTstag1, 15, 8);
  _BF_DEF (NBRegTable, RegDdrDramTmg9, BFTstag0, 7, 0);

  REG_DEF (NBRegTable, RegDdrDramTmg10, _FN (2, 0x22C));
  _BF_DEF (NBRegTable, RegDdrDramTmg10, BFTvrefdq, 31, 24);
  _BF_DEF (NBRegTable, RegDdrDramTmg10, BFTclAdj, 12, 8);
  _BF_DEF (NBRegTable, RegDdrDramTmg10, BFTwr, 4, 0);

  REG_DEF (NBRegTable, RegPhyRODTCSLow , _FN (2, 0x230));
  REG_DEF (NBRegTable, RegPhyRODTCSHigh, _FN (2, 0x234));
  REG_DEF (NBRegTable, RegPhyWODTCSLow , _FN (2, 0x238));
  REG_DEF (NBRegTable, RegPhyWODTCSHigh, _FN (2, 0x23C));

  REG_DEF (NBRegTable, RegDdrDramOdtCtl, _FN (2, 0x240));
  _BF_DEF (NBRegTable, RegDdrDramOdtCtl, BFWrOdtOnDuration, 15, 12);
  _BF_DEF (NBRegTable, RegDdrDramOdtCtl, BFWrOdtTrnOnDly, 10, 8);
  _BF_DEF (NBRegTable, RegDdrDramOdtCtl, BFRdOdtOnDuration, 7, 4);
  _BF_DEF (NBRegTable, RegDdrDramOdtCtl, BFRdOdtTrnOnDly, 3, 0);

  REG_DEF (NBRegTable, RegDramCtlrMisc3, _FN (2, 0x244));
  _BF_DEF (NBRegTable, RegDramCtlrMisc3, BFPrtlChPDDynDly, 3, 0);

  REG_DEF (NBRegTable, RegDdrDramPwrMng0, _FN (2, 0x248));
  _BF_DEF (NBRegTable, RegDdrDramPwrMng0, BFAggrPDDelay, 29, 24);
  _BF_DEF (NBRegTable, RegDdrDramPwrMng0, BFPchgPDEnDelay, 21, 16);
  _BF_DEF (NBRegTable, RegDdrDramPwrMng0, BFTxpdll, 12, 8);
  _BF_DEF (NBRegTable, RegDdrDramPwrMng0, BFTxp, 3, 0);

  REG_DEF (NBRegTable, RegDdrDramPwrMng1, _FN (2, 0x24C));
  _BF_DEF (NBRegTable, RegDdrDramPwrMng1, BFTcksrx, 29, 24);
  _BF_DEF (NBRegTable, RegDdrDramPwrMng1, BFTcksre, 21, 16);
  _BF_DEF (NBRegTable, RegDdrDramPwrMng1, BFTckesr, 13, 8);
  _BF_DEF (NBRegTable, RegDdrDramPwrMng1, BFTcpded, 7, 4);
  _BF_DEF (NBRegTable, RegDdrDramPwrMng1, BFTpd, 3, 0);

  // ---------------------------------------------------------------------------
  // Reliable read/write
  // ---------------------------------------------------------------------------
  REG_DEF (NBRegTable, RegDramLpbkTrnCtl, _FN (2, 0x250));

  _BF_DEF (NBRegTable, RegDramLpbkTrnCtl, BFDataPatGenSel ,  20, 18);
  _BF_DEF (NBRegTable, RegDramLpbkTrnCtl, BFLfsrRollOver ,  13, 13);
  _BF_DEF (NBRegTable, RegDramLpbkTrnCtl, BFCmdSendInProg, 12,  12);
  _BF_DEF (NBRegTable, RegDramLpbkTrnCtl, BFSendCmd, 11,  11);
  _BF_DEF (NBRegTable, RegDramLpbkTrnCtl, BFTestStatus, 10,  10);
  _BF_DEF (NBRegTable, RegDramLpbkTrnCtl, BFCmdTgt,  9,   8);
  _BF_DEF (NBRegTable, RegDramLpbkTrnCtl, BFCmdType,  7,   5);
  _BF_DEF (NBRegTable, RegDramLpbkTrnCtl, BFStopOnErr,  4,   4);
  _BF_DEF (NBRegTable, RegDramLpbkTrnCtl, BFResetAllErr,  3,   3);
  _BF_DEF (NBRegTable, RegDramLpbkTrnCtl, BFCmdTestEnable,  2,   2);

  REG_DEF (NBRegTable, RegTargetBBase, _FN (2, 0x258));
  _BF_DEF (NBRegTable, RegTargetBBase, BFTgtChipSelectB,  26, 24);
  _BF_DEF (NBRegTable, RegTargetBBase, BFTgtBankB,  23, 20);
  _BF_DEF (NBRegTable, RegTargetBBase, BFTgtAddressB,   9,  0);

  REG_DEF (NBRegTable, RegTargetABase, _FN (2, 0x254));
  _BF_DEF (NBRegTable, RegTargetABase, BFTgtChipSelectA,  26, 24);
  _BF_DEF (NBRegTable, RegTargetABase, BFTgtBankA,  23, 20);
  _BF_DEF (NBRegTable, RegTargetABase, BFTgtAddressA,   9,  0);

  REG_DEF (NBRegTable, RegDramCmd0, _FN (2, 0x25C));
  _BF_DEF (NBRegTable, RegDramCmd0, BFBubbleCnt2,  31, 22);
  _BF_DEF (NBRegTable, RegDramCmd0, BFBubbleCnt,  21, 12);
  _BF_DEF (NBRegTable, RegDramCmd0, BFCmdStreamLen,   7,  0);

  REG_DEF (NBRegTable, RegDramCmd1, _FN (2, 0x260));
  _BF_DEF (NBRegTable, RegDramCmd1, BFCmdCount,  20,  0);

  REG_DEF (NBRegTable, RegDramStatus1, _FN (2, 0x268));
  _BF_DEF (NBRegTable, RegDramStatus1, BFNibbleErrSts, 17,  0);

  REG_DEF (NBRegTable, RegDramPRBS, _FN (2, 0x270));
  _BF_DEF (NBRegTable, RegDramPRBS, BFDataPrbsSeed, 18,   0);

  REG_DEF (NBRegTable, RegDramDqMaskLo, _FN (2, 0x274));
  _BF_DEF (NBRegTable, RegDramDqMaskLo, BFDramDqMaskLow , 31,  0);

  REG_DEF (NBRegTable, RegDramDqMaskHi, _FN (2, 0x278));
  _BF_DEF (NBRegTable, RegDramDqMaskHi, BFDramDqMaskHigh, 31,  0);

  REG_DEF (NBRegTable, RegDramEccMask, _FN (2, 0x27C));
  _BF_DEF (NBRegTable, RegDramEccMask, BFDramEccMask, 7,  0);

  REG_DEF (NBRegTable, RegDramCmd2, _FN (2, 0x28C));
  _BF_DEF (NBRegTable, RegDramCmd2, BFSendActCmd, 31, 31);
  _BF_DEF (NBRegTable, RegDramCmd2, BFSendPchgCmd, 30, 30);
  _BF_DEF (NBRegTable, RegDramCmd2, BFCmdChipSelect, 29, 22);
  _BF_DEF (NBRegTable, RegDramCmd2, BFCmdBank, 21, 18);
  _BF_DEF (NBRegTable, RegDramCmd2, BFCmdAddress, 17,  0);

  REG_DEF (NBRegTable, RegDQErrLo, _FN (2, 0x294));
  _BF_DEF (NBRegTable, RegDQErrLo, BFDQErrLow, 31,  0);

  REG_DEF (NBRegTable, RegDQErrHi, _FN (2, 0x298));
  _BF_DEF (NBRegTable, RegDQErrHi, BFDQErrHigh, 31,  0);

  REG_DEF (NBRegTable, RegDQErrEcc, _FN (2, 0x29C));
  _BF_DEF (NBRegTable, RegDQErrEcc, BFEccErr, 7,  0);

  // ---------------------------------------------------------------------------
  //
  // ---------------------------------------------------------------------------

  REG_DEF (NBRegTable, RegDdrDramTmg12, _FN (2, 0x2A0));
  _BF_DEF (NBRegTable, RegDdrDramTmg12, BFTrfc1, 26, 16);
  _BF_DEF (NBRegTable, RegDdrDramTmg12, BFTrfc0, 10, 0);

  REG_DEF (NBRegTable, RegDdrDramTmg13, _FN (2, 0x2A4));
  _BF_DEF (NBRegTable, RegDdrDramTmg13, BFTrfc2, 26, 16);
  _BF_DEF (NBRegTable, RegDdrDramTmg13, BFTrfc3, 10, 0);

  REG_DEF (NBRegTable, RegMemPsCtlSts, _FN (2, 0x2E0));
  _BF_DEF (NBRegTable, RegMemPsCtlSts, BFFastMstateDis, 30, 30);
  _BF_DEF (NBRegTable, RegMemPsCtlSts, BFM1MemClkFreq, 28, 24);
  _BF_DEF (NBRegTable, RegMemPsCtlSts, BFMxMrsEn, 23, 16);
  _BF_DEF (NBRegTable, RegMemPsCtlSts, BFVrefTrainMrsEn, 5, 5);
  _BF_DEF (NBRegTable, RegMemPsCtlSts, BFVrefTrain3Mrs6, 4, 4);

  REG_DEF (NBRegTable, RegMrsBuf0, _FN (2, 0x2E8));
  _BF_DEF (NBRegTable, RegMrsBuf0, BFMxMr0, 15, 0);
  _BF_DEF (NBRegTable, RegMrsBuf0, BFMxMr1, 31, 16);

  REG_DEF (NBRegTable, RegMrsBuf1, _FN (2, 0x2EC));
  _BF_DEF (NBRegTable, RegMrsBuf1, BFMxMr2, 15, 0);
  _BF_DEF (NBRegTable, RegMrsBuf1, BFMxMr3, 31, 16);

  REG_DEF (NBRegTable, RegMrsBuf2, _FN (2, 0x2F0));
  _BF_DEF (NBRegTable, RegMrsBuf2, BFMxMr4, 15, 0);
  _BF_DEF (NBRegTable, RegMrsBuf2, BFMxMr5, 31, 16);

  REG_DEF (NBRegTable, RegMrsBuf3, _FN (2, 0x2F4));
  _BF_DEF (NBRegTable, RegMrsBuf3, BFMxMr6, 15, 0);

  // ---------------------------------------------------------------------------
  // MULTIPLE MEMORY PSTATE BITFIELD
  // ---------------------------------------------------------------------------
  MULTI_MPSTATE_COPY_BF (NBRegTable, BFTras);
  MULTI_MPSTATE_COPY_BF (NBRegTable, BFTrp);
  MULTI_MPSTATE_COPY_BF (NBRegTable, BFTrcd);
  MULTI_MPSTATE_COPY_BF (NBRegTable, BFTcl);
  MULTI_MPSTATE_COPY_BF (NBRegTable, BFTrtp);
  MULTI_MPSTATE_COPY_BF (NBRegTable, BFFourActWindow);
  MULTI_MPSTATE_COPY_BF (NBRegTable, BFTrrdL);
  MULTI_MPSTATE_COPY_BF (NBRegTable, BFTrrd);
  MULTI_MPSTATE_COPY_BF (NBRegTable, BFTrc);
  MULTI_MPSTATE_COPY_BF (NBRegTable, BFTxs);
  MULTI_MPSTATE_COPY_BF (NBRegTable, BFTref);
  MULTI_MPSTATE_COPY_BF (NBRegTable, BFTdllk);
  MULTI_MPSTATE_COPY_BF (NBRegTable, BFTrfc0);
  MULTI_MPSTATE_COPY_BF (NBRegTable, BFTrfc1);
  MULTI_MPSTATE_COPY_BF (NBRegTable, BFTrfc2);
  MULTI_MPSTATE_COPY_BF (NBRegTable, BFTrfc3);
  MULTI_MPSTATE_COPY_BF (NBRegTable, BFTwtrL);
  MULTI_MPSTATE_COPY_BF (NBRegTable, BFTwtr);
  MULTI_MPSTATE_COPY_BF (NBRegTable, BFTcwl);
  MULTI_MPSTATE_COPY_BF (NBRegTable, BFTwrwrSdSc);
  MULTI_MPSTATE_COPY_BF (NBRegTable, BFTwrwrSdScL);
  MULTI_MPSTATE_COPY_BF (NBRegTable, BFTwrwrSdDc);
  MULTI_MPSTATE_COPY_BF (NBRegTable, BFTwrwrDd);
  MULTI_MPSTATE_COPY_BF (NBRegTable, BFTrdrdBan);
  MULTI_MPSTATE_COPY_BF (NBRegTable, BFTrdrdSdSc);
  MULTI_MPSTATE_COPY_BF (NBRegTable, BFTrdrdSdScL);
  MULTI_MPSTATE_COPY_BF (NBRegTable, BFTrdrdSdDc);
  MULTI_MPSTATE_COPY_BF (NBRegTable, BFTwrrd);
  MULTI_MPSTATE_COPY_BF (NBRegTable, BFTrdrdDd);
  MULTI_MPSTATE_COPY_BF (NBRegTable, BFTrwtWB);
  MULTI_MPSTATE_COPY_BF (NBRegTable, BFTrwtTO);
  MULTI_MPSTATE_COPY_BF (NBRegTable, BFTvrefdq);
  MULTI_MPSTATE_COPY_BF (NBRegTable, BFTclAdj);
  MULTI_MPSTATE_COPY_BF (NBRegTable, BFTwr);
  MULTI_MPSTATE_COPY_BF (NBRegTable, BFWrOdtOnDuration);
  MULTI_MPSTATE_COPY_BF (NBRegTable, BFWrOdtTrnOnDly);
  MULTI_MPSTATE_COPY_BF (NBRegTable, BFRdOdtOnDuration);
  MULTI_MPSTATE_COPY_BF (NBRegTable, BFRdOdtTrnOnDly);
  MULTI_MPSTATE_COPY_BF (NBRegTable, BFAggrPDDelay);
  MULTI_MPSTATE_COPY_BF (NBRegTable, BFPchgPDEnDelay);
  MULTI_MPSTATE_COPY_BF (NBRegTable, BFTxpdll);
  MULTI_MPSTATE_COPY_BF (NBRegTable, BFTxp);
  MULTI_MPSTATE_COPY_BF (NBRegTable, BFMxMr0);
  MULTI_MPSTATE_COPY_BF (NBRegTable, BFMxMr1);
  MULTI_MPSTATE_COPY_BF (NBRegTable, BFMxMr2);
  MULTI_MPSTATE_COPY_BF (NBRegTable, BFMxMr3);
  MULTI_MPSTATE_COPY_BF (NBRegTable, BFMxMr4);
  MULTI_MPSTATE_COPY_BF (NBRegTable, BFMxMr5);
  MULTI_MPSTATE_COPY_BF (NBRegTable, BFMxMr6);

  // ---------------------------------------------------------------------------
  // FUNCTION 3
  // ---------------------------------------------------------------------------
  REG_DEF (NBRegTable, RegMcaNbCtl, _FN (3, 0x40));
  _BF_DEF (NBRegTable, RegMcaNbCtl, BFMcaNbCtlReg, 31,  0);

  REG_DEF (NBRegTable, RegMcaNbCfg, _FN (3, 0x44));
  _BF_DEF (NBRegTable, RegMcaNbCfg, BFSyncOnUcEccEn, 2,  2);
  _BF_DEF (NBRegTable, RegMcaNbCfg, BFDramEccEn, 22,  22);

  REG_DEF (NBRegTable, RegDramScrubAddrLo, _FN (3, 0x5C));
  _BF_DEF (NBRegTable, RegDramScrubAddrLo, BFScrubReDirEn, 0,  0);
  _BF_DEF (NBRegTable, RegDramScrubAddrLo, BFScrubAddrLoReg, 31,  0);

  REG_DEF (NBRegTable, RegDramScrubAddrHi, _FN (3, 0x60));
  _BF_DEF (NBRegTable, RegDramScrubAddrHi, BFScrubAddrHiReg, 31,  0);

  REG_DEF (NBRegTable, RegNbCfg1Lo, _FN (3, 0x88));
  _BF_DEF (NBRegTable, RegNbCfg1Lo, BFDisDramScrub, 27,  27);

  REG_DEF (NBRegTable, RegNbCfg1Hi, _FN (3, 0x8C));
  _BF_DEF (NBRegTable, RegNbCfg1Hi, BFDisDatMsk, 4,  4);

  REG_DEF (NBRegTable, RegNbCap, _FN (3, 0xE8));
  _BF_DEF (NBRegTable, RegNbCap, BFEccCapable, 3,  3);

  REG_DEF (NBRegTable, RegCpuid, _FN (3, 0xFC));
  _BF_DEF (NBRegTable, RegCpuid, BFBaseModel, 7,  4);
  _BF_DEF (NBRegTable, RegCpuid, BFExtModel, 19, 16);

  REG_DEF (NBRegTable, RegExtMcaNbCfg, _FN (3, 0x180));
  _BF_DEF (NBRegTable, RegExtMcaNbCfg, BFEccSymbolSize, 25,  25);

  REG_DEF (NBRegTable, RegProductInformationRegister1, _FN (3, 0x1FC));
  _BF_DEF (NBRegTable, RegProductInformationRegister1, BFVddpVddrLowVoltSupp, 21,  21);

  REG_DEF (NBRegTable, RegDctAndFusePowerGateCtrl, _FN (3, 0x2B4));
  _BF_DEF (NBRegTable, RegDctAndFusePowerGateCtrl, BFDctClkGateEn, 9,  8);
  _BF_DEF (NBRegTable, RegDctAndFusePowerGateCtrl, BFDctPwrGateEn, 1,  0);

  // ---------------------------------------------------------------------------
  // FUNCTION 5
  // ---------------------------------------------------------------------------
  REG_DEF (NBRegTable, RegNbCap2, _FN (5, 0x84));
  _BF_DEF (NBRegTable, RegNbCap2, BFDdrMaxRate,  20, 16);
  _BF_DEF (NBRegTable, RegNbCap2, BFDctEn, 15, 12);

  REG_DEF (NBRegTable, RegNbPstate0, _FN (5, 0x160));
  _BF_DEF (NBRegTable, RegNbPstate0, BFNbVid0Hi, 21, 21);
  _BF_DEF (NBRegTable, RegNbPstate0, BFMemPstate0, 18, 18);
  _BF_DEF (NBRegTable, RegNbPstate0, BFNbVid0, 16, 10);
  _BF_DEF (NBRegTable, RegNbPstate0, BFNbDid0, 7, 7);
  _BF_DEF (NBRegTable, RegNbPstate0, BFNbFid0, 6, 1);
  REG_DEF (NBRegTable, RegNbPstate1, _FN (5, 0x164));
  _BF_DEF (NBRegTable, RegNbPstate1, BFNbVid1Hi, 21, 21);
  _BF_DEF (NBRegTable, RegNbPstate1, BFMemPstate1, 18, 18);
  _BF_DEF (NBRegTable, RegNbPstate1, BFNbVid1, 16, 10);
  _BF_DEF (NBRegTable, RegNbPstate1, BFNbDid1, 7, 7);
  _BF_DEF (NBRegTable, RegNbPstate1, BFNbFid1, 6, 1);
  REG_DEF (NBRegTable, RegNbPstate2, _FN (5, 0x168));
  _BF_DEF (NBRegTable, RegNbPstate2, BFNbVid2Hi, 21, 21);
  _BF_DEF (NBRegTable, RegNbPstate2, BFMemPstate2, 18, 18);
  _BF_DEF (NBRegTable, RegNbPstate2, BFNbVid2, 16, 10);
  _BF_DEF (NBRegTable, RegNbPstate2, BFNbDid2, 7, 7);
  _BF_DEF (NBRegTable, RegNbPstate2, BFNbFid2, 6, 1);
  REG_DEF (NBRegTable, RegNbPstate3, _FN (5, 0x16C));
  _BF_DEF (NBRegTable, RegNbPstate3, BFNbVid3Hi, 21, 21);
  _BF_DEF (NBRegTable, RegNbPstate3, BFMemPstate3, 18, 18);
  _BF_DEF (NBRegTable, RegNbPstate3, BFNbVid3, 16, 10);
  _BF_DEF (NBRegTable, RegNbPstate3, BFNbDid3, 7, 7);
  _BF_DEF (NBRegTable, RegNbPstate3, BFNbFid3, 6, 1);

  REG_DEF (NBRegTable, RegNbPstateCtl, _FN (5, 0x170));
  _BF_DEF (NBRegTable, RegNbPstateCtl, BFNbPstateCtlReg, 31, 0);
  _BF_DEF (NBRegTable, RegNbPstateCtl, BFMemPstateDis, 31, 31);
  _BF_DEF (NBRegTable, RegNbPstateCtl, BFSwNbPstateLoDis, 14, 14);
  _BF_DEF (NBRegTable, RegNbPstateCtl, BFNbPstateHi,  7,  6);
  _BF_DEF (NBRegTable, RegNbPstateCtl, BFNbPstateLo,  4,  3);
  _BF_DEF (NBRegTable, RegNbPstateCtl, BFNbPstateMaxVal,  1,  0);

  REG_DEF (NBRegTable, RegNbPstateStatus, _FN (5, 0x174));
  _BF_DEF (NBRegTable, RegNbPstateStatus, BFNbPstateReqBusy, 31, 31);
  _BF_DEF (NBRegTable, RegNbPstateStatus, BFCurMemPstate, 24, 24);
  _BF_DEF (NBRegTable, RegNbPstateStatus, BFCurNbVidHi, 23, 23);
  _BF_DEF (NBRegTable, RegNbPstateStatus, BFCurNbPstateLo, 22, 22);
  _BF_DEF (NBRegTable, RegNbPstateStatus, BFCurNbPstate, 20, 19);
  _BF_DEF (NBRegTable, RegNbPstateStatus, BFCurNbVid, 18, 12);
  _BF_DEF (NBRegTable, RegNbPstateStatus, BFCurNbDid, 9, 9);
  _BF_DEF (NBRegTable, RegNbPstateStatus, BFCurNbFid, 8, 3);
  _BF_DEF (NBRegTable, RegNbPstateStatus, BFNbPstateDis,  0,  0);

  REG_DEF (NBRegTable, RegNbCfg7, _FN (5, 0x9C));
  _BF_DEF (NBRegTable, RegNbCfg7, BFDisMctHldRegSkidBuffer, 6, 6);

  REG_DEF (NBRegTable, RegMctToOnion3BufferCount, _FN (5, 0x228));
  _BF_DEF (NBRegTable, RegMctToOnion3BufferCount, BFFreeOpbdDcqStallThresh, 24, 21);

  // ---------------------------------------------------------------------------
  //
  // DCT PHY REGISTERS
  //
  // ---------------------------------------------------------------------------
  //
  // SW Broadcast:
  //    - DCT PHY registers can have multiple instances per register address.
  //    - BIOS must read-mod-write to all instances to change a bit field.
  //    - For convenience, SetBitField will do SW broadcast by default. The broadcast fields
  //      must be defined with the upper bound of the range as show in below example.
  //    - When SW broadcast is not desired, a particular macro must be used to specify which
  //      field to skip broadcast and pass in the new index of that field. See examples.
  //    - GetBitField always issues single read (no SW broadcast)
  //
  // For example:
  //    D18F2x9C_x0[3,1:0][F,7:0]1_[F,B:0]04A
  //                  |      |        |
  //                  |      |        |
  //                  |      |        +-----------+
  //                  |      +------------------+ |
  //                  +------------------------+| |
  //                                           || |
  //                                           vv v
  //    REG_DEF (NBRegTable, RegDqDqsRxCtl, 0x0171B04A);
  //    _BF_DEF (NBRegTable, RegDqDqsRxCtl, BFMajorMode, 6, 4);
  //
  //    GetBitField (RegDqDqsRxCtl);                   // no broadcast due to register read
  //    SetBitField (RegDqDqsRxCtl, 1);                // broadcast to all instances of that register, with read-mod-write
  //    SetBitField (BFMajorMode, 1);                  // broadcast to all instances of DqDqsRxCtl
  //    SetBitField (PER_MEM_PS (0, BFMajorMode), 1);  // partially broadcast to MP0 instances
  //    SetBitField (SW_BC_DIS (BFMajorMode), 1);      // single write to 0x0171B04A
  //
  REG_DEF (NBRegTable, RegPllMemPs0, 0x00020000);
  REG_DEF (NBRegTable, RegPllMemPs1, 0x00020001);

  REG_DEF (NBRegTable, RegPwrStateCmd, 0x0002000B);

  REG_DEF (NBRegTable, RegGlobalCtl, 0x0002000E);
  _BF_DEF (NBRegTable, RegGlobalCtl, BFPhyDisable,  1,  1);
  _BF_DEF (NBRegTable, RegGlobalCtl, BFD4ModeMByte,  0,  0);

  REG_DEF (NBRegTable, RegMemResetCtl, 0x00020060);
  _BF_DEF (NBRegTable, RegMemResetCtl, BFMemResetL,  0,  0);

  REG_DEF (NBRegTable, RegCalRate, 0x00020088);
  _BF_DEF (NBRegTable, RegCalRate, BFCalRun,  4,  4);
  _BF_DEF (NBRegTable, RegCalRate, BFCalOnce, 5,  5);
  _BF_DEF (NBRegTable, RegCalRate, BFCalInitMode, 7,  7);

  REG_DEF (NBRegTable, RegCalBusy, 0x00020097);

  REG_DEF (NBRegTable, RegGlobalCtlSlaveAbyte, 0x00F0000E);
  _BF_DEF (NBRegTable, RegGlobalCtlSlaveAbyte, BFD4ModeAbyte,  0,  0);

  REG_DEF (NBRegTable, RegGlobalCtlSlaveDbyte, 0x0081000E);
  _BF_DEF (NBRegTable, RegGlobalCtlSlaveDbyte, BFD4ModeDbyte,  0,  0);

  REG_DEF (NBRegTable, RegPmuClkDiv, 0x01020080);
  _BF_DEF (NBRegTable, RegPmuClkDiv, BFPMUClkDiv, 3, 0);

  REG_DEF (NBRegTable, RegDisCal, 0x00020087);
  _BF_DEF (NBRegTable, RegDisCal, BFDisAutoComp,  1,  1);
  _BF_DEF (NBRegTable, RegDisCal, BFDisPredriverCal,  0,  0);

  REG_DEF (NBRegTable, RegPllRegWaitTime, 0x00020093);
  REG_DEF (NBRegTable, RegPllLockTime, 0x00020089);

  REG_DEF (NBRegTable, RegCalMisc2, 0x00020098);
  _BF_DEF (NBRegTable, RegCalMisc2, BFCalD4D3, 13, 13);

  REG_DEF (NBRegTable, RegMbProtocolShadow, 0x00020004);
  _BF_DEF (NBRegTable, RegMbProtocolShadow, BFUsRdy, 1, 1);
  _BF_DEF (NBRegTable, RegMbProtocolShadow, BFUs2Rdy, 2, 2);

  REG_DEF (NBRegTable, RegUsMbMsg, 0x00020032);
  _BF_DEF (NBRegTable, RegUsMbMsg, BFUsMessage, 15, 0);

  REG_DEF (NBRegTable, RegUsMbProtocol, 0x00020033);
  _BF_DEF (NBRegTable, RegUsMbProtocol, BFRdy, 0, 0);

  REG_DEF (NBRegTable, RegUsMb2Msg, 0x00020034);
  _BF_DEF (NBRegTable, RegUsMb2Msg, BFUs2Message, 15, 0);

  REG_DEF (NBRegTable, RegUsMb2Protocol, 0x00020035);
  _BF_DEF (NBRegTable, RegUsMb2Protocol, BFRdy2, 0, 0);

  REG_DEF (NBRegTable, RegPmuRst, 0x00020099);
  _BF_DEF (NBRegTable, RegPmuRst, BFPmuSramSd, 6, 6);
  _BF_DEF (NBRegTable, RegPmuRst, BFPmuReset, 3, 3);
  _BF_DEF (NBRegTable, RegPmuRst, BFPmuStall, 0, 0);

  REG_DEF (NBRegTable, RegMisc5, 0x0002005D);

  REG_DEF (NBRegTable, RegSramMsgBlk, 0x00050000);

  REG_DEF (NBRegTable, RegPhyClkCtl, 0x00FF000D);
  _BF_DEF (NBRegTable, RegPhyClkCtl, BFPhyClkCtl, 0, 0);

  REG_DEF (NBRegTable, RegAbyteDqDqsRcvCntrl1, 0x00F0F04A);
  _BF_DEF (NBRegTable, RegAbyteDqDqsRcvCntrl1, BFMajorModeAbyte, 7, 5);
  _BF_DEF (NBRegTable, RegAbyteDqDqsRcvCntrl1, BFPowerDownRcvrAbyte, 8, 8);
  _BF_DEF (NBRegTable, RegAbyteDqDqsRcvCntrl1, BFAVoltageLevel, 12, 10);

  REG_DEF (NBRegTable, RegDbyteDqDqsRcvCntrl2, 0x01F1F043);
  _BF_DEF (NBRegTable, RegDbyteDqDqsRcvCntrl2, BFMajorModeDbyte, 2, 0);
  _BF_DEF (NBRegTable, RegDbyteDqDqsRcvCntrl2, BFExtVrefRange, 4, 4);

  REG_DEF (NBRegTable, RegAcsmByteCntrl0, 0x000400F0);
  _BF_DEF (NBRegTable, RegAcsmByteCntrl0, BFAcsmDdrMode, 1, 1);

  REG_DEF (NBRegTable, RegDbyteDqDqsRcvCntrl1, 0x0081B04A);
  _BF_DEF (NBRegTable, RegDbyteDqDqsRcvCntrl1, BFPowerDownRcvrDbyte, 8, 8);
  _BF_DEF (NBRegTable, RegDbyteDqDqsRcvCntrl1, BFVoltageLevel, 12, 10);
  REG_DEF (NBRegTable, RegDbyteDqDqsRcvCntrl1Bcst, 0x00F1F04A);

  REG_DEF (NBRegTable, RegRdPtrInitVal, 0x00F0F82E);     // HW broadcast

  REG_DEF (NBRegTable, RegDataRdPtrInitVal, 0x00F1082E); // HW broadcast

  REG_DEF (NBRegTable, RegTxImpedance, 0x03FFF041);      // HW broadcast

  REG_DEF (NBRegTable, RegCadTxImpedance, 0x0130B041);   // CAD chip to pad translation
  REG_DEF (NBRegTable, RegCalTxImpedance, 0x0030B04E);   // CAL chip to pad translation

  REG_DEF (NBRegTable, RegRxCtl1, 0x00FFF04A);           // HW broadcast
  REG_DEF (NBRegTable, RegFAF04A, 0x00FAF04A);           // HW broadcast

  REG_DEF (NBRegTable, RegDataRdPtrOffset, 0x01F10028);  // HW broadcast

  REG_DEF (NBRegTable, RegDByteCtrl1, 0x03F10010);       // HW broadcast

  REG_DEF (NBRegTable, RegDataTxImpedance, 0x0181B041);  // Data chip to pad translation
  REG_DEF (NBRegTable, RegDataTxImpedanceBcst, 0x01F1F041);

  REG_DEF (NBRegTable, RegDataRxImpedance, 0x0181B04D);  // Data chip to pad translation
  REG_DEF (NBRegTable, RegDataRxImpedanceBcst, 0x01F1F04D);

  REG_DEF (NBRegTable, RegCadTxSlewRate, 0x0030B05F);    // CAD chip to pad translation

  REG_DEF (NBRegTable, RegDataTxSlewRate, 0x0081B05F);   // Data chip to pad translation
  REG_DEF (NBRegTable, RegDataTxSlewRateBcst, 0x00F1F05F);   // Data chip to pad translation broadcast

  REG_DEF (NBRegTable, RegHighAddrMode, 0x00F00009);   // High Addr Mode

  REG_DEF (NBRegTable, RegAcsmOdtCtrl0, 0x00F400E0);
  REG_DEF (NBRegTable, RegAcsmOdtCtrl1, 0x00F400E1);
  REG_DEF (NBRegTable, RegAcsmOdtCtrl2, 0x00F400E2);
  REG_DEF (NBRegTable, RegAcsmOdtCtrl3, 0x00F400E3);
  REG_DEF (NBRegTable, RegAcsmOdtCtrl4, 0x00F400E4);
  REG_DEF (NBRegTable, RegAcsmOdtCtrl5, 0x00F400E5);
  REG_DEF (NBRegTable, RegAcsmOdtCtrl6, 0x00F400E6);
  REG_DEF (NBRegTable, RegAcsmOdtCtrl7, 0x00F400E7);

  REG_DEF (NBRegTable, RegVrefByteAbyte, 0x00F00015);
  REG_DEF (NBRegTable, RegVrefByteDbyte, 0x00F10015);
  REG_DEF (NBRegTable, RegVrefByteMaster, 0x00F20015);

  REG_DEF (NBRegTable, RegProcOdtTmg, 0x00F10016);      // HW broadcast

  // Registers trained by PMU
  REG_DEF (NBRegTable, RegDataRxDly, 0x01813380);
  REG_DEF (NBRegTable, RegDataTxDly, 0x01813381);

  REG_DEF (NBRegTable, RegDataVrefHspeed, 0x0181B044);
  _BF_DEF (NBRegTable, RegDataVrefHspeed, BFVrefHspeed, 6, 0);

  REG_DEF (NBRegTable, RegDataTxEqHiImp, 0x0181B046);
  _BF_DEF (NBRegTable, RegDataTxEqHiImp, BFEQStrenHiP, 6, 4);

  REG_DEF (NBRegTable, RegDataTxEqLoImp, 0x0181B047);
  REG_DEF (NBRegTable, RegDataTxEqBoostImp, 0x0181B048);

  REG_DEF (NBRegTable, RegDataDllPstateConfigBcst, 0x00F10F79);

  REG_DEF (NBRegTable, RegDllPstateConfigBcst, 0x00F00F79);

  REG_DEF (NBRegTable, RegRdPtrOffsetCad0Group0, 0x00000028);
  REG_DEF (NBRegTable, RegRdPtrOffsetCad0Group1, 0x00001028);
  REG_DEF (NBRegTable, RegRdPtrOffsetCad0Group2, 0x00002028);
  REG_DEF (NBRegTable, RegRdPtrOffsetCad0Group3, 0x00003028);
  REG_DEF (NBRegTable, RegRdPtrOffsetCad1Group0, 0x00100028);
  REG_DEF (NBRegTable, RegRdPtrOffsetCad1Group1, 0x00101028);
  REG_DEF (NBRegTable, RegRdPtrOffsetCad1Group2, 0x00102028);
  REG_DEF (NBRegTable, RegRdPtrOffsetCad1Group3, 0x00103028);
  REG_DEF (NBRegTable, RegRdPtrOffsetCad2Group0, 0x00200028);
  REG_DEF (NBRegTable, RegRdPtrOffsetCad2Group1, 0x00201028);
  REG_DEF (NBRegTable, RegRdPtrOffsetCad2Group2, 0x00202028);
  REG_DEF (NBRegTable, RegRdPtrOffsetCad2Group3, 0x00203028);
  REG_DEF (NBRegTable, RegRdPtrOffsetCad3Group0, 0x00300028);
  REG_DEF (NBRegTable, RegRdPtrOffsetCad3Group1, 0x00301028);
  REG_DEF (NBRegTable, RegRdPtrOffsetCad3Group2, 0x00302028);
  REG_DEF (NBRegTable, RegRdPtrOffsetCad3Group3, 0x00303028);

  REG_DEF (NBRegTable, RegDataRdPtrOffset0, 0x00010028);
  REG_DEF (NBRegTable, RegDataRdPtrOffset1, 0x00110028);
  REG_DEF (NBRegTable, RegDataRdPtrOffset2, 0x00210028);
  REG_DEF (NBRegTable, RegDataRdPtrOffset3, 0x00310028);
  REG_DEF (NBRegTable, RegDataRdPtrOffset4, 0x00410028);
  REG_DEF (NBRegTable, RegDataRdPtrOffset5, 0x00510028);
  REG_DEF (NBRegTable, RegDataRdPtrOffset6, 0x00610028);
  REG_DEF (NBRegTable, RegDataRdPtrOffset7, 0x00710028);
  REG_DEF (NBRegTable, RegDataRdPtrOffset8, 0x00810028);

  REG_DEF (NBRegTable, RegTxDlyCad0Group0, 0x00000081);
  REG_DEF (NBRegTable, RegTxDlyCad0Group1, 0x00001081);
  REG_DEF (NBRegTable, RegTxDlyCad0Group2, 0x00002081);
  REG_DEF (NBRegTable, RegTxDlyCad0Group3, 0x00003081);
  REG_DEF (NBRegTable, RegTxDlyCad1Group0, 0x00100081);
  REG_DEF (NBRegTable, RegTxDlyCad1Group1, 0x00101081);
  REG_DEF (NBRegTable, RegTxDlyCad1Group2, 0x00102081);
  REG_DEF (NBRegTable, RegTxDlyCad1Group3, 0x00103081);
  REG_DEF (NBRegTable, RegTxDlyCad2Group0, 0x00200081);
  REG_DEF (NBRegTable, RegTxDlyCad2Group1, 0x00201081);
  REG_DEF (NBRegTable, RegTxDlyCad2Group2, 0x00202081);
  REG_DEF (NBRegTable, RegTxDlyCad2Group3, 0x00203081);
  REG_DEF (NBRegTable, RegTxDlyCad3Group0, 0x00300081);
  REG_DEF (NBRegTable, RegTxDlyCad3Group1, 0x00301081);
  REG_DEF (NBRegTable, RegTxDlyCad3Group2, 0x00302081);
  REG_DEF (NBRegTable, RegTxDlyCad3Group3, 0x00303081);

  REG_DEF (NBRegTable, RegDllTuningCad0Group0, 0x0000006F);
  REG_DEF (NBRegTable, RegDllTuningCad0Group1, 0x0000016F);
  REG_DEF (NBRegTable, RegDllTuningCad0Group2, 0x0000026F);
  REG_DEF (NBRegTable, RegDllTuningCad1Group0, 0x0010006F);
  REG_DEF (NBRegTable, RegDllTuningCad1Group1, 0x0010016F);
  REG_DEF (NBRegTable, RegDllTuningCad1Group2, 0x0010026F);
  REG_DEF (NBRegTable, RegDllTuningCad2Group0, 0x0020006F);
  REG_DEF (NBRegTable, RegDllTuningCad2Group1, 0x0020016F);
  REG_DEF (NBRegTable, RegDllTuningCad2Group2, 0x0020026F);
  REG_DEF (NBRegTable, RegDllTuningCad3Group0, 0x0030006F);
  REG_DEF (NBRegTable, RegDllTuningCad3Group1, 0x0030016F);
  REG_DEF (NBRegTable, RegDllTuningCad3Group2, 0x0030026F);

  REG_DEF (NBRegTable, RegDataDllTuningGroupBcst, 0x00F10F6F);

  REG_DEF (NBRegTable, RegDataDqDqsRxCtl00, 0x0001004A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl01, 0x0001104A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl02, 0x0001204A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl03, 0x0001304A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl04, 0x0001404A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl05, 0x0001504A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl06, 0x0001604A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl07, 0x0001704A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl08, 0x0001804A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl09, 0x0001904A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl0a, 0x0001A04A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl0b, 0x0001B04A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl10, 0x0011004A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl11, 0x0011104A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl12, 0x0011204A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl13, 0x0011304A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl14, 0x0011404A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl15, 0x0011504A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl16, 0x0011604A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl17, 0x0011704A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl18, 0x0011804A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl19, 0x0011904A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl1a, 0x0011A04A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl1b, 0x0011B04A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl20, 0x0021004A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl21, 0x0021104A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl22, 0x0021204A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl23, 0x0021304A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl24, 0x0021404A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl25, 0x0021504A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl26, 0x0021604A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl27, 0x0021704A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl28, 0x0021804A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl29, 0x0021904A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl2a, 0x0021A04A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl2b, 0x0021B04A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl30, 0x0031004A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl31, 0x0031104A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl32, 0x0031204A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl33, 0x0031304A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl34, 0x0031404A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl35, 0x0031504A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl36, 0x0031604A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl37, 0x0031704A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl38, 0x0031804A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl39, 0x0031904A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl3a, 0x0031A04A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl3b, 0x0031B04A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl40, 0x0041004A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl41, 0x0041104A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl42, 0x0041204A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl43, 0x0041304A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl44, 0x0041404A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl45, 0x0041504A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl46, 0x0041604A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl47, 0x0041704A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl48, 0x0041804A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl49, 0x0041904A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl4a, 0x0041A04A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl4b, 0x0041B04A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl50, 0x0051004A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl51, 0x0051104A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl52, 0x0051204A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl53, 0x0051304A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl54, 0x0051404A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl55, 0x0051504A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl56, 0x0051604A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl57, 0x0051704A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl58, 0x0051804A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl59, 0x0051904A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl5a, 0x0051A04A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl5b, 0x0051B04A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl60, 0x0061004A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl61, 0x0061104A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl62, 0x0061204A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl63, 0x0061304A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl64, 0x0061404A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl65, 0x0061504A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl66, 0x0061604A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl67, 0x0061704A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl68, 0x0061804A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl69, 0x0061904A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl6a, 0x0061A04A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl6b, 0x0061B04A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl70, 0x0071004A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl71, 0x0071104A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl72, 0x0071204A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl73, 0x0071304A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl74, 0x0071404A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl75, 0x0071504A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl76, 0x0071604A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl77, 0x0071704A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl78, 0x0071804A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl79, 0x0071904A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl7a, 0x0071A04A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl7b, 0x0071B04A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl80, 0x0081004A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl81, 0x0081104A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl82, 0x0081204A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl83, 0x0081304A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl84, 0x0081404A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl85, 0x0081504A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl86, 0x0081604A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl87, 0x0081704A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl88, 0x0081804A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl89, 0x0081904A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl8a, 0x0081A04A);
  REG_DEF (NBRegTable, RegDataDqDqsRxCtl8b, 0x0081B04A);

  REG_DEF (NBRegTable, RegDataRxDly000, 0x00010080);
  REG_DEF (NBRegTable, RegDataRxDly001, 0x00010180);
  REG_DEF (NBRegTable, RegDataRxDly002, 0x00010280);
  REG_DEF (NBRegTable, RegDataRxDly003, 0x00010380);
  REG_DEF (NBRegTable, RegDataRxDly010, 0x00011080);
  REG_DEF (NBRegTable, RegDataRxDly011, 0x00011180);
  REG_DEF (NBRegTable, RegDataRxDly012, 0x00011280);
  REG_DEF (NBRegTable, RegDataRxDly013, 0x00011380);
  REG_DEF (NBRegTable, RegDataRxDly020, 0x00012080);
  REG_DEF (NBRegTable, RegDataRxDly021, 0x00012180);
  REG_DEF (NBRegTable, RegDataRxDly022, 0x00012280);
  REG_DEF (NBRegTable, RegDataRxDly023, 0x00012380);
  REG_DEF (NBRegTable, RegDataRxDly030, 0x00013080);
  REG_DEF (NBRegTable, RegDataRxDly031, 0x00013180);
  REG_DEF (NBRegTable, RegDataRxDly032, 0x00013280);
  REG_DEF (NBRegTable, RegDataRxDly033, 0x00013380);
  REG_DEF (NBRegTable, RegDataRxDly100, 0x00110080);
  REG_DEF (NBRegTable, RegDataRxDly101, 0x00110180);
  REG_DEF (NBRegTable, RegDataRxDly102, 0x00110280);
  REG_DEF (NBRegTable, RegDataRxDly103, 0x00110380);
  REG_DEF (NBRegTable, RegDataRxDly110, 0x00111080);
  REG_DEF (NBRegTable, RegDataRxDly111, 0x00111180);
  REG_DEF (NBRegTable, RegDataRxDly112, 0x00111280);
  REG_DEF (NBRegTable, RegDataRxDly113, 0x00111380);
  REG_DEF (NBRegTable, RegDataRxDly120, 0x00112080);
  REG_DEF (NBRegTable, RegDataRxDly121, 0x00112180);
  REG_DEF (NBRegTable, RegDataRxDly122, 0x00112280);
  REG_DEF (NBRegTable, RegDataRxDly123, 0x00112380);
  REG_DEF (NBRegTable, RegDataRxDly130, 0x00113080);
  REG_DEF (NBRegTable, RegDataRxDly131, 0x00113180);
  REG_DEF (NBRegTable, RegDataRxDly132, 0x00113280);
  REG_DEF (NBRegTable, RegDataRxDly133, 0x00113380);
  REG_DEF (NBRegTable, RegDataRxDly200, 0x00210080);
  REG_DEF (NBRegTable, RegDataRxDly201, 0x00210180);
  REG_DEF (NBRegTable, RegDataRxDly202, 0x00210280);
  REG_DEF (NBRegTable, RegDataRxDly203, 0x00210380);
  REG_DEF (NBRegTable, RegDataRxDly210, 0x00211080);
  REG_DEF (NBRegTable, RegDataRxDly211, 0x00211180);
  REG_DEF (NBRegTable, RegDataRxDly212, 0x00211280);
  REG_DEF (NBRegTable, RegDataRxDly213, 0x00211380);
  REG_DEF (NBRegTable, RegDataRxDly220, 0x00212080);
  REG_DEF (NBRegTable, RegDataRxDly221, 0x00212180);
  REG_DEF (NBRegTable, RegDataRxDly222, 0x00212280);
  REG_DEF (NBRegTable, RegDataRxDly223, 0x00212380);
  REG_DEF (NBRegTable, RegDataRxDly230, 0x00213080);
  REG_DEF (NBRegTable, RegDataRxDly231, 0x00213180);
  REG_DEF (NBRegTable, RegDataRxDly232, 0x00213280);
  REG_DEF (NBRegTable, RegDataRxDly233, 0x00213380);
  REG_DEF (NBRegTable, RegDataRxDly300, 0x00310080);
  REG_DEF (NBRegTable, RegDataRxDly301, 0x00310180);
  REG_DEF (NBRegTable, RegDataRxDly302, 0x00310280);
  REG_DEF (NBRegTable, RegDataRxDly303, 0x00310380);
  REG_DEF (NBRegTable, RegDataRxDly310, 0x00311080);
  REG_DEF (NBRegTable, RegDataRxDly311, 0x00311180);
  REG_DEF (NBRegTable, RegDataRxDly312, 0x00311280);
  REG_DEF (NBRegTable, RegDataRxDly313, 0x00311380);
  REG_DEF (NBRegTable, RegDataRxDly320, 0x00312080);
  REG_DEF (NBRegTable, RegDataRxDly321, 0x00312180);
  REG_DEF (NBRegTable, RegDataRxDly322, 0x00312280);
  REG_DEF (NBRegTable, RegDataRxDly323, 0x00312380);
  REG_DEF (NBRegTable, RegDataRxDly330, 0x00313080);
  REG_DEF (NBRegTable, RegDataRxDly331, 0x00313180);
  REG_DEF (NBRegTable, RegDataRxDly332, 0x00313280);
  REG_DEF (NBRegTable, RegDataRxDly333, 0x00313380);
  REG_DEF (NBRegTable, RegDataRxDly400, 0x00410080);
  REG_DEF (NBRegTable, RegDataRxDly401, 0x00410180);
  REG_DEF (NBRegTable, RegDataRxDly402, 0x00410280);
  REG_DEF (NBRegTable, RegDataRxDly403, 0x00410380);
  REG_DEF (NBRegTable, RegDataRxDly410, 0x00411080);
  REG_DEF (NBRegTable, RegDataRxDly411, 0x00411180);
  REG_DEF (NBRegTable, RegDataRxDly412, 0x00411280);
  REG_DEF (NBRegTable, RegDataRxDly413, 0x00411380);
  REG_DEF (NBRegTable, RegDataRxDly420, 0x00412080);
  REG_DEF (NBRegTable, RegDataRxDly421, 0x00412180);
  REG_DEF (NBRegTable, RegDataRxDly422, 0x00412280);
  REG_DEF (NBRegTable, RegDataRxDly423, 0x00412380);
  REG_DEF (NBRegTable, RegDataRxDly430, 0x00413080);
  REG_DEF (NBRegTable, RegDataRxDly431, 0x00413180);
  REG_DEF (NBRegTable, RegDataRxDly432, 0x00413280);
  REG_DEF (NBRegTable, RegDataRxDly433, 0x00413380);
  REG_DEF (NBRegTable, RegDataRxDly500, 0x00510080);
  REG_DEF (NBRegTable, RegDataRxDly501, 0x00510180);
  REG_DEF (NBRegTable, RegDataRxDly502, 0x00510280);
  REG_DEF (NBRegTable, RegDataRxDly503, 0x00510380);
  REG_DEF (NBRegTable, RegDataRxDly510, 0x00511080);
  REG_DEF (NBRegTable, RegDataRxDly511, 0x00511180);
  REG_DEF (NBRegTable, RegDataRxDly512, 0x00511280);
  REG_DEF (NBRegTable, RegDataRxDly513, 0x00511380);
  REG_DEF (NBRegTable, RegDataRxDly520, 0x00512080);
  REG_DEF (NBRegTable, RegDataRxDly521, 0x00512180);
  REG_DEF (NBRegTable, RegDataRxDly522, 0x00512280);
  REG_DEF (NBRegTable, RegDataRxDly523, 0x00512380);
  REG_DEF (NBRegTable, RegDataRxDly530, 0x00513080);
  REG_DEF (NBRegTable, RegDataRxDly531, 0x00513180);
  REG_DEF (NBRegTable, RegDataRxDly532, 0x00513280);
  REG_DEF (NBRegTable, RegDataRxDly533, 0x00513380);
  REG_DEF (NBRegTable, RegDataRxDly600, 0x00610080);
  REG_DEF (NBRegTable, RegDataRxDly601, 0x00610180);
  REG_DEF (NBRegTable, RegDataRxDly602, 0x00610280);
  REG_DEF (NBRegTable, RegDataRxDly603, 0x00610380);
  REG_DEF (NBRegTable, RegDataRxDly610, 0x00611080);
  REG_DEF (NBRegTable, RegDataRxDly611, 0x00611180);
  REG_DEF (NBRegTable, RegDataRxDly612, 0x00611280);
  REG_DEF (NBRegTable, RegDataRxDly613, 0x00611380);
  REG_DEF (NBRegTable, RegDataRxDly620, 0x00612080);
  REG_DEF (NBRegTable, RegDataRxDly621, 0x00612180);
  REG_DEF (NBRegTable, RegDataRxDly622, 0x00612280);
  REG_DEF (NBRegTable, RegDataRxDly623, 0x00612380);
  REG_DEF (NBRegTable, RegDataRxDly630, 0x00613080);
  REG_DEF (NBRegTable, RegDataRxDly631, 0x00613180);
  REG_DEF (NBRegTable, RegDataRxDly632, 0x00613280);
  REG_DEF (NBRegTable, RegDataRxDly633, 0x00613380);
  REG_DEF (NBRegTable, RegDataRxDly700, 0x00710080);
  REG_DEF (NBRegTable, RegDataRxDly701, 0x00710180);
  REG_DEF (NBRegTable, RegDataRxDly702, 0x00710280);
  REG_DEF (NBRegTable, RegDataRxDly703, 0x00710380);
  REG_DEF (NBRegTable, RegDataRxDly710, 0x00711080);
  REG_DEF (NBRegTable, RegDataRxDly711, 0x00711180);
  REG_DEF (NBRegTable, RegDataRxDly712, 0x00711280);
  REG_DEF (NBRegTable, RegDataRxDly713, 0x00711380);
  REG_DEF (NBRegTable, RegDataRxDly720, 0x00712080);
  REG_DEF (NBRegTable, RegDataRxDly721, 0x00712180);
  REG_DEF (NBRegTable, RegDataRxDly722, 0x00712280);
  REG_DEF (NBRegTable, RegDataRxDly723, 0x00712380);
  REG_DEF (NBRegTable, RegDataRxDly730, 0x00713080);
  REG_DEF (NBRegTable, RegDataRxDly731, 0x00713180);
  REG_DEF (NBRegTable, RegDataRxDly732, 0x00713280);
  REG_DEF (NBRegTable, RegDataRxDly733, 0x00713380);
  REG_DEF (NBRegTable, RegDataRxDly800, 0x00810080);
  REG_DEF (NBRegTable, RegDataRxDly801, 0x00810180);
  REG_DEF (NBRegTable, RegDataRxDly802, 0x00810280);
  REG_DEF (NBRegTable, RegDataRxDly803, 0x00810380);
  REG_DEF (NBRegTable, RegDataRxDly810, 0x00811080);
  REG_DEF (NBRegTable, RegDataRxDly811, 0x00811180);
  REG_DEF (NBRegTable, RegDataRxDly812, 0x00811280);
  REG_DEF (NBRegTable, RegDataRxDly813, 0x00811380);
  REG_DEF (NBRegTable, RegDataRxDly820, 0x00812080);
  REG_DEF (NBRegTable, RegDataRxDly821, 0x00812180);
  REG_DEF (NBRegTable, RegDataRxDly822, 0x00812280);
  REG_DEF (NBRegTable, RegDataRxDly823, 0x00812380);
  REG_DEF (NBRegTable, RegDataRxDly830, 0x00813080);
  REG_DEF (NBRegTable, RegDataRxDly831, 0x00813180);
  REG_DEF (NBRegTable, RegDataRxDly832, 0x00813280);
  REG_DEF (NBRegTable, RegDataRxDly833, 0x00813380);

  REG_DEF (NBRegTable, RegDataTxDly000, 0x00010081);
  REG_DEF (NBRegTable, RegDataTxDly001, 0x00010181);
  REG_DEF (NBRegTable, RegDataTxDly002, 0x00010281);
  REG_DEF (NBRegTable, RegDataTxDly003, 0x00010381);
  REG_DEF (NBRegTable, RegDataTxDly010, 0x00011081);
  REG_DEF (NBRegTable, RegDataTxDly011, 0x00011181);
  REG_DEF (NBRegTable, RegDataTxDly012, 0x00011281);
  REG_DEF (NBRegTable, RegDataTxDly013, 0x00011381);
  REG_DEF (NBRegTable, RegDataTxDly020, 0x00012081);
  REG_DEF (NBRegTable, RegDataTxDly021, 0x00012181);
  REG_DEF (NBRegTable, RegDataTxDly022, 0x00012281);
  REG_DEF (NBRegTable, RegDataTxDly023, 0x00012381);
  REG_DEF (NBRegTable, RegDataTxDly030, 0x00013081);
  REG_DEF (NBRegTable, RegDataTxDly031, 0x00013181);
  REG_DEF (NBRegTable, RegDataTxDly032, 0x00013281);
  REG_DEF (NBRegTable, RegDataTxDly033, 0x00013381);
  REG_DEF (NBRegTable, RegDataTxDly100, 0x00110081);
  REG_DEF (NBRegTable, RegDataTxDly101, 0x00110181);
  REG_DEF (NBRegTable, RegDataTxDly102, 0x00110281);
  REG_DEF (NBRegTable, RegDataTxDly103, 0x00110381);
  REG_DEF (NBRegTable, RegDataTxDly110, 0x00111081);
  REG_DEF (NBRegTable, RegDataTxDly111, 0x00111181);
  REG_DEF (NBRegTable, RegDataTxDly112, 0x00111281);
  REG_DEF (NBRegTable, RegDataTxDly113, 0x00111381);
  REG_DEF (NBRegTable, RegDataTxDly120, 0x00112081);
  REG_DEF (NBRegTable, RegDataTxDly121, 0x00112181);
  REG_DEF (NBRegTable, RegDataTxDly122, 0x00112281);
  REG_DEF (NBRegTable, RegDataTxDly123, 0x00112381);
  REG_DEF (NBRegTable, RegDataTxDly130, 0x00113081);
  REG_DEF (NBRegTable, RegDataTxDly131, 0x00113181);
  REG_DEF (NBRegTable, RegDataTxDly132, 0x00113281);
  REG_DEF (NBRegTable, RegDataTxDly133, 0x00113381);
  REG_DEF (NBRegTable, RegDataTxDly200, 0x00210081);
  REG_DEF (NBRegTable, RegDataTxDly201, 0x00210181);
  REG_DEF (NBRegTable, RegDataTxDly202, 0x00210281);
  REG_DEF (NBRegTable, RegDataTxDly203, 0x00210381);
  REG_DEF (NBRegTable, RegDataTxDly210, 0x00211081);
  REG_DEF (NBRegTable, RegDataTxDly211, 0x00211181);
  REG_DEF (NBRegTable, RegDataTxDly212, 0x00211281);
  REG_DEF (NBRegTable, RegDataTxDly213, 0x00211381);
  REG_DEF (NBRegTable, RegDataTxDly220, 0x00212081);
  REG_DEF (NBRegTable, RegDataTxDly221, 0x00212181);
  REG_DEF (NBRegTable, RegDataTxDly222, 0x00212281);
  REG_DEF (NBRegTable, RegDataTxDly223, 0x00212381);
  REG_DEF (NBRegTable, RegDataTxDly230, 0x00213081);
  REG_DEF (NBRegTable, RegDataTxDly231, 0x00213181);
  REG_DEF (NBRegTable, RegDataTxDly232, 0x00213281);
  REG_DEF (NBRegTable, RegDataTxDly233, 0x00213381);
  REG_DEF (NBRegTable, RegDataTxDly300, 0x00310081);
  REG_DEF (NBRegTable, RegDataTxDly301, 0x00310181);
  REG_DEF (NBRegTable, RegDataTxDly302, 0x00310281);
  REG_DEF (NBRegTable, RegDataTxDly303, 0x00310381);
  REG_DEF (NBRegTable, RegDataTxDly310, 0x00311081);
  REG_DEF (NBRegTable, RegDataTxDly311, 0x00311181);
  REG_DEF (NBRegTable, RegDataTxDly312, 0x00311281);
  REG_DEF (NBRegTable, RegDataTxDly313, 0x00311381);
  REG_DEF (NBRegTable, RegDataTxDly320, 0x00312081);
  REG_DEF (NBRegTable, RegDataTxDly321, 0x00312181);
  REG_DEF (NBRegTable, RegDataTxDly322, 0x00312281);
  REG_DEF (NBRegTable, RegDataTxDly323, 0x00312381);
  REG_DEF (NBRegTable, RegDataTxDly330, 0x00313081);
  REG_DEF (NBRegTable, RegDataTxDly331, 0x00313181);
  REG_DEF (NBRegTable, RegDataTxDly332, 0x00313281);
  REG_DEF (NBRegTable, RegDataTxDly333, 0x00313381);
  REG_DEF (NBRegTable, RegDataTxDly400, 0x00410081);
  REG_DEF (NBRegTable, RegDataTxDly401, 0x00410181);
  REG_DEF (NBRegTable, RegDataTxDly402, 0x00410281);
  REG_DEF (NBRegTable, RegDataTxDly403, 0x00410381);
  REG_DEF (NBRegTable, RegDataTxDly410, 0x00411081);
  REG_DEF (NBRegTable, RegDataTxDly411, 0x00411181);
  REG_DEF (NBRegTable, RegDataTxDly412, 0x00411281);
  REG_DEF (NBRegTable, RegDataTxDly413, 0x00411381);
  REG_DEF (NBRegTable, RegDataTxDly420, 0x00412081);
  REG_DEF (NBRegTable, RegDataTxDly421, 0x00412181);
  REG_DEF (NBRegTable, RegDataTxDly422, 0x00412281);
  REG_DEF (NBRegTable, RegDataTxDly423, 0x00412381);
  REG_DEF (NBRegTable, RegDataTxDly430, 0x00413081);
  REG_DEF (NBRegTable, RegDataTxDly431, 0x00413181);
  REG_DEF (NBRegTable, RegDataTxDly432, 0x00413281);
  REG_DEF (NBRegTable, RegDataTxDly433, 0x00413381);
  REG_DEF (NBRegTable, RegDataTxDly500, 0x00510081);
  REG_DEF (NBRegTable, RegDataTxDly501, 0x00510181);
  REG_DEF (NBRegTable, RegDataTxDly502, 0x00510281);
  REG_DEF (NBRegTable, RegDataTxDly503, 0x00510381);
  REG_DEF (NBRegTable, RegDataTxDly510, 0x00511081);
  REG_DEF (NBRegTable, RegDataTxDly511, 0x00511181);
  REG_DEF (NBRegTable, RegDataTxDly512, 0x00511281);
  REG_DEF (NBRegTable, RegDataTxDly513, 0x00511381);
  REG_DEF (NBRegTable, RegDataTxDly520, 0x00512081);
  REG_DEF (NBRegTable, RegDataTxDly521, 0x00512181);
  REG_DEF (NBRegTable, RegDataTxDly522, 0x00512281);
  REG_DEF (NBRegTable, RegDataTxDly523, 0x00512381);
  REG_DEF (NBRegTable, RegDataTxDly530, 0x00513081);
  REG_DEF (NBRegTable, RegDataTxDly531, 0x00513181);
  REG_DEF (NBRegTable, RegDataTxDly532, 0x00513281);
  REG_DEF (NBRegTable, RegDataTxDly533, 0x00513381);
  REG_DEF (NBRegTable, RegDataTxDly600, 0x00610081);
  REG_DEF (NBRegTable, RegDataTxDly601, 0x00610181);
  REG_DEF (NBRegTable, RegDataTxDly602, 0x00610281);
  REG_DEF (NBRegTable, RegDataTxDly603, 0x00610381);
  REG_DEF (NBRegTable, RegDataTxDly610, 0x00611081);
  REG_DEF (NBRegTable, RegDataTxDly611, 0x00611181);
  REG_DEF (NBRegTable, RegDataTxDly612, 0x00611281);
  REG_DEF (NBRegTable, RegDataTxDly613, 0x00611381);
  REG_DEF (NBRegTable, RegDataTxDly620, 0x00612081);
  REG_DEF (NBRegTable, RegDataTxDly621, 0x00612181);
  REG_DEF (NBRegTable, RegDataTxDly622, 0x00612281);
  REG_DEF (NBRegTable, RegDataTxDly623, 0x00612381);
  REG_DEF (NBRegTable, RegDataTxDly630, 0x00613081);
  REG_DEF (NBRegTable, RegDataTxDly631, 0x00613181);
  REG_DEF (NBRegTable, RegDataTxDly632, 0x00613281);
  REG_DEF (NBRegTable, RegDataTxDly633, 0x00613381);
  REG_DEF (NBRegTable, RegDataTxDly700, 0x00710081);
  REG_DEF (NBRegTable, RegDataTxDly701, 0x00710181);
  REG_DEF (NBRegTable, RegDataTxDly702, 0x00710281);
  REG_DEF (NBRegTable, RegDataTxDly703, 0x00710381);
  REG_DEF (NBRegTable, RegDataTxDly710, 0x00711081);
  REG_DEF (NBRegTable, RegDataTxDly711, 0x00711181);
  REG_DEF (NBRegTable, RegDataTxDly712, 0x00711281);
  REG_DEF (NBRegTable, RegDataTxDly713, 0x00711381);
  REG_DEF (NBRegTable, RegDataTxDly720, 0x00712081);
  REG_DEF (NBRegTable, RegDataTxDly721, 0x00712181);
  REG_DEF (NBRegTable, RegDataTxDly722, 0x00712281);
  REG_DEF (NBRegTable, RegDataTxDly723, 0x00712381);
  REG_DEF (NBRegTable, RegDataTxDly730, 0x00713081);
  REG_DEF (NBRegTable, RegDataTxDly731, 0x00713181);
  REG_DEF (NBRegTable, RegDataTxDly732, 0x00713281);
  REG_DEF (NBRegTable, RegDataTxDly733, 0x00713381);
  REG_DEF (NBRegTable, RegDataTxDly800, 0x00810081);
  REG_DEF (NBRegTable, RegDataTxDly801, 0x00810181);
  REG_DEF (NBRegTable, RegDataTxDly802, 0x00810281);
  REG_DEF (NBRegTable, RegDataTxDly803, 0x00810381);
  REG_DEF (NBRegTable, RegDataTxDly810, 0x00811081);
  REG_DEF (NBRegTable, RegDataTxDly811, 0x00811181);
  REG_DEF (NBRegTable, RegDataTxDly812, 0x00811281);
  REG_DEF (NBRegTable, RegDataTxDly813, 0x00811381);
  REG_DEF (NBRegTable, RegDataTxDly820, 0x00812081);
  REG_DEF (NBRegTable, RegDataTxDly821, 0x00812181);
  REG_DEF (NBRegTable, RegDataTxDly822, 0x00812281);
  REG_DEF (NBRegTable, RegDataTxDly823, 0x00812381);
  REG_DEF (NBRegTable, RegDataTxDly830, 0x00813081);
  REG_DEF (NBRegTable, RegDataTxDly831, 0x00813181);
  REG_DEF (NBRegTable, RegDataTxDly832, 0x00813281);
  REG_DEF (NBRegTable, RegDataTxDly833, 0x00813381);

  REG_DEF (NBRegTable, RegCadTxImpedance00, 0x00000041);
  REG_DEF (NBRegTable, RegCadTxImpedance01, 0x00001041);
  REG_DEF (NBRegTable, RegCadTxImpedance02, 0x00002041);
  REG_DEF (NBRegTable, RegCadTxImpedance03, 0x00003041);
  REG_DEF (NBRegTable, RegCadTxImpedance04, 0x00004041);
  REG_DEF (NBRegTable, RegCadTxImpedance05, 0x00005041);
  REG_DEF (NBRegTable, RegCadTxImpedance06, 0x00006041);
  REG_DEF (NBRegTable, RegCadTxImpedance07, 0x00007041);
  REG_DEF (NBRegTable, RegCadTxImpedance08, 0x00008041);
  REG_DEF (NBRegTable, RegCadTxImpedance09, 0x00009041);
  REG_DEF (NBRegTable, RegCadTxImpedance0a, 0x0000A041);
  REG_DEF (NBRegTable, RegCadTxImpedance0b, 0x0000B041);
  REG_DEF (NBRegTable, RegCadTxImpedance10, 0x00100041);
  REG_DEF (NBRegTable, RegCadTxImpedance11, 0x00101041);
  REG_DEF (NBRegTable, RegCadTxImpedance12, 0x00102041);
  REG_DEF (NBRegTable, RegCadTxImpedance13, 0x00103041);
  REG_DEF (NBRegTable, RegCadTxImpedance14, 0x00104041);
  REG_DEF (NBRegTable, RegCadTxImpedance15, 0x00105041);
  REG_DEF (NBRegTable, RegCadTxImpedance16, 0x00106041);
  REG_DEF (NBRegTable, RegCadTxImpedance17, 0x00107041);
  REG_DEF (NBRegTable, RegCadTxImpedance18, 0x00108041);
  REG_DEF (NBRegTable, RegCadTxImpedance19, 0x00109041);
  REG_DEF (NBRegTable, RegCadTxImpedance1a, 0x0010A041);
  REG_DEF (NBRegTable, RegCadTxImpedance1b, 0x0010B041);
  REG_DEF (NBRegTable, RegCadTxImpedance20, 0x00200041);
  REG_DEF (NBRegTable, RegCadTxImpedance21, 0x00201041);
  REG_DEF (NBRegTable, RegCadTxImpedance22, 0x00202041);
  REG_DEF (NBRegTable, RegCadTxImpedance23, 0x00203041);
  REG_DEF (NBRegTable, RegCadTxImpedance24, 0x00204041);
  REG_DEF (NBRegTable, RegCadTxImpedance25, 0x00205041);
  REG_DEF (NBRegTable, RegCadTxImpedance26, 0x00206041);
  REG_DEF (NBRegTable, RegCadTxImpedance27, 0x00207041);
  REG_DEF (NBRegTable, RegCadTxImpedance28, 0x00208041);
  REG_DEF (NBRegTable, RegCadTxImpedance29, 0x00209041);
  REG_DEF (NBRegTable, RegCadTxImpedance2a, 0x0020A041);
  REG_DEF (NBRegTable, RegCadTxImpedance2b, 0x0020B041);
  REG_DEF (NBRegTable, RegCadTxImpedance30, 0x00300041);
  REG_DEF (NBRegTable, RegCadTxImpedance31, 0x00301041);
  REG_DEF (NBRegTable, RegCadTxImpedance32, 0x00302041);
  REG_DEF (NBRegTable, RegCadTxImpedance33, 0x00303041);
  REG_DEF (NBRegTable, RegCadTxImpedance34, 0x00304041);
  REG_DEF (NBRegTable, RegCadTxImpedance35, 0x00305041);
  REG_DEF (NBRegTable, RegCadTxImpedance36, 0x00306041);
  REG_DEF (NBRegTable, RegCadTxImpedance37, 0x00307041);
  REG_DEF (NBRegTable, RegCadTxImpedance38, 0x00308041);
  REG_DEF (NBRegTable, RegCadTxImpedance39, 0x00309041);
  REG_DEF (NBRegTable, RegCadTxImpedance3a, 0x0030A041);
  REG_DEF (NBRegTable, RegCadTxImpedance3b, 0x0030B041);

  REG_DEF (NBRegTable, RegCalTxImpedance00, 0x0000004E);
  REG_DEF (NBRegTable, RegCalTxImpedance01, 0x0000104E);
  REG_DEF (NBRegTable, RegCalTxImpedance02, 0x0000204E);
  REG_DEF (NBRegTable, RegCalTxImpedance03, 0x0000304E);
  REG_DEF (NBRegTable, RegCalTxImpedance04, 0x0000404E);
  REG_DEF (NBRegTable, RegCalTxImpedance05, 0x0000504E);
  REG_DEF (NBRegTable, RegCalTxImpedance06, 0x0000604E);
  REG_DEF (NBRegTable, RegCalTxImpedance07, 0x0000704E);
  REG_DEF (NBRegTable, RegCalTxImpedance08, 0x0000804E);
  REG_DEF (NBRegTable, RegCalTxImpedance09, 0x0000904E);
  REG_DEF (NBRegTable, RegCalTxImpedance0a, 0x0000A04E);
  REG_DEF (NBRegTable, RegCalTxImpedance0b, 0x0000B04E);
  REG_DEF (NBRegTable, RegCalTxImpedance10, 0x0010004E);
  REG_DEF (NBRegTable, RegCalTxImpedance11, 0x0010104E);
  REG_DEF (NBRegTable, RegCalTxImpedance12, 0x0010204E);
  REG_DEF (NBRegTable, RegCalTxImpedance13, 0x0010304E);
  REG_DEF (NBRegTable, RegCalTxImpedance14, 0x0010404E);
  REG_DEF (NBRegTable, RegCalTxImpedance15, 0x0010504E);
  REG_DEF (NBRegTable, RegCalTxImpedance16, 0x0010604E);
  REG_DEF (NBRegTable, RegCalTxImpedance17, 0x0010704E);
  REG_DEF (NBRegTable, RegCalTxImpedance18, 0x0010804E);
  REG_DEF (NBRegTable, RegCalTxImpedance19, 0x0010904E);
  REG_DEF (NBRegTable, RegCalTxImpedance1a, 0x0010A04E);
  REG_DEF (NBRegTable, RegCalTxImpedance1b, 0x0010B04E);
  REG_DEF (NBRegTable, RegCalTxImpedance20, 0x0020004E);
  REG_DEF (NBRegTable, RegCalTxImpedance21, 0x0020104E);
  REG_DEF (NBRegTable, RegCalTxImpedance22, 0x0020204E);
  REG_DEF (NBRegTable, RegCalTxImpedance23, 0x0020304E);
  REG_DEF (NBRegTable, RegCalTxImpedance24, 0x0020404E);
  REG_DEF (NBRegTable, RegCalTxImpedance25, 0x0020504E);
  REG_DEF (NBRegTable, RegCalTxImpedance26, 0x0020604E);
  REG_DEF (NBRegTable, RegCalTxImpedance27, 0x0020704E);
  REG_DEF (NBRegTable, RegCalTxImpedance28, 0x0020804E);
  REG_DEF (NBRegTable, RegCalTxImpedance29, 0x0020904E);
  REG_DEF (NBRegTable, RegCalTxImpedance2a, 0x0020A04E);
  REG_DEF (NBRegTable, RegCalTxImpedance2b, 0x0020B04E);
  REG_DEF (NBRegTable, RegCalTxImpedance30, 0x0030004E);
  REG_DEF (NBRegTable, RegCalTxImpedance31, 0x0030104E);
  REG_DEF (NBRegTable, RegCalTxImpedance32, 0x0030204E);
  REG_DEF (NBRegTable, RegCalTxImpedance33, 0x0030304E);
  REG_DEF (NBRegTable, RegCalTxImpedance34, 0x0030404E);
  REG_DEF (NBRegTable, RegCalTxImpedance35, 0x0030504E);
  REG_DEF (NBRegTable, RegCalTxImpedance36, 0x0030604E);
  REG_DEF (NBRegTable, RegCalTxImpedance37, 0x0030704E);
  REG_DEF (NBRegTable, RegCalTxImpedance38, 0x0030804E);
  REG_DEF (NBRegTable, RegCalTxImpedance39, 0x0030904E);
  REG_DEF (NBRegTable, RegCalTxImpedance3a, 0x0030A04E);
  REG_DEF (NBRegTable, RegCalTxImpedance3b, 0x0030B04E);

  // DRAM PHY Power Savings
  REG_DEF (NBRegTable, RegCadDllLockMaintenance, 0x01F00014);
  _BF_DEF (NBRegTable, RegCadDllLockMaintenance, BFCadMaxDurDllNoLock,  3,  0);
  _BF_DEF (NBRegTable, RegCadDllLockMaintenance, BFCadDllPumpCount, 7,  4);

  REG_DEF (NBRegTable, RegDataDllLockMaintenance, 0x01F10014);
  _BF_DEF (NBRegTable, RegDataDllLockMaintenance, BFDataMaxDurDllNoLock,  3,  0);
  _BF_DEF (NBRegTable, RegDataDllLockMaintenance, BFDataDllPumpCount, 7,  4);

  REG_DEF (NBRegTable, RegDctPhyDllPowerdown0, 0x00F10077);  // HW broadcast
  REG_DEF (NBRegTable, RegDctPhyDllPowerdown2, 0x00F10277);  // HW broadcast
  REG_DEF (NBRegTable, RegDctPhyDllPowerdown2EccByte, 0x00810277);  // HW broadcast

  REG_DEF (NBRegTable, RegDctPhyA78DllControl, 0x00F00078);  // HW broadcast
  REG_DEF (NBRegTable, RegDctPhyD78DllControl, 0x00F10F78);  // HW broadcast

  REG_DEF (NBRegTable, RegCalVRefs, 0x0002009B);

  REG_DEF (NBRegTable, RegVrefInGlobal, 0x000200B2);
  _BF_DEF (NBRegTable, RegVrefInGlobal, BFGlobalVrefInSel, 2, 0);

  // Lane to CRC Map
  REG_DEF (NBRegTable, RegLaneToCrcMap0, 0x00070015);
  REG_DEF (NBRegTable, RegLaneToCrcMap1, 0x00070016);

  // VrefDnom
  REG_DEF (NBRegTable, RegDctPhy0x00F0F04A, 0x00F0F04A);     // HW broadcast

  REG_DEF (NBRegTable, RegVrefHSpeed, 0x01F1F044);           // HW broadcast
  REG_DEF (NBRegTable, RegVrefLpower, 0x01F1F045);           // HW broadcast

  // TxControlDq
  REG_DEF (NBRegTable, RegDctPhyD0091F04E, 0x0091F04E);     // HW broadcast

  REG_DEF (NBRegTable, RegTxControlDq, 0x03F6F04E);         // HW broadcast
  REG_DEF (NBRegTable, RegTxControlDq2, 0x03F6F050);        // HW broadcast
  REG_DEF (NBRegTable, RegCadByteDbgCtrl, 0x00F0001A);      // HW broadcast
  REG_DEF (NBRegTable, RegDataByteDbgCtrl, 0x00F1001A);     // HW broadcast
  REG_DEF (NBRegTable, RegMasterByteDbgCtrl, 0x0002001A);
  REG_DEF (NBRegTable, RegMasterD3MerrRcvrCntrl, 0x0002005A);
  REG_DEF (NBRegTable, RegMasterD3EvntMerr, 0x0002005B);
  REG_DEF (NBRegTable, RegDataDqDqsRcvCntrl3, 0x00F1F051);  // HW broadcast
  REG_DEF (NBRegTable, RegDataRcvMajorMode, 0x01F1F043);    // HW broadcast

  // Unused DBYTE 9
  REG_DEF (NBRegTable, RegDctPhyD0091F04A, 0x0091F04A);  // HW broadcast
  REG_DEF (NBRegTable, RegDctPhyD00910F77, 0x00910F77);  // HW broadcast
  REG_DEF (NBRegTable, RegDctPhyD00910000, 0x00910000);
  REG_DEF (NBRegTable, RegDctPhyD0391F04D, 0x0391F04D);  // HW broadcast
  REG_DEF (NBRegTable, RegDctPhyD0391F041, 0x0391F041);  // HW broadcast

  // Unused ABYTE DLL
  REG_DEF (NBRegTable, RegDctPhy0x00200077, 0x00200077);
  REG_DEF (NBRegTable, RegDctPhy0x00300077, 0x00300077);
  REG_DEF (NBRegTable, RegDctPhy0x00000077, 0x00000077);
  REG_DEF (NBRegTable, RegDctPhy0x00100077, 0x00100077);

  // Unused DBYTE receivers
  REG_DEF (NBRegTable, RegDctPhyD00F1804A, 0x00F1804A);  // HW broadcast
  REG_DEF (NBRegTable, RegDctPhyD00F1904A, 0x00F1904A);  // HW broadcast
  REG_DEF (NBRegTable, RegDctPhyD00F1B04A, 0x00F1B04A);  // HW broadcast

  // ---------------------------------------------------------------------------
  // LINK BITFIELD
  // ---------------------------------------------------------------------------
  LINK_BF (NBRegTable, BFDctSelIntLvAddr, BFDctSelIntLvAddrHi);
  LINK_BF (NBRegTable, BFBaseModel, BFExtModel);
  LINK_BF (NBRegTable, BFNbVid0, BFNbVid0Hi);
  LINK_BF (NBRegTable, BFNbVid1, BFNbVid1Hi);
  LINK_BF (NBRegTable, BFNbVid2, BFNbVid2Hi);
  LINK_BF (NBRegTable, BFNbVid3, BFNbVid3Hi);
  LINK_BF (NBRegTable, BFCurNbVid, BFCurNbVidHi);

  IDS_OPTION_HOOK (IDS_INIT_MEM_REG_TABLE, NBPtr, &NBPtr->MemPtr->StdHeader);
}


