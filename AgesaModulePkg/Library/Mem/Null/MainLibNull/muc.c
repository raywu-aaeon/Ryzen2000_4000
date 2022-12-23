/* $NoKeywords:$ */
/**
 * @file
 *
 * muc.c
 *
 * Utility functions
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/Main)
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

/*
 *----------------------------------------------------------------------------
 *                                MODULES USED
 *
 *----------------------------------------------------------------------------
 */



#include "AGESA.h"
#include "Library/AmdBaseLib.h"
#include "OptionMemory.h"
#include "PlatformMemoryConfiguration.h"
#include "Ids.h"
#include "mport.h"
#include "mu.h"
#include "cpuCacheInit.h"
#include "Filecode.h"
CODE_GROUP (G1_PEICC)
RDATA_GROUP (G1_PEICC)

#define FILECODE LIBRARY_MEM_NULL_MAINLIBNULL_MUC_FILECODE
/*----------------------------------------------------------------------------
 *                          DEFINITIONS AND MACROS
 *
 *----------------------------------------------------------------------------
 */
CONST UINT32 Pattern2[16] = {
  0x12345678, 0x87654321, 0x23456789, 0x98765432,
  0x59385824, 0x30496724, 0x24490795, 0x99938733,
  0x40385642, 0x38465245, 0x29432163, 0x05067894,
  0x12349045, 0x98723467, 0x12387634, 0x34587623
};

CONST UINT32 MaxLatPat[48] = {
  0x6E0E3FAC, 0x0C3CFF52,
  0x4A688181, 0x49C5B613,
  0x7C780BA6, 0x5C1650E3,
  0x0C4F9D76, 0x0C6753E6,
  0x205535A5, 0xBABFB6CA,
  0x610E6E5F, 0x0C5F1C87,
  0x488493CE, 0x14C9C383,
  0xF5B9A5CD, 0x9CE8F615,

  0xAAD714B5, 0xC38F1B4C,
  0x72ED647C, 0x669F7562,
  0x5233F802, 0x4A898B30,
  0x10A40617, 0x3326B465,
  0x55386E04, 0xC807E3D3,
  0xAB49E193, 0x14B4E63A,
  0x67DF2495, 0xEA517C45,
  0x7624CE51, 0xF8140C51,

  0x4824BD23, 0xB61DD0C9,
  0x072BCFBE, 0xE8F3807D,
  0x919EA373, 0x25E30C47,
  0xFEB12958, 0x4DA80A5A,
  0xE9A0DDF8, 0x792B0076,
  0xE81C73DC, 0xF025B496,
  0x1DB7E627, 0x808594FE,
  0x82668268, 0x655C7783
};

CONST UINT8 PatternJD[9] = {0x44, 0xA6, 0x38, 0x4F, 0x4B, 0x2E, 0xEF, 0xD5, 0x54};

CONST UINT8 PatternJD_256[256] = {
  0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00,
  0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF,
  0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF,
  0xFF, 0xFF, 0x00, 0xF7, 0x08, 0xF7, 0x00, 0xFF,
  0x00, 0xF7, 0x00, 0xFF, 0x00, 0xF7, 0x00, 0xF7,
  0x08, 0xF7, 0x08, 0xFF, 0x00, 0xFF, 0x08, 0xFF,
  0x00, 0xFF, 0x08, 0xFF, 0x08, 0xF7, 0xFB, 0x04,
  0xFB, 0xFB, 0x04, 0xFB, 0xFB, 0xFB, 0x04, 0xFB,
  0xFB, 0xFB, 0xFB, 0x04, 0xFB, 0x04, 0x04, 0xFB,
  0x04, 0x04, 0x04, 0xFB, 0x04, 0x04, 0x04, 0x04,
  0xFB, 0x7F, 0x80, 0x7F, 0x00, 0xFF, 0x00, 0x7F,
  0x00, 0xFF, 0x00, 0x7F, 0x00, 0x7F, 0x80, 0x7F,
  0x80, 0xFF, 0x00, 0xFF, 0x80, 0xFF, 0x00, 0xFF,
  0x80, 0xFF, 0x80, 0x7F, 0xBF, 0x40, 0xBF, 0xBF,
  0x40, 0xBF, 0xBF, 0xBF, 0x40, 0xBF, 0xBF, 0xBF,
  0xBF, 0x40, 0xBF, 0x40, 0x40, 0xBF, 0x40, 0x40,
  0x40, 0xBF, 0x40, 0x40, 0x40, 0x40, 0xBF, 0xFD,
  0x02, 0xFD, 0x00, 0xFF, 0x00, 0xFD, 0x00, 0xFF,
  0x00, 0xFD, 0x00, 0xFD, 0x02, 0xFD, 0x02, 0xFF,
  0x00, 0xFF, 0x02, 0xFF, 0x00, 0xFF, 0x02, 0xFF,
  0x02, 0xFD, 0xFE, 0x01, 0xFE, 0xFE, 0x01, 0xFE,
  0xFE, 0xFE, 0x01, 0xFE, 0xFE, 0xFE, 0xFE, 0x01,
  0xFE, 0x01, 0x01, 0xFE, 0x01, 0x01, 0x01, 0xFE,
  0x01, 0x01, 0x01, 0x01, 0xFE, 0xDF, 0x20, 0xDF,
  0x00, 0xFF, 0x00, 0xDF, 0x00, 0xFF, 0x00, 0xDF,
  0x00, 0xDF, 0x20, 0xDF, 0x20, 0xFF, 0x00, 0xFF,
  0x20, 0xFF, 0x00, 0xFF, 0x20, 0xFF, 0x20, 0xDF,
  0xEF, 0x10, 0xEF, 0xEF, 0x10, 0xEF, 0xEF, 0xEF,
  0x10, 0xEF, 0xEF, 0xEF, 0xEF, 0x10, 0xEF, 0x10,
  0x10, 0xEF, 0x10, 0x10, 0x10, 0xEF, 0x10, 0x10,
  0x10, 0x10, 0xEF, 0xF7, 0x00, 0xFF, 0x04, 0x7F,
  0x00, 0xFF, 0x40, 0xFD, 0x00, 0xFF, 0x01, 0xDF
};

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


/*----------------------------------------------------------------------------
 *                            EXPORTED FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */
/* -----------------------------------------------------------------------------*/
/**
 *
 *      This function returns the (index)th UINT8
 *   from an indicated test pattern.
 *
 *     @param[in] Pattern - encoding of test pattern type
 *     @param[in] Buffer[] - buffer to be filled
 *     @param[in] Size - Size of the buffer
 *
 * ----------------------------------------------------------------------------
 */

VOID
MemUFillTrainPattern (
  IN       TRAIN_PATTERN Pattern,
  IN       UINT8 Buffer[],
  IN       UINT16 Size
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *      This function flushes cache lines
 *
 *     @param[in,out] MemPtr - pointer to MEM_DATA_STRUCTURE
 *     @param[in] ClCount - Number of cache lines
 *     @param[in] Address - System Address [47:16]
 *
 * ----------------------------------------------------------------------------
 */

VOID
MemUProcIOClFlush (
  IN       UINT32 Address,
  IN       UINT16 ClCount,
  IN OUT   MEM_DATA_STRUCT *MemPtr
  )
{

}

/*----------------------------------------------------------------------------
 *                              LOCAL FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */

/* -----------------------------------------------------------------------------*/
/**
 *
 *      This function sets the upper 32-bits of the Base address, 4GB aligned) for the FS selector.
 *      @param[in,out] MemPtr - pointer to MEM_DATA_STRUCTURE
 *      @param[in] Address - System Address [47:16]
 *
 *     @return  Address - Lowest 32-bit of physical address
 * ----------------------------------------------------------------------------
 */

UINT32
MemUSetUpperFSbase (
  IN       UINT32 Address,
  IN OUT   MEM_DATA_STRUCT *MemPtr
  )
{
  return 0;
}


/* -----------------------------------------------------------------------------*/
/**
 *
 *      This function resets the target address space to Write Through IO by disabling IORRs
 *
 *      @param[in,out] MemPtr - pointer to MEM_DATA_STRUCTURE
 *
 * ----------------------------------------------------------------------------
 */

VOID
MemUResetTargetWTIO (
  IN OUT   MEM_DATA_STRUCT *MemPtr
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *       This function sets the target range to WT IO (using an IORR overlapping
 *       the already existing
 *
 *      @param[in,out] MemPtr - pointer to MEM_DATA_STRUCTURE
 *      @param[in] Address - System Address [47:16]
 *
 * ----------------------------------------------------------------------------
 */

VOID
MemUSetTargetWTIO (
  IN       UINT32 Address,
  IN OUT   MEM_DATA_STRUCT *MemPtr
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *  Waits specified number of 10ns cycles
 *      @param[in,out] MemPtr - pointer to MEM_DATA_STRUCTURE
 *      @param[in] Count - Number of 10ns cycles to wait; Note that Count must not exceed 1000000
 *
 * ----------------------------------------------------------------------------
 */

VOID
MemUWait10ns (
  IN       UINT32 Count,
  IN OUT   MEM_DATA_STRUCT *MemPtr
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *      Find the entry of platform specific overriding table.
 *
 *      @param[in] PlatformMemoryConfiguration - Platform config table
 *      @param[in] EntryType - Entry type
 *      @param[in] SocketID - Physical socket ID
 *      @param[in] ChannelID - Physical channel ID
 *      @param[in] DimmID - Physical Dimm ID
 *      @param[in] *LogicalIdPtr - Pointer to the SOC_LOGICAL_ID
 *      @param[in,out]  *StdHeader - Pointer of AMD_CONFIG_PARAMS
 *                 - If both *LogicalIdPtr and *StdHeader are "NULL" input,
 *                   that means, the "EntryType" are not CPU family dependent,
 *                   ex. PSO_MAX_DIMMS for NUMBER_OF_DIMMS_SUPPORTED macro.
 *
 *
 *      @return  NULL - entry could not be found.
 *      @return  Pointer - points to the entry's data.
 *
 * ----------------------------------------------------------------------------
 */

VOID *
FindPSOverrideEntry (
  IN       PSO_TABLE *PlatformMemoryConfiguration,
  IN       PSO_ENTRY EntryType,
  IN       UINT8 SocketID,
  IN       UINT8 ChannelID,
  IN       UINT8 DimmID,
  IN       SOC_LOGICAL_ID *LogicalIdPtr,
  IN       AMD_CONFIG_PARAMS *StdHeader
  )
{
  return NULL;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *      This function returns the max dimms for a given memory channel on a given
 *  processor.  It first searches the platform override table for the max dimms
 *  value.  If it is not provided, the AGESA default value is returned. The target
 *  socket must be a valid present socket.
 *
 *     @param[in] PlatformMemoryConfiguration - Platform config table
 *     @param[in] SocketID  - ID of the processor that owns the channel
 *     @param[in] ChannelID - Channel to get max dimms for
 *
 *
 *     @return UINT8 - Max Number of Dimms for that channel
 */
UINT8
GetMaxDimmsPerChannel (
  IN       PSO_TABLE *PlatformMemoryConfiguration,
  IN       UINT8 SocketID,
  IN       UINT8 ChannelID
  )
{
  return 0;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *      This function returns the max soldered-down dimms for a given memory channel on a given
 *  processor.  It first searches the platform override table for the soldered-down dimms
 *  value.  If it is not provided, the AGESA default value is returned. The target
 *  socket must be a valid present socket.
 *
 *     @param[in] PlatformMemoryConfiguration - Platform config table
 *     @param[in] SocketID  - ID of the processor that owns the channel
 *     @param[in] ChannelID - Channel to get max dimms for
 *
 *
 *     @return UINT8 - Max Number of soldered-down dimms for that channel
 */
UINT8
GetMaxSolderedDownDimmsPerChannel (
  IN       PSO_TABLE *PlatformMemoryConfiguration,
  IN       UINT8 SocketID,
  IN       UINT8 ChannelID
  )
{
  return 0;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *      This function returns the max memory channels on a given processor.
 *  It first searches the platform override table for the max channels value.
 *  If it is not provided, the AGESA default value is returned.
 *
 *     @param[in] PlatformMemoryConfiguration - Platform config table
 *     @param[in] SocketID - ID of the processor
 *     @param[in] StdHeader - Header for library and services
 *
 *
 *     @return UINT8 - Max Number of Channels on that Processor
 */
UINT8
GetMaxChannelsPerSocket (
  IN       PSO_TABLE *PlatformMemoryConfiguration,
  IN       UINT8 SocketID,
  IN       AMD_CONFIG_PARAMS *StdHeader
  )
{
  return 0;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *      This function returns the max number of chip select on a given channel of
 *  a given processor. It first searches the platform override table for the max
 *  chip select value. If it is not provided, the AGESA default value is returned.
 *  The target socket must be a valid present socket.
 *
 *     @param[in] PlatformMemoryConfiguration - Platform config table
 *     @param[in] SocketID - ID of the processor
 *     @param[in] ChannelID - ID of a channel
 *
 *
 *     @return UINT8 - Max Number of chip selects on the channel of the Processor
 */
UINT8
GetMaxCSPerChannel (
  IN      PSO_TABLE *PlatformMemoryConfiguration,
  IN      UINT8 SocketID,
  IN      UINT8 ChannelID
  )
{
  return 0;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *      This function returns the index of the first Dimm SPD structure for a
 *  given processor socket. It checks the Max Dimms per channel for every memory
 *  channel on every processor up to the current one, and adds them together.
 *
 *      This function may also be used to calculate the maximum dimms per system
 *  by passing the total number of dimm sockets
 *
 *     @param[in] PlatformMemoryConfiguration - Platform config table
 *     @param[in] SocketID - ID of the processor
 *     @param[in] StdHeader - Header for library and services
 *
 *     @return UINT8 - SPD Index
 */
UINT8
GetSpdSocketIndex (
  IN       PSO_TABLE *PlatformMemoryConfiguration,
  IN       UINT8 SocketID,
  IN       AMD_CONFIG_PARAMS *StdHeader
  )
{
  return 0;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *      This function returns the index of the first Dimm SPD structure for a
 *  given channel relative to the processor socket. It checks the Max Dimms per
 *  channel for every memory channel on that processor up to the current one,
 *  and adds them together.
 *
 *      This function may also be used to calculate the maximum dimms per system
 *  by passing the total number of DIMM sockets
 *
 *     @param[in] PlatformMemoryConfiguration - Platform config table
 *     @param[in] SocketID - ID of the processor
 *     @param[in] ChannelID - ID of the Channel
 *     @param[in] StdHeader - Header for library and services
 *
 *     @return UINT8 - SPD Index
 */
UINT8
GetSpdChannelIndex (
  IN       PSO_TABLE *PlatformMemoryConfiguration,
  IN       UINT8 SocketID,
  IN       UINT8 ChannelID,
  IN       AMD_CONFIG_PARAMS *StdHeader
  )
{
  return 0;
}

/*-----------------------------------------------------------------------------*/
/**
 *
 *     This function returns the upper 32 bits mask for variable MTRR based on
 *     the SOC_LOGICAL_ID.
 *     @param[in]       *LogicalIdPtr - Pointer to the SOC_LOGICAL_ID
 *     @param[in]       StdHeader - Header for library and services
 *
 *     @return          UINT32 - MTRR mask for upper 32 bits
 *
 */
UINT32
GetVarMtrrHiMsk (
  IN       SOC_LOGICAL_ID *LogicalIdPtr,
  IN       AMD_CONFIG_PARAMS *StdHeader
  )
{
  return 0x00007FFF;
}


/*-----------------------------------------------------------------------------*/
/**
 *
 *     This function returns number of memclk converted from ns
 *     @param[in]       Speed - memclk frequency
 *     @param[in]       NumberOfns - number of ns to be converted
 *
 *     @return          UINT32 - number of memclk
 *
 */
UINT32
MemUnsToMemClk (
  IN       UINT32 Speed,
  IN       UINT32 NumberOfns
  )
{
  return 0;
}

