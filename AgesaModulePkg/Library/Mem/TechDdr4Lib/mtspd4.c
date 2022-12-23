/* $NoKeywords:$ */
/**
 * @file
 *
 * mtspd4.c
 *
 * Technology SPD supporting functions for DDR4
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/Tech/DDR4)
 * @e \$Revision: 328552 $ @e \$Date: 2015-10-09 19:05:57 +0800 (Fri, 09 Oct 2015) $
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


#include "AGESA.h"
#include "Library/AmdBaseLib.h"
#include "Library/AmdMemBaseV5Lib.h"
#include "Library/IdsLib.h"
#include "Ids.h"
#include "mport.h"
#include "mm.h"
#include "mn.h"
#include "mt.h"
#include "mt4.h"
#include "mu.h"
#include "mtspd4.h"
#include "mftds.h"
#include "Filecode.h"
CODE_GROUP (G1_PEICC)
RDATA_GROUP (G1_PEICC)

#define FILECODE LIBRARY_MEM_TECHDDR4LIB_MTSPD4_FILECODE

/*----------------------------------------------------------------------------
 *                          DEFINITIONS AND MACROS
 *
 *----------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------
 *                           TYPEDEFS AND STRUCTURES
 *
 *----------------------------------------------------------------------------
 */

typedef struct _DDR4_DRAM_ADDRESS_MAP {
  UINT8  DimmAddressMap;
  UINT8  BGBits;
  UINT8  BABits;
  UINT8  RowBits;
  UINT8  ColBits;
} DDR4_DRAM_ADDRESS_MAP;

typedef struct _DQMAP_NIBBLE {
  UINT8 Nibble;
  UINT8 SpdOffset;
} DQMAP_NIBBLE;

/*----------------------------------------------------------------------------
 *                        PROTOTYPES OF LOCAL FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */
BOOLEAN
STATIC
MemTCRCCheck4 (
  IN OUT   UINT8 *SPDPtr
  );

UINT8
STATIC
MemTSPDGetTCL4 (
  IN OUT   MEM_TECH_BLOCK *TechPtr
  );

UINT8
STATIC
MemTSPDGetTrcpage4 (
  IN OUT   MEM_TECH_BLOCK *TechPtr
  );

BOOLEAN
STATIC
MemTCheckBankAddr4 (
  OUT   UINT8 *DimmAddrMap,
  IN    UINT8 BGBits,
  IN    UINT8 BABits,
  IN    UINT8 RowBits,
  IN    UINT8 ColBits
  );

INT32
MemTGetMTB (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN OUT   UINT8 *SpdBuffer
  );

INT32
MemTGetFTB (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN OUT   UINT8 *SpdBuffer
  );

UINT8
MemTGetJedecMinClks (
  IN UINT8 SPDOffset,
  IN UINT16 PageSize
  );

/*----------------------------------------------------------------------------
 *                            EXPORTED FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */
//
// JEDEC DDR4 TIMING MINIMUM VALUES IN NUMBER OF CLKs
//
// ----------------------------------------------------------------------------
DDR4_NCK_MIN MemDdr4JedecMinClksTable[] = {
  { SPD_TCCD_L,   PGSZ_NA,    5 },
  { SPD_TRRD_S,   PGSZ_512,   4 },
  { SPD_TRRD_S,   PGSZ_1K,    4 },
  { SPD_TRRD_S,   PGSZ_2K,    4 },
  { SPD_TRRD_L,   PGSZ_512,   4 },
  { SPD_TRRD_L,   PGSZ_1K,    4 },
  { SPD_TRRD_L,   PGSZ_2K,    4 },
  { SPD_TFAW_LSB, PGSZ_512,  16 },
  { SPD_TFAW_LSB, PGSZ_1K,   20 },
  { SPD_TFAW_LSB, PGSZ_2K,   28 },
  { SPD_TWTR_S,   PGSZ_NA,    2 },
  { SPD_TWTR_L,   PGSZ_NA,    4 }
};

/* -----------------------------------------------------------------------------*/
/**
 *
 *   This function determines if DIMMs are present. It checks checksum and interrogates the SPDs
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *
 *     @return  TRUE  - indicates that a FATAL error has not occurred
 *     @return  FALSE - indicates that a FATAL error has occurred
 */

BOOLEAN
MemTDIMMPresence4 (
  IN OUT   MEM_TECH_BLOCK *TechPtr
  )
{
  UINT8 Dct;
  UINT8 Channel;
  UINT8 i;
  MEM_PARAMETER_STRUCT *RefPtr;
  UINT8 *SpdBufferPtr;
  DIE_STRUCT *MCTPtr;
  DCT_STRUCT *DCTPtr;
  CH_DEF_STRUCT *ChannelPtr;
  MEM_NB_BLOCK *NBPtr;
  BOOLEAN SPDCtrl;
  UINT8 Devwidth;
  UINT8 BaseModuleType;
  UINT8 MaxDimms;
  UINT8 NumDimmslots;
  UINT8 Value8;
  UINT16 DimmMask;
  UINT32 DimmValidMask;

  SpdBufferPtr = NULL;

  NBPtr = TechPtr->NBPtr;
  RefPtr = NBPtr->RefPtr;
  MCTPtr = NBPtr->MCTPtr;

  ASSERT (TechPtr != NULL);
  ASSERT (NBPtr != NULL);
  ASSERT (MCTPtr != NULL);
  ASSERT (NBPtr->PsPtr != NULL);

  SPDCtrl = RefPtr->IgnoreSpdChecksum;
  DimmValidMask = 0;
  IDS_HDT_CONSOLE(MEM_FLOW, "DimmPresence Detection\n");
  IDS_HDT_CONSOLE(MEM_FLOW, "NBPtr->DctCount = %d\n",  NBPtr->DctCount);

  for (Dct = 0; Dct < NBPtr->DctCount; Dct++) {
    IDS_HDT_CONSOLE (MEM_STATUS, "\tDct %d\n", Dct);
    NBPtr->SwitchDCT (NBPtr, Dct);
    DCTPtr = NBPtr->DCTPtr;
    for (Channel = 0; Channel < NBPtr->ChannelCount; Channel++) {
      NBPtr->SwitchChannel (NBPtr, Channel);
      ChannelPtr = NBPtr->ChannelPtr;
      ChannelPtr->DimmQrPresent = 0;
      ChannelPtr->Loads = 0;
      ChannelPtr->Dimms = 0;
      ChannelPtr->Ranks = 0;
      //
      // Get the maximum number of DIMMs
      //
      MaxDimms = MAX_DIMMS_PER_CHANNEL;
      NumDimmslots = GetMaxDimmsPerChannel (NBPtr->RefPtr->PlatformMemoryConfiguration,
                                            MCTPtr->SocketId,
                                            ChannelPtr->ChannelID);
      DimmValidMask |= (NumDimmslots == 3) ? 0x7 : 0x3;

      for (i = 0; i < MaxDimms; i++) {
        IDS_HDT_CONSOLE(MEM_FLOW, "\t\tDimm %d\n", i);
        //  Bitmask representing dimm #i.
        DimmMask = (UINT16)1 << i;
        //
        if (MemTGetDimmSpdBuffer4 (TechPtr, &SpdBufferPtr, i)) {
          MCTPtr->DimmPresent |= DimmMask;
          //
          //  Check for valid checksum value
          //
          AGESA_TESTPOINT (TpProcMemSPDChecking, &(NBPtr->MemPtr->StdHeader));
          if (SpdBufferPtr[SPD_DRAM_DEVICE_TYPE] == DEVICE_TYPE_DDR4) {
            ChannelPtr->ChDimmValid |= DimmMask;
            MCTPtr->DimmValid |= DimmMask;
            IDS_HDT_CONSOLE(MEM_FLOW, "\t\t\tDDR4 Detected\n");
          } else {
            // Current socket is set up to only support DDR4 dimms.
            IDS_ERROR_TRAP;
          }
          if ((!MemTCRCCheck4 (SpdBufferPtr) || !MemTCRCCheck4 (SpdBufferPtr + 128)) && !NBPtr->IsSupported[AMPIsEnabled]) {
            IDS_HDT_CONSOLE(MEM_FLOW, "\t\t\tSPD Checksum Failed\n");
            //
            // NV_SPDCHK_RESTRT is set to 0,
            // cannot ignore faulty SPD checksum
            //
            //  Indicate checksum error
            if (!SPDCtrl) {
              ChannelPtr->DimmSpdCse |= DimmMask;
            }
            PutEventLog (AGESA_ERROR, MEM_ERROR_CHECKSUM_NV_SPDCHK_RESTRT_ERROR, NBPtr->Node, NBPtr->Dct, NBPtr->Channel, 0, &NBPtr->MemPtr->StdHeader);
            SetMemError (AGESA_ERROR, MCTPtr);
          }
          NBPtr->PsPtr->SpdDramType = DEVICE_TYPE_DDR4;
          //
          //  Check module type information.
          //
          BaseModuleType = SpdBufferPtr[SPD_BASE_MODULE_TYPE] & MODULE_TYPE_MASK;
          NBPtr->PsPtr->SpdModuleType = BaseModuleType;
          if (BaseModuleType == MOD_TYPE_LRDIMM) {
            //
            // LRDIMMS
            //
            if (i < NumDimmslots) {
              ChannelPtr->LrDimmPresent |= DimmMask;
              MCTPtr->LrDimmPresent |= DimmMask;

              if (!RefPtr->MemoryLRDimmCapable) {
                PutEventLog (AGESA_WARNING, MEM_WARNING_UNSUPPORTED_LRDIMM, NBPtr->Node, NBPtr->Dct, NBPtr->Channel, 0, &NBPtr->MemPtr->StdHeader);
                IDS_ERROR_TRAP;
              }
              TechPtr->TechnologySpecificHook[LrdimmPresence] (TechPtr, &i);
            }
          }
          if (BaseModuleType == MOD_TYPE_RDIMM) {
            //
            // RDIMMS
            //
            ChannelPtr->RegDimmPresent |= DimmMask;
            MCTPtr->RegDimmPresent |= DimmMask;
            if (!RefPtr->MemoryRDimmCapable) {
              PutEventLog (AGESA_WARNING, MEM_WARNING_UNSUPPORTED_RDIMM, NBPtr->Node, NBPtr->Dct, NBPtr->Channel, 0, &NBPtr->MemPtr->StdHeader);
              IDS_ERROR_TRAP;
            }
          }
          if ((BaseModuleType == MOD_TYPE_UDIMM) && !RefPtr->MemoryUDimmCapable) {
            PutEventLog (AGESA_WARNING, MEM_WARNING_UNSUPPORTED_UDIMM, NBPtr->Node, NBPtr->Dct, NBPtr->Channel, 0, &NBPtr->MemPtr->StdHeader);
            IDS_ERROR_TRAP;
          }
          if ((BaseModuleType == MOD_TYPE_SODIMM) || (BaseModuleType == MOD_TYPE_72b_SO_UDIMM)) {
            IDS_HDT_CONSOLE(MEM_FLOW, "\t\t\tSODIMM Module found.\n");
            ChannelPtr->SODimmPresent |= DimmMask;
            if (!RefPtr->MemorySODimmCapable) {
              PutEventLog (AGESA_WARNING, MEM_WARNING_UNSUPPORTED_SODIMM, NBPtr->Node, NBPtr->Dct, NBPtr->Channel, 0, &NBPtr->MemPtr->StdHeader);
              IDS_ERROR_TRAP;
            }
          }
          //
          //  Check error correction type
          //
          if ((SpdBufferPtr[SPD_BUSWIDTH_EXT] & BUSWIDTH_EXT_ECC) != 0) {
            MCTPtr->DimmEccPresent |= DimmMask;  //  Dimm has ECC
            IDS_HDT_CONSOLE(MEM_FLOW, "\t\t\tEcc Capable\n", i);
          }
          //
          //  Get the Dimm width data
          //
          Devwidth = SpdBufferPtr[SPD_DEVICE_WIDTH] & DEVICE_WIDTH_MASK;
          switch (Devwidth) {
          case 0:
            ChannelPtr->Dimmx4Present |= DimmMask;
            if ((ChannelPtr->LrDimmPresent & DimmMask) == 0) {
              //
              // DimmNibbleAccess indicates that a DIMM will use nibble signaling and use nibble training.
              // LRDIMMs will not use Nibble based signaling even if x4 parts are present.
              //
              if (i < NumDimmslots) {
                ChannelPtr->DimmNibbleAccess |= DimmMask;
              }
            }
            Devwidth = 4;
            break;
          case 1:
            ChannelPtr->Dimmx8Present |= DimmMask;
            Devwidth = 8;
            break;
          case 2:
            ChannelPtr->Dimmx16Present |= DimmMask;
            Devwidth = 16;
            break;
          default:
            IDS_ERROR_TRAP;
          }
          IDS_HDT_CONSOLE(MEM_FLOW, "\t\t\tDevice Width: %d\n", Devwidth);
          //
          //  Determine the geometry of the DIMM module
          //  specify the number of ranks
          //
          Value8 = ((SpdBufferPtr[SPD_RANKS] >> RANKS_SHIFT) & RANKS_MASK) + 1;
          if (Value8 == 5) {
            // Octal Rank
            Value8 = 8;
          }
          IDS_HDT_CONSOLE(MEM_FLOW, "\t\t\tRanks : %d\n", Value8);
          //
          // For LRDIMMS we will assume that if there are at least 4 Physical ranks, then it Could be used
          // as a QR RDIMM with a rank Mux of x1 and therefore all four CS will be used. So an 8R LRDIMM will
          // be marked as a QR even if Rank multiplication allows it to use only 2 logical ranks.
          //
          if ((ChannelPtr->LrDimmPresent & DimmMask) != 0) {
            //
            // LRDIMM Physical Ranks
            //
            ChannelPtr->LrdimmPhysicalRanks[i] = Value8;
          }
          if (Value8 > 2) {
            if (!RefPtr->MemoryQuadRankCapable) {
              PutEventLog (AGESA_WARNING, MEM_WARNING_UNSUPPORTED_QRDIMM, NBPtr->Node, NBPtr->Dct, NBPtr->Channel, 0, &NBPtr->MemPtr->StdHeader);
            }
            //
            // Mark this Dimm as Quad Rank
            //
            IDS_HDT_CONSOLE(MEM_FLOW, "\t\t\tQuad Rank Detected\n");
            ChannelPtr->DimmQrPresent |= DimmMask;
            Value8 = 2;
            RefPtr->EnableDllPDBypassMode = FALSE;
          } else if (Value8 == 2) {
            ChannelPtr->DimmDrPresent |= DimmMask;   //  Dual rank dimms
          } else {
            ChannelPtr->DimmSRPresent |= DimmMask;   //  Single rank dimms
          }
          //
          //  Calculate bus loading per Channel
          //
          if (Devwidth == 16) {
            Devwidth = 4;
          } else if (Devwidth == 4) {
            Devwidth = 16;
          }
          //
          //  Double Addr bus load value for dual rank DIMMs (Unless LRDIMM)
          //
          if (((ChannelPtr->LrDimmPresent & DimmMask) == 0) && (Value8 == 2) ) {
            Devwidth = Devwidth << 1;
          }
          //
          ChannelPtr->Ranks = ChannelPtr->Ranks + Value8;
          ChannelPtr->Loads = ChannelPtr->Loads + Devwidth;
          if ((i < NumDimmslots) || ((ChannelPtr->DimmQrPresent & DimmMask) == 0)) {
            ChannelPtr->Dimms++;
          }
          //
          // Check address mirror support for Unbuffered Dimms or LRDimms
          //
          if ((ChannelPtr->RegDimmPresent & DimmMask) == 0) {
            if ((SpdBufferPtr[SPD_ADDRMAP] & ADDRMAP_MASK) != 0) {
              ChannelPtr->DimmMirrorPresent |= DimmMask;
            }
          }
          //
          // Check for an On-DIMM Thermal Sensor
          //
          if (((SpdBufferPtr[SPD_THERMAL_SENSOR] >> THERMAL_SENSOR_SHIFT) & THERMAL_SENSOR_MASK) != 0) {
            ChannelPtr->DimmThermSensorPresent |= DimmMask;
          }
          //
          // Reference Raw Card information
          //
          ChannelPtr->RefRawCard[i] = SpdBufferPtr[SPD_RAWCARD] & RAWCARD_MASK;
          //
          // Copy the number of registers to the Ps Block to persist across frequency changes
          //
          NBPtr->PsPtr->NumOfReg[i] = SpdBufferPtr[SPD_NUM_REGISTERS] & NUM_REGISTERS_MASK;
          //
          // Workaround for RDIMMs with value if Zero for # of Registers
          //
          if (NBPtr->PsPtr->NumOfReg[i] == NUM_REGISTERS_UNDEF) {
            NBPtr->PsPtr->NumOfReg[i] = 1;
          }
        } // if DIMM present
      } // Dimm loop

      if (Channel == 0) {
        DCTPtr->Timings.DctDimmValid = ChannelPtr->ChDimmValid;
        DCTPtr->Timings.DimmMirrorPresent = ChannelPtr->DimmMirrorPresent;
        DCTPtr->Timings.DimmSpdCse = ChannelPtr->DimmSpdCse;
        DCTPtr->Timings.DimmQrPresent = ChannelPtr->DimmQrPresent;
        DCTPtr->Timings.DimmDrPresent = ChannelPtr->DimmDrPresent;
        DCTPtr->Timings.DimmSRPresent = ChannelPtr->DimmSRPresent;
        DCTPtr->Timings.Dimmx4Present = ChannelPtr->Dimmx4Present;
        DCTPtr->Timings.Dimmx8Present = ChannelPtr->Dimmx8Present;
        DCTPtr->Timings.Dimmx16Present = ChannelPtr->Dimmx16Present;
      }
      if ((Channel != 1) || (Dct != 1)) {
        MCTPtr->DimmPresent <<= 8;
        MCTPtr->DimmValid <<= 8;
        MCTPtr->RegDimmPresent <<= 8;
        MCTPtr->LrDimmPresent <<= 8;
        MCTPtr->DimmEccPresent <<= 8;
        MCTPtr->DimmParPresent <<= 8;
        DimmValidMask <<= 8;
      }
    } // Channel loop
  } // DCT loop

  //  If we have DIMMs, some further general characteristics checking
  if (MCTPtr->DimmValid != 0) {
    IDS_HDT_CONSOLE(MEM_FLOW, "Dimms Found.\n");
    //  If there are registered dimms, all the dimms must be registered
    if (MCTPtr->RegDimmPresent == MCTPtr->DimmValid) {
      //  All dimms registered
      MCTPtr->Status[SbRegistered] = TRUE;
      MCTPtr->Status[SbParDimms] = TRUE;  //  All DDR4 RDIMMs are parity capable
    } else if (MCTPtr->RegDimmPresent != 0) {
      //  We have an illegal DIMM mismatch
      PutEventLog (AGESA_FATAL, MEM_ERROR_MODULE_TYPE_MISMATCH_DIMM, NBPtr->Node, NBPtr->Dct, NBPtr->Channel, 0, &NBPtr->MemPtr->StdHeader);
      SetMemError (AGESA_FATAL, MCTPtr);
      ASSERT (FALSE);
    }
    //  If there are LrDimms, all the dimms must be LrDimms
    if (MCTPtr->LrDimmPresent == (MCTPtr->DimmValid & DimmValidMask)) {
      //  All dimms LRDIMMs
      MCTPtr->Status[SbLrdimms] = TRUE;
      MCTPtr->Status[SbParDimms] = TRUE;  //  All DDR4 RDIMMs are parity capable
    } else if (MCTPtr->LrDimmPresent != 0) {
      //  We have an illegal DIMM mismatch
      PutEventLog (AGESA_FATAL, MEM_ERROR_MODULE_TYPE_MISMATCH_DIMM, NBPtr->Node, NBPtr->Dct, NBPtr->Channel, 0, &NBPtr->MemPtr->StdHeader);
      SetMemError (AGESA_FATAL, MCTPtr);
      ASSERT (FALSE);
    }
    //
    //  Check the ECC capability of the DIMMs
    //
    if (MCTPtr->DimmEccPresent == MCTPtr->DimmValid) {
      MCTPtr->Status[SbEccDimms] = TRUE;  //  All dimms ECC capable
    }
  } else {
  }
  IDS_HDT_CONSOLE(MEM_FLOW, "Dimm Presence Complete.\n");
  NBPtr->SwitchDCT (NBPtr, 0);
  NBPtr->SwitchChannel (NBPtr, 0);
  return (BOOLEAN) (MCTPtr->ErrCode < AGESA_FATAL);
}


/* -----------------------------------------------------------------------------*/
/**
 *
 *   This function finds the maximum frequency that each channel is capable to run at.
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *
 *     @return  TRUE  - indicates that a FATAL error has not occurred
 *     @return  FALSE - indicates that a FATAL error has occurred
 */

BOOLEAN
MemTSPDGetTargetSpeed4 (
  IN OUT   MEM_TECH_BLOCK *TechPtr
  )
{
  UINT8 *SpdBufferPtr;
  UINT8 Dimm;
  UINT8 Dct;
  UINT8 Channel;
  INT32 MTB_ps;
  INT32 FTB_ps;
  INT32 TCKmin_ps;
  INT32 Value32;
  MEM_NB_BLOCK *NBPtr;
  DCT_STRUCT *DCTPtr;
  CH_DEF_STRUCT *ChannelPtr;

  SpdBufferPtr = NULL;

  NBPtr = TechPtr->NBPtr;

  IDS_HDT_CONSOLE (MEM_FLOW, "\tDetermine Max Frequency based on highest tCKmin from SPD.\n");
  for (Dct = 0; Dct < NBPtr->DctCount; Dct++) {
    NBPtr->SwitchDCT (NBPtr, Dct);
    DCTPtr = NBPtr->DCTPtr;
    TCKmin_ps = 0;
    for (Channel = 0; Channel < NBPtr->ChannelCount; Channel++) {
      NBPtr->SwitchChannel (NBPtr, Channel);
      ChannelPtr = NBPtr->ChannelPtr;
      for (Dimm = 0; Dimm < MAX_DIMMS_PER_CHANNEL; Dimm++) {
        if ((ChannelPtr->ChDimmValid & ((UINT8)1 << Dimm)) != 0) {
          MemTGetDimmSpdBuffer4 (TechPtr, &SpdBufferPtr, Dimm);
          //
          // Determine tCKmin(all) which is the largest tCKmin
          // value for all modules on the memory Channel.
          //
          MTB_ps = MemTGetMTB (TechPtr, SpdBufferPtr);
          FTB_ps = MemTGetFTB (TechPtr, SpdBufferPtr);
          Value32 = (MTB_ps * SpdBufferPtr[SPD_TCK]) + (FTB_ps * (INT8) SpdBufferPtr[SPD_TCK_FTB]) ;
          if (TCKmin_ps < Value32) {
            TCKmin_ps = Value32;
          }
        }
      }
    }
    if (TCKmin_ps <= 834) {
      DCTPtr->Timings.TargetSpeed = DDR2400_FREQUENCY;
    } else if (TCKmin_ps <= 938) {
      DCTPtr->Timings.TargetSpeed = DDR2133_FREQUENCY;
    } else if (TCKmin_ps <= 1071) {
      DCTPtr->Timings.TargetSpeed = DDR1866_FREQUENCY;
    } else if (TCKmin_ps <= 1250) {
      DCTPtr->Timings.TargetSpeed = DDR1600_FREQUENCY;
    } else if (TCKmin_ps <= 1500) {
      DCTPtr->Timings.TargetSpeed = DDR1333_FREQUENCY;
    } else if (TCKmin_ps <= 1875) {
      DCTPtr->Timings.TargetSpeed = DDR1066_FREQUENCY;
    } else if (TCKmin_ps <= 2500) {
      DCTPtr->Timings.TargetSpeed = DDR800_FREQUENCY;
    } else {
      DCTPtr->Timings.TargetSpeed = DDR667_FREQUENCY;
    }
    IDS_HDT_CONSOLE (MEM_FLOW, "\t\tDCT%d Max Frequency = %d MHz\n", Dct, NBPtr->DCTPtr->Timings.TargetSpeed);
  }


  // Ensure the target speed can be applied to all channels of the current node
  NBPtr->SyncTargetSpeed (NBPtr);

  // Set the start-up frequency
  for (Dct = 0; Dct < NBPtr->DctCount; Dct++) {
    NBPtr->SwitchDCT (NBPtr, Dct);
    NBPtr->DCTPtr->Timings.Speed = TechPtr->NBPtr->StartupSpeed;
  }
  return (BOOLEAN) (NBPtr->MCTPtr->ErrCode < AGESA_FATAL);
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *   This function check the symmetry of DIMM pairs (DIMM on Channel A matching with
 *   DIMM on Channel B), the overall DIMM population, and determine the width mode:
 *   64-bit, 64-bit muxed, 128-bit.
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *
 *     @return  TRUE  - indicates that a FATAL error has not occurred
 *     @return  FALSE - indicates that a FATAL error has occurred
 */

BOOLEAN
MemTSPDCalcWidth4 (
  IN OUT   MEM_TECH_BLOCK *TechPtr
  )
{
  UINT8 *SpdBufferAPtr;
  UINT8 *SpdBufferBPtr;
  MEM_NB_BLOCK *NBPtr;
  DIE_STRUCT *MCTPtr;
  DCT_STRUCT *DCTPtr;
  UINT8 i;
  UINT16 DimmMask;
  UINT8 UngangMode;
  MEM_PARAMETER_STRUCT *RefPtr;

  SpdBufferAPtr = NULL;
  SpdBufferBPtr = NULL;

  NBPtr = TechPtr->NBPtr;
  MCTPtr = NBPtr->MCTPtr;
  DCTPtr = NBPtr->DCTPtr;
  RefPtr = NBPtr->MemPtr->ParameterListPtr;
  UngangMode = RefPtr->MemoryModeUnganged;
  // Does not support ganged mode for DDR4 dimms
  ASSERT (UngangMode);
  IDS_OPTION_HOOK (IDS_GANGING_MODE, &UngangMode, &(NBPtr->MemPtr->StdHeader));

  //  Check symmetry of channel A and channel B dimms for 128-bit mode
  //  capability.
  //
  AGESA_TESTPOINT (TpProcMemModeChecking, &(NBPtr->MemPtr->StdHeader));
  i = 0;
  if (!UngangMode) {
    if (MCTPtr->DctData[0].Timings.DctDimmValid == MCTPtr->DctData[1].Timings.DctDimmValid) {
      for (; i < MAX_DIMMS_PER_CHANNEL; i++) {
        DimmMask = (UINT16)1 << i;
        if ((DCTPtr->Timings.DctDimmValid & DimmMask) != 0) {
          NBPtr->SwitchDCT (NBPtr, 0);
          MemTGetDimmSpdBuffer4 (TechPtr, &SpdBufferAPtr, i);
          NBPtr->SwitchDCT (NBPtr, 1);
          MemTGetDimmSpdBuffer4 (TechPtr, &SpdBufferBPtr, i);
          // compare rows and columns
          if ((SpdBufferAPtr[SPD_ROWS_COLS] & ROW_COL_MASK) != (SpdBufferBPtr[SPD_ROWS_COLS] & ROW_COL_MASK)) {
            break;
          }
          if ((SpdBufferAPtr[SPD_CAPACITY] & CAPACITY_MASK) != (SpdBufferBPtr[SPD_CAPACITY] & CAPACITY_MASK)) {
            break;
          }
          // compare ranks and devwidth
          if ((SpdBufferAPtr[SPD_DEVICE_WIDTH] & DEVICE_WIDTH_MASK) != (SpdBufferBPtr[SPD_DEVICE_WIDTH] & DEVICE_WIDTH_MASK)) {
            break;
          }
        }
      }
    }
    if (i < MAX_DIMMS_PER_CHANNEL) {
      PutEventLog (AGESA_ALERT, MEM_ALERT_ORG_MISMATCH_DIMM, NBPtr->Node, NBPtr->Dct, NBPtr->Channel, 0, &NBPtr->MemPtr->StdHeader);
      SetMemError (AGESA_ALERT, MCTPtr);
    } else {
      NBPtr->Ganged = TRUE;
      MCTPtr->GangedMode = TRUE;
      MCTPtr->Status[Sb128bitmode] = TRUE;
      NBPtr->SetBitField (NBPtr, BFDctGangEn, 1);
    }
  }

  return (BOOLEAN) (MCTPtr->ErrCode < AGESA_FATAL);
}


/* -----------------------------------------------------------------------------*/
/**
 *
 *       Initialize DCT Timing registers as per DIMM SPD.
 *       For primary timing (T, CL) use best case T value.
 *       For secondary timing params., use most aggressive settings
 *           of slowest DIMM.
 *
 *   Note:
 *   There are three components to determining "maximum frequency": SPD component,
 *   Bus load component, and "Preset" max frequency component.
 *   The SPD component is a function of the min cycle time specified by each DIMM,
 *   and the interaction of cycle times from all DIMMs in conjunction with CAS
 *   latency.  The SPD component only applies when user timing mode is 'Auto'.
 *
 *   The Bus load component is a limiting factor determined by electrical
 *   characteristics on the bus as a result of varying number of device loads.  The
 *   Bus load component is specific to each platform but may also be a function of
 *   other factors.  The bus load component only applies when user timing mode is
 * ' Auto'.
 *
 *   The Preset component is subdivided into three items and is the minimum of
 *   the set: Silicon revision, user limit setting when user timing mode is 'Auto' and
 *   memclock mode is 'Limit', OEM build specification of the maximum frequency.
 *   The Preset component only applies when user timing mode is 'Auto'.
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *
 *     @return  TRUE  - indicates that a FATAL error has not occurred
 *     @return  FALSE - indicates that a FATAL error has occurred
 */

BOOLEAN
MemTAutoCycTiming4 (
  IN OUT   MEM_TECH_BLOCK *TechPtr
  )
{
  CONST UINT8 SpdIndexes[] = {
    SPD_TRCD,
    SPD_TRP,
    0,
    SPD_TRAS_LSB,
    SPD_TRC_LSB,
    SPD_TWR,              // No TWR in early DDR4 SPD
    SPD_TRRD_S,
    SPD_TWTR_S,           // No TWTR in early DDR4 SPD
    SPD_TFAW_LSB,
    SPD_TRRD_L,
    SPD_TWTR_L,           // No TWTR_L in early DDR4 SPD
    SPD_TCCD_L            //
  };

  CONST UINT8 SpdFTBIndexes[] = {
    SPD_TRCD_FTB,
    SPD_TRP_FTB,
    0,
    0,
    SPD_TRC_FTB,
    0,
    SPD_TRRD_S_FTB,
    0,
    0,
    SPD_TRRD_L_FTB,
    0,
    SPD_TCCD_L_FTB
  };

  UINT8  *SpdBufferPtr;
  INT32  MiniMaxTmg[GET_SIZE_OF (SpdIndexes)];
  UINT16  MiniMaxTrfc[4];
  INT32  MiniMaxTrfc4;

  DIE_STRUCT *MCTPtr;
  DCT_STRUCT *DCTPtr;
  MEM_NB_BLOCK *NBPtr;
  UINT16 DimmMask;
  INT32 Value32;
  INT32 JedecMin;
  INT32 MTB_ps;
  INT32 FTB_ps;
  INT32 TCK_ps;
  UINT8 i;
  UINT8 j;
  UINT16 Value16;
  UINT8  *StatTmgPtr;
  UINT16 *StatDimmTmgPtr;
  UINT16  PageSize;

  SpdBufferPtr = NULL;

  NBPtr = TechPtr->NBPtr;
  MCTPtr = NBPtr->MCTPtr;
  DCTPtr = NBPtr->DCTPtr;
  // initialize mini-max arrays
  for (j = 0; j < GET_SIZE_OF (MiniMaxTmg); j++) {
    MiniMaxTmg[j] = 0;
  }
  for (j = 0; j < GET_SIZE_OF (MiniMaxTrfc); j++) {
    MiniMaxTrfc[j] = 0;
  }

  MiniMaxTrfc4 = 0;

  TCK_ps = 1000500 / DCTPtr->Timings.Speed;

  // ======================================================================
  //  Get primary timing (CAS Latency and Cycle Time)
  // ======================================================================
  //  Get OEM specific load variant max
  //

  //======================================================================
  // Gather all DIMM mini-max values for cycle timing data
  //======================================================================
  //
  DimmMask = 1;
  for (i = 0; i < (MAX_CS_PER_CHANNEL / 2); i++) {
    IDS_HDT_CONSOLE (MEM_STATUS, "\n\t\t\tDimm %d\n", i);
    if ((DCTPtr->Timings.DctDimmValid & DimmMask) != 0) {
      MemTGetDimmSpdBuffer4 (TechPtr, &SpdBufferPtr, i);
      MTB_ps = MemTGetMTB (TechPtr, SpdBufferPtr);
      FTB_ps = MemTGetFTB (TechPtr, SpdBufferPtr);
      // Calculate Page Size (2 Pow ColBits * DQBits/8)
      //
      PageSize = (1 << (9 + (SpdBufferPtr[SPD_COL_ADDR_BITS] & COL_ADDR_BITS_MASK))) *
                 ((1 << (2 + (SpdBufferPtr[SPD_DEVICE_WIDTH] & DEVICE_WIDTH_MASK))) / 8);

      IDS_HDT_CONSOLE (MEM_FLOW, "\t\t\t\tPage Size = %d Bytes\n", PageSize);
      IDS_HDT_CONSOLE (MEM_FLOW, "\t\t\t\tMTB(pS)  = %d\tFTB(pS)  = %d\n\n", MTB_ps,FTB_ps);
      IDS_HDT_CONSOLE (MEM_FLOW, "\t\t\t\tSPD Byte    Time in pS  (* = new max)\n");

      for (j = 0; j < GET_SIZE_OF (SpdIndexes); j++) {
        if (SpdIndexes[j] != 0) {
          // Process Supported Entries only
          Value32 = (UINT16)SpdBufferPtr[SpdIndexes[j]];
          IDS_HDT_CONSOLE (MEM_FLOW, "\t\t\t\t   %02d   ", (UINT8) SpdIndexes[j]);
          if (SpdIndexes[j] == SPD_TRC_LSB) {
            Value32 |= ((UINT16)SpdBufferPtr[SPD_TRC_UPPERNIBBLE] & 0xF0) << 4;
          } else if (SpdIndexes[j] == SPD_TRAS_LSB) {
            Value32 |= ((UINT16)SpdBufferPtr[SPD_TRAS_UPPERNIBBLE] & 0x0F) << 8;
          } else if (SpdIndexes[j] == SPD_TFAW_LSB) {
            Value32 |= ((UINT16)SpdBufferPtr[SPD_TFAW_UPPERNIBBLE] & 0x0F) << 8;
          }

          Value32 *= MTB_ps;
          if (SpdFTBIndexes[j] != 0) {
            Value32 += (FTB_ps * (INT8) SpdBufferPtr[SpdFTBIndexes[j]]) ;
          }

          if (SpdIndexes[j] == SPD_TCCD_L) {
            //
            // If tCCD_Lmin is unspecified, use value from the JEDEC DDR4 Spec:
            //
            JedecMin = (( DCTPtr->Timings.Speed <= DDR1333_FREQUENCY ) ? 4 :   // 4nCK  Data rate <= 1333
                        (( DCTPtr->Timings.Speed <= DDR1866_FREQUENCY ) ? 5 :   // 5nCK  1333 < Data rate <= 1866
                        (( DCTPtr->Timings.Speed <= DDR2400_FREQUENCY ) ? 6 :   // 6nCK  1866 < Data rate <= 2400
                                                                          7))); // 7nCK  Data rate > 2400
            JedecMin *= TCK_ps;
            if (Value32 == 0 || Value32 < JedecMin) {
              // Convert to pS
              Value32 = JedecMin;
            }
            ASSERT (Value32 <= 8 * TCK_ps);
          }

          if (SpdIndexes[j] == SPD_TWR) {
            if (Value32 == 0) {
              //
              // If tWRmin is not specified in the SPD, use JEDEC minimum of 15nS
              //
              Value32 = 15000;
            }
          }

          if (SpdIndexes[j] == SPD_TWTR_S) {
            if (Value32 == 0) {
              //
              // If tWTR_Smin is not specified in the SPD, use JEDEC minimum of MAX(2nCK, 2.5nS)
              //
              Value32 = MAX ((2 * TCK_ps), 2500);
            }
          }

          if (SpdIndexes[j] == SPD_TWTR_L) {
            if (Value32 == 0) {
              //
              // If tWTR_Lmin is not specified in the SPD, use JEDEC minimum of MAX(4nCK, 7.5nS)
              //
              Value32 = MAX ((4 * TCK_ps), 7500);
            }
          }

          IDS_HDT_CONSOLE (MEM_FLOW, "    %05d", Value32);
          // Enforce JEDEC Minimum nCK values.
          //
          JedecMin = TCK_ps * (INT32) MemTGetJedecMinClks (SpdIndexes[j], PageSize);
          if (JedecMin > Value32) {
            Value32 = JedecMin;
            IDS_HDT_CONSOLE (MEM_FLOW, " Jedec Min Applied --> %05d", Value32);
          }
          //
          // Choose Max Value
          //
          if (MiniMaxTmg[j] < Value32) {
            MiniMaxTmg[j] = Value32;
            IDS_HDT_CONSOLE (MEM_FLOW, " *"); // Indicate new max
          }
          IDS_HDT_CONSOLE (MEM_FLOW, "\n");
        }
      }
      //
      //  Get Trfc0 - Trfc3 values
      //
      Value16 = SpdBufferPtr[SPD_TRFC1_MSB] << 8;
      Value16 |= SpdBufferPtr[SPD_TRFC1_LSB];
      Value32 = Value16 * MTB_ps;
      MiniMaxTrfc[i] = (UINT16) (Value32 / 1000);
      //
      // Get tRFC4
      //
      Value16 = SpdBufferPtr[SPD_TRFC4_MSB] << 8;
      Value16 |= SpdBufferPtr[SPD_TRFC4_LSB];
      Value32 = Value16 * MTB_ps;
      IDS_HDT_CONSOLE (MEM_FLOW, "\t\t\t\t   Trfc4     %05d", Value32);
      if (MiniMaxTrfc4 < Value32) {
        MiniMaxTrfc4 = Value32;
        IDS_HDT_CONSOLE (MEM_FLOW, " *"); // Indicate new max
      }
    }
    DimmMask <<= 1;
  }
  MiniMaxTmg[2] = 7500;

  // ======================================================================
  //  Convert  DRAM CycleTiming values and store into DCT structure
  // ======================================================================
  //

  IDS_HDT_CONSOLE (MEM_FLOW, "\t\tTCK = %d pS @ %dMHz\n", TCK_ps, DCTPtr->Timings.Speed);

  StatDimmTmgPtr = &DCTPtr->Timings.DIMMTrcd;
  StatTmgPtr = &DCTPtr->Timings.Trcd;
  IDS_HDT_CONSOLE (MEM_FLOW, "\t\t\t\tSPD Byte    Time in pS    nCK Value\n");
  for (j = 0; j < GET_SIZE_OF (SpdIndexes); j++) {
    Value32 = MiniMaxTmg[j];

    //
    // Use JEDEC DDR4 Rounding Rule to round down with a .01 Memclk guardband
    //
    MiniMaxTmg[j] = ((MiniMaxTmg[j] * 100) + (TCK_ps * 99)) / (TCK_ps * 100);
    IDS_HDT_CONSOLE (MEM_FLOW, "\t\t\t\t   %02d       %05d    %05d\n", (UINT8) SpdIndexes[j], Value32, MiniMaxTmg[j]);

    StatDimmTmgPtr[j] = (UINT16) (Value32 / (1000 / 40));
    StatTmgPtr[j] = (UINT8) MiniMaxTmg[j];
  }
  DCTPtr->Timings.Trfc0 = MiniMaxTrfc[0];
  DCTPtr->Timings.Trfc1 = MiniMaxTrfc[1];
  DCTPtr->Timings.Trfc2 = MiniMaxTrfc[2];
  DCTPtr->Timings.Trfc3 = MiniMaxTrfc[3];

  DCTPtr->Timings.Trfc4 = (UINT16) (MiniMaxTrfc4 / 1000);

  DCTPtr->Timings.CasL = MemTSPDGetTCL4 (TechPtr);
  IDS_HDT_CONSOLE (MEM_FLOW, "\t\tCAS Latency = %d\n", DCTPtr->Timings.CasL);
  DCTPtr->Timings.Trcpage = MemTSPDGetTrcpage4 (TechPtr);
  //======================================================================
  // Program DRAM Timing values
  //======================================================================
  //
  NBPtr->ProgramCycTimings (NBPtr);

  MemFInitTableDrive (NBPtr, MTAfterAutoCycTiming);

  IDS_HDT_CONSOLE (MEM_FLOW, "\n");

  return (BOOLEAN) (MCTPtr->ErrCode < AGESA_FATAL);
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *   This function sets the bank addressing, program Mask values and build a chip-select population map.
 *   This routine programs PCI 0:24N:2x80 config register.
 *   This routine programs PCI 0:24N:2x60,64,68,6C config registers (CS Mask 0-3)
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *
 *     @return  TRUE  - indicates that a FATAL error has not occurred
 *     @return  FALSE - indicates that a FATAL error has occurred
 */

BOOLEAN
MemTSPDSetBanks4 (
  IN OUT   MEM_TECH_BLOCK *TechPtr
  )
{
  UINT8 *SpdBufferPtr;
  UINT8 ChipSel;
  UINT8 DimmID;
  UINT16 Value16;
  UINT8 RowBits;
  UINT8 ColBits;
  UINT8 Ranks;
  UINT8 BankBits;
  UINT8 GroupBits;
  UINT8 Capacity;
  UINT32 BankAddrReg;
  UINT8 BankAddrVal;
  UINT32 CsMask;
  UINT16 CSSpdCSE;
  UINT16 CSExclude;
  UINT16 DimmQRDR;
  DIE_STRUCT *MCTPtr;
  DCT_STRUCT *DCTPtr;
  MEM_NB_BLOCK *NBPtr;

  SpdBufferPtr = NULL;

  NBPtr = TechPtr->NBPtr;
  MCTPtr = NBPtr->MCTPtr;
  DCTPtr = NBPtr->DCTPtr;
  BankAddrReg = 0;
  CSSpdCSE = 0;
  CSExclude = 0;

  IDS_HDT_CONSOLE (MEM_FLOW, "\n\t\t\t       Row    Col    Bank   Bank                 Totl   Bank\n");
  IDS_HDT_CONSOLE (MEM_FLOW, "\t\t\t       Addr   Addr   Addr   Group                Addr   Addr\n");
  IDS_HDT_CONSOLE (MEM_FLOW, "\t\t\tDimm   bits   bits   bits   bits   Ranks   Cap   Bits   Val\n");
  for (ChipSel = 0; ChipSel < MAX_CS_PER_CHANNEL; ChipSel += 2) {
    DimmID = ChipSel >> 1;

    DimmQRDR = (DCTPtr->Timings.DimmQrPresent) | (DCTPtr->Timings.DimmDrPresent);
    if ((DCTPtr->Timings.DimmSpdCse & ((UINT16) 1 << DimmID)) != 0) {
      CSSpdCSE |= (UINT16) ((DimmQRDR & (UINT16) 1 << DimmID) ? 3 : 1) << ChipSel;
    }
    if ((DCTPtr->Timings.DimmExclude & ((UINT16) 1 << DimmID)) != 0) {
      CSExclude |= (UINT16) ((DimmQRDR & (UINT16) 1 << DimmID) ? 3: 1) << ChipSel;
    }

    if ((DCTPtr->Timings.DctDimmValid & ((UINT16)1 << DimmID)) != 0) {
      MemTGetDimmSpdBuffer4 (TechPtr, &SpdBufferPtr, DimmID);
      //
      //  Get the basic data
      //
      RowBits   = 12 + ((SpdBufferPtr[SPD_ROW_ADDR_BITS] >> ROW_ADDR_BITS_SHIFT) & ROW_ADDR_BITS_MASK);
      ColBits   = 9 +   (SpdBufferPtr[SPD_COL_ADDR_BITS] & COL_ADDR_BITS_MASK);
      BankBits  = 2 +  ((SpdBufferPtr[SPD_BANK_ADDR_BITS] >> BANK_ADDR_BITS_SHIFT) & BANK_ADDR_BITS_MASK);
      GroupBits =       (SpdBufferPtr[SPD_BANK_GROUP_BITS] >> BANK_GROUP_BITS_SHIFT) & BANK_GROUP_BITS_MASK;
      Ranks     =      ((SpdBufferPtr[SPD_RANKS] >> RANKS_SHIFT) & RANKS_MASK) + 1;
      Capacity  =       (SpdBufferPtr[SPD_CAPACITY]) & CAPACITY_MASK;
      if (Ranks == 5) {
        Ranks = 8;
      }
      IDS_HDT_CONSOLE (MEM_FLOW, "\t\t\t  %d     %d     %d     %d      %d       %d      %d",
        DimmID, RowBits, ColBits, BankBits, GroupBits, Ranks, Capacity);

      if (MemTCheckBankAddr4 (&BankAddrVal, GroupBits, BankBits, RowBits, ColBits)) {
        //
        // Mask value = (2 pow(Rows + Cols + Banks + Group + 3 ) -1 ) >> 8,
        // or 2 pow(Rows + Cols + Banks + Group - 5 ) - 1
        //
        Value16 = (RowBits) + (ColBits) + (BankBits) + (GroupBits) + 3 - 8;
        IDS_HDT_CONSOLE (MEM_FLOW, "     %d     %02x\n", Value16, BankAddrVal);
        if (MCTPtr->Status[Sb128bitmode]) {
          Value16++;
        }

        DCTPtr->Timings.CsPresent |= (UINT16)1 << ChipSel;

        if (Ranks >= 2) {
          DCTPtr->Timings.CsPresent |= (UINT16)1 << (ChipSel + 1);
        }
        //
        // Determine LRDIMM Rank Multiplication
        //
        if (TechPtr->TechnologySpecificHook[LrdimmRankMultiplication] (TechPtr, &DimmID)) {
          //
          // Increase the CS Size by the rank multiplication factor
          //
          Value16 = Value16 + (UINT16) ((NBPtr->ChannelPtr->LrDimmRankMult[DimmID]) >> 1);
          CsMask = ((UINT32)1 << Value16) - 1;
          CsMask &= NBPtr->CsRegMsk;
          CsMask |= (NBPtr->GetBitField (NBPtr, BFRankDef0 + DimmID) & 0x03);
        } else {
          CsMask = ((UINT32)1 << Value16) - 1;
          CsMask &= NBPtr->CsRegMsk;
        }
        //
        //  Update the DRAM CS Mask and BankAddrReg for this chipselect
        //
        if ((DCTPtr->Timings.CsPresent & (UINT16)3 << ChipSel) != 0) {
          NBPtr->SetBitField (NBPtr, BFCSMask0Reg + (ChipSel >> 1), (CsMask));
          BankAddrReg |= ((UINT32)BankAddrVal << (ChipSel << 1));
        }
      } else {
        //
        // Dimm is not supported, as no address mapping is found.
        //
        DCTPtr->Timings.CsPresent |= (UINT16)1 << ChipSel;
        DCTPtr->Timings.CsTestFail |= (UINT16)1 << ChipSel;
        if (Ranks >= 2) {
          DCTPtr->Timings.CsPresent |= (UINT16)1 << (ChipSel + 1);
          DCTPtr->Timings.CsTestFail |= (UINT16)1 << (ChipSel + 1);
        }
        PutEventLog (AGESA_ERROR, MEM_ERROR_NO_ADDRESS_MAPPING, NBPtr->Node, NBPtr->Dct, NBPtr->Channel, DimmID, &NBPtr->MemPtr->StdHeader);
        SetMemError (AGESA_ERROR, MCTPtr);
        IDS_HDT_CONSOLE (MEM_FLOW, "     No Address Mapping Found\n");
      }
    } // if (MemTCheckBankAddr4 (&BankAddrVal, GroupBits, BankBits, RowBits, ColBits))
  }
  // For ranks that need to be excluded, the loading of this rank should be considered
  // in timing, so need to set CsPresent before setting CsTestFail
  if ((CSSpdCSE != 0) || (CSExclude != 0)) {
    if (!NBPtr->MemPtr->ErrorHandling (MCTPtr, NBPtr->Dct, (CSSpdCSE | CSExclude), &NBPtr->MemPtr->StdHeader)) {
      ASSERT (FALSE);
    }
  }

  //  If there are no chip selects, we have an error situation.
  if (DCTPtr->Timings.CsPresent == 0) {
    PutEventLog (AGESA_ERROR, MEM_ERROR_NO_CHIPSELECT, NBPtr->Node, NBPtr->Dct, NBPtr->Channel, 0, &NBPtr->MemPtr->StdHeader);
    SetMemError (AGESA_ERROR, MCTPtr);
  }
  IDS_HDT_CONSOLE (MEM_FLOW, "\t\t\tFinal Bank Address Value: %08x\n", BankAddrReg);
  NBPtr->SetBitField (NBPtr, BFDramBankAddrReg, BankAddrReg);
  return (BOOLEAN) (MCTPtr->ErrCode < AGESA_FATAL);
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *      This function returns the low bit that will be swapped to enable CS
 *      interleaving
 *
 *     @param[in,out] *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in]    BankAddrMap - AddrMap Bank encoding from F2x80
 *     @param[in]        *LowBit - pointer to low bit
 *     @param[in]        *HiBit  - pointer hight bit
 *
 */

VOID
MemTGetCSIntLvAddr4 (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 BankAddrMap,
  OUT   UINT8 *LowBit,
  OUT   UINT8 *HiBit
  )
{
  TechPtr->NBPtr->GetCSIntLvAddr (TechPtr->NBPtr, BankAddrMap, LowBit, HiBit);
  return;
}

/*----------------------------------------------------------------------------
 *                              LOCAL FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */

/* -----------------------------------------------------------------------------*/
/**
 *
 *       This function determines if the checksum is correct
 *
 *     @param[in]   *SPDPtr - Pointer to SPD data
 *
 *     @return    TRUE  - CRC check passes
 *     @return    FALSE - CRC check fails
 */

BOOLEAN
STATIC
MemTCRCCheck4 (
  IN OUT   UINT8 *SPDPtr
  )
{
  UINT16 Crc;
  INT16 i;
  INT16 j;
  INT16 Count;

  Count = 126;
  Crc = 0;
  for (j = 0; j < Count; j++) {
    Crc = Crc ^ ((UINT16)SPDPtr[j] << 8);
    for (i = 0; i < 8; i++) {
      if (Crc & 0x8000) {
        Crc = (Crc << 1) ^ 0x1021;
      } else {
        Crc = (Crc << 1);
      }
    }
  }
  if (*(UINT16 *) (SPDPtr + 126) == Crc) {
    return TRUE;
  } else {
    return FALSE;
  }
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *   This function returns the CAS latency of the current frequency (DCTPtr->Timings.Speed).
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *
 *     @return  CAS Latency
 */

UINT8
STATIC
MemTSPDGetTCL4 (
  IN OUT   MEM_TECH_BLOCK *TechPtr
  )
{
  UINT8  *SpdBufferPtr;
  UINT8 CLdesired;
  UINT8 CLactual;
  UINT8 Dimm;
  UINT8 Channel;
  UINT32 CASLat;
  UINT32 Mask32;
  INT32 MTB_ps;
  INT32 FTB_ps;
  INT32 TAAmin_ps;
  INT32 TCKproposed_ps;
  INT32 Value32;
  BOOLEAN CltFail;
  MEM_NB_BLOCK *NBPtr;
  DCT_STRUCT *DCTPtr;
  CH_DEF_STRUCT *ChannelPtr;

  SpdBufferPtr = NULL;

  NBPtr = TechPtr->NBPtr;
  DCTPtr = NBPtr->DCTPtr;

  CASLat = 0xFFFFFFFF;
  TAAmin_ps = 0;
  CltFail = FALSE;

  for (Channel = 0; Channel < NBPtr->ChannelCount; Channel++) {
    NBPtr->SwitchChannel (NBPtr, Channel);
    ChannelPtr = NBPtr->ChannelPtr;
    for (Dimm = 0; Dimm < MAX_DIMMS_PER_CHANNEL; Dimm++) {
      if ((ChannelPtr->ChDimmValid & ((UINT8)1 << Dimm)) != 0) {
        MemTGetDimmSpdBuffer4 (TechPtr, &SpdBufferPtr, Dimm);

        // Step 1: Determine the common set of supported CAS Latency
        // values for all modules on the memory Channel using the CAS
        // Latencies Supported in SPD bytes 14 and 15.
        //
        CASLat &= ((UINT32)SpdBufferPtr[SPD_CAS_BYTE_3] << 24) |
                  ((UINT32)SpdBufferPtr[SPD_CAS_BYTE_2] << 16) |
                  ((UINT32)SpdBufferPtr[SPD_CAS_BYTE_1] << 8)  |
                           SpdBufferPtr[SPD_CAS_BYTE_0];

        // Step 2: Determine tAAmin(all) which is the largest tAAmin
        // value for all modules on the memory Channel (SPD byte 16).
        //
        MTB_ps = MemTGetMTB (TechPtr, SpdBufferPtr);
        FTB_ps = MemTGetFTB (TechPtr, SpdBufferPtr);
        Value32 = (MTB_ps * SpdBufferPtr[SPD_TAA]) + (FTB_ps * (INT8) SpdBufferPtr[SPD_TAA_FTB]) ;
        if (TAAmin_ps < Value32) {
          TAAmin_ps = Value32;
        }

        // Step 3: Determine tCKmin(all) which is the largest tCKmin
        // value for all modules on the memory Channel (SPD byte 12).
        // * This step has been done in SPDGetTargetSpeed
      }
    }
  }

  TCKproposed_ps = 1000500 / DCTPtr->Timings.Speed;

  // Step 4: For a proposed tCK value (tCKproposed) between tCKmin(all) and tCKmax,
  // determine the desired CAS Latency. If tCKproposed is not a standard JEDEC
  // value (2.5, 1.875, 1.5, or 1.25 ns) then tCKproposed must be adjusted to the
  // next lower standard tCK value for calculating CLdesired.
  // CLdesired = ceiling ( tAAmin(all) / tCKproposed )
  // where tAAmin is defined in Byte 16. The ceiling function requires that the
  // quotient be rounded up always.
  //
  CLdesired = (UINT8) ((TAAmin_ps + TCKproposed_ps - 1) / TCKproposed_ps);

  // Step 5: Choose an actual CAS Latency (CLactual) that is greater than or equal
  // to CLdesired and is supported by all modules on the memory Channel as
  // determined in step 1. If no such value exists, choose a higher tCKproposed
  // value and repeat steps 4 and 5 until a solution is found.
  //
  CLactual = 7;
  for (Mask32 = 1; Mask32 < 0x80000000; Mask32 <<= 1) {
    if (CASLat & Mask32) {
      if (CLdesired <= CLactual) {
        break;
      }
    }
    CLactual++;
  }
  if (Mask32 == 0x80000000) {
    CltFail = TRUE;
  }

  // Step 6: Once the calculation of CLactual is completed, the BIOS must also
  // verify that this CAS Latency value does not exceed tAAmax, which is 20 ns
  // for all DDR4 speed grades, by multiplying CLactual times tCKproposed. If
  // not, choose a lower CL value and repeat steps 5 and 6 until a solution is found.
  //
  if ((TCKproposed_ps * CLactual) > 20000) {
    CltFail = TRUE;
  }

  if (!CltFail) {
    DCTPtr->Timings.CasL = CLactual;
  } else {
    //  Fail to find supported Tcl, use 6 clocks since it is required for all DDR4 speed bin.
    DCTPtr->Timings.CasL = 6;
  }

  if (NBPtr->RefPtr->CustomCasLatency != 0xFF) {
    DCTPtr->Timings.CasL = NBPtr->RefPtr->CustomCasLatency;
  }

  return DCTPtr->Timings.CasL;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *   This function returns Trcpage.
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *
 *     @return  Trcpage
 */

UINT8
STATIC
MemTSPDGetTrcpage4 (
  IN OUT   MEM_TECH_BLOCK *TechPtr
  )
{
  UINT8  *SpdBufferPtr;
  UINT8 Dimm;
  UINT32 Tmac;
  UINT32 TmacInCount;
  UINT32 Tmaw;
  UINT32 TmawInNs;
  UINT32 Trcpage;
  UINT32 TrcpageMin;
  MEM_NB_BLOCK *NBPtr;
  CH_DEF_STRUCT *ChannelPtr;
  MEM_PARAMETER_STRUCT *RefPtr;

  SpdBufferPtr = NULL;

  NBPtr = TechPtr->NBPtr;
  RefPtr = NBPtr->MemPtr->ParameterListPtr;

  TmacInCount = 0;
  TrcpageMin = 0;

  ChannelPtr = NBPtr->ChannelPtr;
  for (Dimm = 0; Dimm < MAX_DIMMS_PER_CHANNEL; Dimm++) {
    if ((ChannelPtr->ChDimmValid & ((UINT8)1 << Dimm)) != 0) {
      MemTGetDimmSpdBuffer4 (TechPtr, &SpdBufferPtr, Dimm);

      Tmac = SpdBufferPtr[SPD_MAC] & MAC_MASK;
      Tmaw = (SpdBufferPtr[SPD_TMAW] >> MAW_SHIFT) & MAW_MASK;

      if (Tmac == 0) {
        Tmac = (RefPtr->DramMacDefault == 0) ? 8 : RefPtr->DramMacDefault;
      }

      switch (Tmac) {
      case 0:
        // Unt*sted MAC
      case 7:
        // Reserved
      case 8:
        // Unrestricted MAC
        TmacInCount = 0;
        break;
      case 1:
        TmacInCount = 700000;
        break;
      case 2:
        TmacInCount = 600000;
        break;
      case 3:
        TmacInCount = 500000;
        break;
      case 4:
        TmacInCount = 400000;
        break;
      case 5:
        TmacInCount = 300000;
        break;
      case 6:
        TmacInCount = 200000;
        break;
      default:
        IDS_ERROR_TRAP;
      }

      TmawInNs = NBPtr->RefPtr->DramDoubleRefreshRateEn ? 3900 : 7800;
      switch (Tmaw) {
      case 0:
        TmawInNs *= 8192;
        break;
      case 1:
        TmawInNs *= 4096;
        break;
      case 2:
        TmawInNs *= 2048;
        break;
      case 3:
        TmawInNs = 0;
      default:
        IDS_ERROR_TRAP;
      }

      if (TmacInCount == 0 || TmawInNs == 0) {
        // Trcpage should be disabled
        Trcpage = 0;
        break;
      } else if (TmacInCount == 1) {
        Trcpage = 0;
      } else {
        Trcpage = (TmawInNs / TmacInCount + 9) / 10;
      }

      if (Trcpage > TrcpageMin) {
        TrcpageMin = Trcpage;
      }
    }
  }

  return (UINT8)TrcpageMin;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function returns the encoded value of the bank address.
 *
 *     @param[out]  *DimmAddrMap - Dimm Address Map value
 *     @param[in]   BGBits  - Number of Bank Group bits
 *     @param[in]   BABits  - Number of Bank Address bits
 *     @param[in]   RowBits - Number of Row Address bits
 *     @param[in]   ColBits - Number of Column Address bits
 *
 *     @return      TRUE   - encoded value is found.
 *                  FALSE  - encoded value is not found.
 */

BOOLEAN
STATIC
MemTCheckBankAddr4 (
  OUT   UINT8 *DimmAddrMap,
  IN       UINT8 BGBits,
  IN       UINT8 BABits,
  IN       UINT8 RowBits,
  IN       UINT8 ColBits
  )
{
  CONST DDR4_DRAM_ADDRESS_MAP DimmAddressMapTable[] = {
  // Value BG  BA   Row  Col
  // 0x00   Reserved
    { 0x01, 1,  2,  14,  10}, // 1G
    { 0x02, 2,  2,  14,  10}, // 2G
    { 0x03, 1,  2,  15,  10}, // 2G
    { 0x04, 2,  2,  15,  10}, // 4G
    { 0x05, 1,  2,  16,  10}, // 4G
    { 0x06, 2,  2,  16,  10}, // 8G
    { 0x07, 1,  2,  17,  10}, // 8G
    { 0x08, 2,  2,  17,  10}, // 16G
  //  0x09  Reserved
    { 0x0A, 2,  2,  18,  10}  // 32G
  // 0x0B - 0x0F Reserved
  };
  UINT8 i;

  for (i = 0; i < GET_SIZE_OF (DimmAddressMapTable); i++) {
    if (BGBits == DimmAddressMapTable[i].BGBits) {
      if (BABits == DimmAddressMapTable[i].BABits) {
        if (RowBits == DimmAddressMapTable[i].RowBits) {
          if (ColBits == DimmAddressMapTable[i].ColBits) {
            *DimmAddrMap = DimmAddressMapTable[i].DimmAddressMap;
            return TRUE;
          } // ColBits
        } // RowBits
      } // BABits
    } //BGBits
  } // i
  return FALSE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *       This function returns a pointer to the SPD Buffer of a specific dimm on
 *    the current channel.
 *
 *     @param[in,out] *TechPtr - Pointer to the MEM_TECH_BLOCK
 *     @param[in,out] **SpdBuffer - Pointer to a pointer to a UINT8 Buffer
 *     @param[in] Dimm - Dimm number
 *
 *
 *     @return BOOLEAN - Value of DimmPresent
 *                       TRUE = Dimm is present, pointer is valid
 *                       FALSE = Dimm is not present, pointer has not been modified.
 */

BOOLEAN
MemTGetDimmSpdBuffer4 (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN OUT   UINT8 **SpdBuffer,
  IN       UINT8 Dimm
  )
{
  CH_DEF_STRUCT *ChannelPtr;
  SPD_DEF_STRUCT *SPDPtr;
  BOOLEAN DimmPresent;

  DimmPresent = FALSE;
  ChannelPtr = TechPtr->NBPtr->ChannelPtr;
  ASSERT (Dimm < (sizeof (ChannelPtr->DimmSpdPtr) / sizeof (ChannelPtr->DimmSpdPtr[0])))
  SPDPtr = ChannelPtr->DimmSpdPtr[Dimm];

  if (SPDPtr != NULL) {
    DimmPresent = SPDPtr->DimmPresent;
    if (DimmPresent) {
      *SpdBuffer = SPDPtr->Data;
    }
  }
  return DimmPresent;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *       This function returns the MTB
 *
 *     @param[in,out] *TechPtr - Pointer to the MEM_TECH_BLOCK
 *     @param[in,out] *SpdBuffer - Pointer to a pointer to a UINT8 Buffer
 *
 *
 *     @return INT32 - MTB value in ps
 */
INT32
MemTGetMTB (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN OUT   UINT8 *SpdBuffer
  )
{
  if (((SpdBuffer[SPD_MEDIUM_TIMEBASE] >> MTB_SHIFT) & MTB_MSK) == 0) {
    return 125;
  }

  return 0;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *       This function returns the FTB
 *
 *     @param[in,out] *TechPtr - Pointer to the MEM_TECH_BLOCK
 *     @param[in,out] *SpdBuffer - Pointer to a pointer to a UINT8 Buffer
 *
 *
 *     @return INT32 - FTB value in ps
 */
INT32
MemTGetFTB (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN OUT   UINT8 *SpdBuffer
  )
{
  if ((SpdBuffer[SPD_FINE_TIMEBASE] & FTB_MSK) == 0) {
    return 1;
  }

  return 0;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function returns DDR4 SPD Offset for a given Bus Nibble Range
 *
 *     @param[in] Nibble - Enum value indicating nibble range
 *
 *     @return UINT8 - DDR4 SPD Offset containing nibble mapping info for
 *                     the supplied range.
 */
UINT8
MemTGetDQMappingByte (
  IN DQ_MAP_NIBBLES Nibble
  )
{
  //
  // This Table Translates the Memory Bus Nibble to the
  // DQ Mapping Value within the SPD Array.
  //
  CONST DQMAP_NIBBLE NibbleOffsetTbl[] = {
    { DQ_0_3   , 0 },
    { DQ_4_7   , 1 },
    { DQ_8_11  , 2 },
    { DQ_12_15 , 3 },
    { DQ_16_19 , 4 },
    { DQ_20_23 , 5 },
    { DQ_24_27 , 6 },
    { DQ_28_31 , 7 },
    { DQ_64_67 , 8 },
    { DQ_68_71 , 9 },
    { DQ_32_35 , 10},
    { DQ_36_39 , 11},
    { DQ_40_43 , 12},
    { DQ_44_47 , 13},
    { DQ_48_51 , 14},
    { DQ_52_55 , 15},
    { DQ_56_59 , 16},
    { DQ_60_63 , 17}
  };

  UINT8 i;
  UINT8 SpdIndex;
  ASSERT ( (Nibble >= DQ_0_3) && (Nibble <= DQ_68_71) );
  SpdIndex = 0xFF;
  for (i = 0; i < GET_SIZE_OF (NibbleOffsetTbl); i++) {
    if (Nibble == NibbleOffsetTbl[i].Nibble) {
      SpdIndex = SPD_DQ_MAPPING + i;
      break;
    }
  }
  ASSERT (SpdIndex != 0xFF);
  return SpdIndex;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function returns the JEDEC DDR4 nCK Minimum Timing for select SPD
 *     Based timings.
 *
 *     @param[in] SPDOffset - SPD Timing Offset
 *     @param[in] PageSize - Page Size
 *
 *     @return UINT8 - Jedec nCK Minimum
 *
 */
UINT8
MemTGetJedecMinClks (
  IN UINT8 SPDOffset,
  IN UINT16 PageSize
  )
{
  UINT8 i;
  //
  // Search the table for the SPD Parameter being checked.
  //
  for (i = 0; i < GET_SIZE_OF (MemDdr4JedecMinClksTable); i++) {
    if (SPDOffset == MemDdr4JedecMinClksTable[i].SpdOffset) {
      if ((MemDdr4JedecMinClksTable[i].PageSize == PGSZ_NA) || (MemDdr4JedecMinClksTable[i].PageSize == PageSize))  {
        return MemDdr4JedecMinClksTable[i].nCKMin;
      }
    }
  }
  return 0;
}


