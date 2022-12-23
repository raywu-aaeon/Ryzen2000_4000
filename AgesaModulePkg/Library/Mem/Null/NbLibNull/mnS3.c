/* $NoKeywords:$ */
/**
 * @file
 *
 * mnS3.c
 *
 * Common Northbridge S3
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/NB)
 * @e \$Revision: 311790 $ @e \$Date: 2015-01-27 13:03:49 +0800 (Tue, 27 Jan 2015) $
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
#include "Library/IdsLib.h"
#include "Ids.h"
#include "OptionMemory.h"
#include "mport.h"
#include "mm.h"
#include "mn.h"
#include "S3.h"
#include "Library/AmdMemFeatS3Lib.h"
#include "Library/AmdHeapLib.h"
#include "Filecode.h"
CODE_GROUP (G3_DXE)
RDATA_GROUP (G3_DXE)

#define FILECODE LIBRARY_MEM_NULL_NBLIBNULL_MNS3_FILECODE
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

/*----------------------------------------------------------------------------
 *                        PROTOTYPES OF LOCAL FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */
VOID
STATIC
MemNS3GetSetBitField (
  IN       ACCESS_WIDTH AccessWidth,
  IN       PCI_ADDR Address,
  IN       BOOLEAN IsSet,
  IN OUT   VOID *Value,
  IN OUT   VOID *ConfigPtr
  );

UINT16
STATIC
MemNS3GetMemClkFreqUnb (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 FreqId
  );
/*----------------------------------------------------------------------------
 *                            EXPORTED FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function executes the S3 resume for a node on a UNB
 *
 *     @param[in,out]   *S3NBPtr - Pointer to the S3_MEM_NB_BLOCK
 *     @param[in]       NodeID - The Node id of the target die
 *
 *     @return         BOOLEAN
 *                         TRUE - This is the correct constructor for the targeted node.
 *                         FALSE - This isn't the correct constructor for the targeted node.
 */
BOOLEAN
MemNS3ResumeUNb (
  IN OUT   S3_MEM_NB_BLOCK *S3NBPtr,
  IN       UINT8 NodeID
  )
{

  // Errata After S3 resume sequence
  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function reads register bitfield
 *
 *     @param[in]   AccessWidth - Access width of the register
 *     @param[in]   Address - address of the CSR register in PCI_ADDR format.
 *     @param[in, out]  *Value - Pointer to the value be read.
 *     @param[in, out]  *ConfigPtr - Pointer to Config handle.
 *     @return         none
 */
VOID
MemNS3GetBitFieldNb (
  IN       ACCESS_WIDTH AccessWidth,
  IN       PCI_ADDR Address,
  IN OUT   VOID *Value,
  IN OUT   VOID *ConfigPtr
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function writes register bitfield
 *
 *     @param[in]   AccessWidth - Access width of the register
 *     @param[in]   Address - address of the CSR register in PCI_ADDR format.
 *     @param[in, out]  *Value - Pointer to the value to be written.
 *     @param[in, out]  *ConfigPtr - Pointer to Config handle.
 *     @return         none
 */
VOID
MemNS3SetBitFieldNb (
  IN       ACCESS_WIDTH AccessWidth,
  IN       PCI_ADDR Address,
  IN OUT   VOID *Value,
  IN OUT   VOID *ConfigPtr
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function restores scrubber base register
 *
 *     @param[in,out]   *NBPtr - Pointer to the MEM_NB_BLOCK
 *     @param[in]       Node - The Node id of the target die
 *
 */
VOID
MemNS3RestoreScrubNb (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 Node
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function retores Pre Driver Calibration with pre driver calibration code
 *   code valid bit set.
 *
 *     @param[in]   AccessWidth - Access width of the register.
 *     @param[in]   Address - address in PCI_ADDR format.
 *     @param[in, out]  *Value - Pointer to the value to be written.
 *     @param[in, out]  *ConfigPtr - Pointer to Config handle.
 *     @return         none
 */
VOID
MemNS3SetPreDriverCalUnb (
  IN       ACCESS_WIDTH AccessWidth,
  IN       PCI_ADDR Address,
  IN OUT   VOID *Value,
  IN OUT   VOID *ConfigPtr
  )
{

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
MemNS3DctCfgSelectUnb (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       VOID *Dct
  )
{
  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function write to a register that has one copy for each NB Pstate
 *
 *     @param[in]   AccessWidth - Access width of the register
 *     @param[in]   Address - address of the CSR register in PCI_ADDR format.
 *     @param[in, out]  *Value - Pointer to the value be read.
 *     @param[in, out]  *ConfigPtr - Pointer to Config handle.
 *     @return         none
 */
VOID
MemNS3GetNBPStateDepRegUnb (
  IN       ACCESS_WIDTH AccessWidth,
  IN       PCI_ADDR Address,
  IN OUT   VOID *Value,
  IN OUT   VOID *ConfigPtr
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function write to a register that has one copy for each NB Pstate
 *
 *     @param[in]   AccessWidth - Access width of the register
 *     @param[in]   Address - address of the CSR register in PCI_ADDR format.
 *     @param[in, out]  *Value - Pointer to the value be read.
 *     @param[in, out]  *ConfigPtr - Pointer to Config handle.
 *     @return         none
 */
VOID
MemNS3SetNBPStateDepRegUnb (
  IN       ACCESS_WIDTH AccessWidth,
  IN       PCI_ADDR Address,
  IN OUT   VOID *Value,
  IN OUT   VOID *ConfigPtr
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function read the value of Function 2 PCI register.
 *
 *     @param[in]   AccessWidth - Access width of the register
 *     @param[in]   Address - address of the NB register in PCI_ADDR format.
 *     @param[in]  *Value - Pointer to the value be read.
 *     @param[in, out]  *ConfigPtr - Pointer to Config handle.
 *     @return         none
 */
VOID
MemNS3SaveNBRegisterUnb (
  IN       ACCESS_WIDTH AccessWidth,
  IN       PCI_ADDR Address,
  IN OUT   VOID *Value,
  IN OUT   VOID *ConfigPtr
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function set the value of Function 2 PCI register.
 *
 *     @param[in]   AccessWidth - Access width of the register
 *     @param[in]   Address - address of the NB register in PCI_ADDR format.
 *     @param[in]  *Value - Pointer to the value be write.
 *     @param[in, out]  *ConfigPtr - Pointer to Config handle.
 *     @return         none
 */
VOID
MemNS3RestoreNBRegisterUnb (
  IN       ACCESS_WIDTH AccessWidth,
  IN       PCI_ADDR Address,
  IN OUT   VOID *Value,
  IN OUT   VOID *ConfigPtr
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function sets MemClkFreqVal bit.
 *
 *     @param[in]   AccessWidth - Access width of the register.
 *     @param[in]   Address - address in PCI_ADDR format.
 *     @param[in, out]  *Value - Pointer to the value to be written.
 *     @param[in, out]  *ConfigPtr - Pointer to Config handle.
 *     @return         none
 */
VOID
MemNS3SetMemClkFreqValUnb (
  IN       ACCESS_WIDTH AccessWidth,
  IN       PCI_ADDR Address,
  IN OUT   VOID *Value,
  IN OUT   VOID *ConfigPtr
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *     This function changes memory Pstate context
 *
 *     @param[in]   AccessWidth - Access width of the register.
 *     @param[in]   Address - address in PCI_ADDR format. Target MemPState is in
 *                            Address.Address.Register.
 *     @param[in, out]  *Value - Pointer to the value to be written.
 *     @param[in, out]  *ConfigPtr - Pointer to Config handle.
 *     @return         none
 *
 *     @return    TRUE
 * ----------------------------------------------------------------------------
 */
VOID
MemNS3ChangeMemPStateContextNb (
  IN       ACCESS_WIDTH AccessWidth,
  IN       PCI_ADDR Address,
  IN OUT   VOID *Value,
  IN OUT   VOID *ConfigPtr
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function forces NBPstate to NBP0
 *
 *     @param[in]   AccessWidth - Access width of the register
 *     @param[in]   Address - address of the CSR register in PCI_ADDR format.
 *     @param[in, out]  *Value - Pointer to the value be read or  written.
 *     @param[in, out]  *ConfigPtr - Pointer to Config handle.
 *     @return         none
 */
VOID
MemNS3ForceNBP0Unb (
  IN       ACCESS_WIDTH AccessWidth,
  IN       PCI_ADDR Address,
  IN OUT   VOID *Value,
  IN OUT   VOID *ConfigPtr
  )
{
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function releases NBPState force
 *
 *     @param[in]   AccessWidth - Access width of the register
 *     @param[in]   Address - address of the CSR register in PCI_ADDR format.
 *     @param[in, out]  *Value - Pointer to the value be read or  written.
 *     @param[in, out]  *ConfigPtr - Pointer to Config handle.
 *     @return         none
 */
VOID
MemNS3ReleaseNBPSUnb (
  IN       ACCESS_WIDTH AccessWidth,
  IN       PCI_ADDR Address,
  IN OUT   VOID *Value,
  IN OUT   VOID *ConfigPtr
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function saves hob data into NV Ram.
 *
 *     @param[in]   AccessWidth - Access width of the register.
 *     @param[in]   Address - address in PCI_ADDR format.
 *     @param[in, out]  *Value - Pointer to the value to be written.
 *     @param[in, out]  *ConfigPtr - Pointer to Config handle.
 *     @return         none
 */
VOID
MemNSaveHobDataUnb (
  IN       ACCESS_WIDTH AccessWidth,
  IN       PCI_ADDR Address,
  IN OUT   VOID *Value,
  IN OUT   VOID *ConfigPtr
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function gets hob data from NV Ram.
 *
 *     @param[in]   AccessWidth - Access width of the register.
 *     @param[in]   Address - address in PCI_ADDR format.
 *     @param[in, out]  *Value - Pointer to the value to be written.
 *     @param[in, out]  *ConfigPtr - Pointer to Config handle.
 *     @return         none
 */
VOID
MemNRestoreHobDataUnb (
  IN       ACCESS_WIDTH AccessWidth,
  IN       PCI_ADDR Address,
  IN OUT   VOID *Value,
  IN OUT   VOID *ConfigPtr
  )
{

}


/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function enables and disables the fixed MTRR modify bit.
 *
 *     @param[in]   MsrAddress - Target MrsAddress
 *     @param[in]   *Value - Value to be written
 *     @param[in]   *StdHeader - Pointer to standard header
 */
VOID
MemNModdifyMtrrFixDramModEn (
  IN       UINT32             MsrAddress,
  IN       UINT64             *Value,
  IN       VOID               *StdHeader
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *    Configure disable DLL shutdown in self-refresh mode.
 *
 *     @param[in]   AccessWidth - Access width of the register.
 *     @param[in]   Address - address in PCI_ADDR format.
 *     @param[in, out]  *Value - Pointer to the value to be written.
 *     @param[in, out]  *ConfigPtr - Pointer to Config handle.
 *     @return         none
 *
 */

VOID
MemNS3ConfigureDisDllShutdownSrKV (
  IN       ACCESS_WIDTH AccessWidth,
  IN       PCI_ADDR Address,
  IN OUT   VOID *Value,
  IN OUT   VOID *ConfigPtr
  )
{

}
/*----------------------------------------------------------------------------
 *                              LOCAL FUNCTIONS
 *
 *----------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function reads and writes register bitfield
 *
 *     @param[in]   AccessWidth - Access width of the register
 *     @param[in]   Address - address of the CSR register in PCI_ADDR format.
 *     @param[in]   IsSet - if this is a register read or write
 *     @param[in, out]  *Value - Pointer to the value be read or  written.
 *     @param[in, out]  *ConfigPtr - Pointer to Config handle.
 *     @return         none
 */
VOID
STATIC
MemNS3GetSetBitField (
  IN       ACCESS_WIDTH AccessWidth,
  IN       PCI_ADDR Address,
  IN       BOOLEAN IsSet,
  IN OUT   VOID *Value,
  IN OUT   VOID *ConfigPtr
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function converts MemClkFreq Id value to MemClk frequency in MHz
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]       FreqId   - FreqId from Register
 *
 *     @return          MemClk frequency in MHz
 */
UINT16
STATIC
MemNS3GetMemClkFreqUnb (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 FreqId
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function is the default return and always return PSP not present
 *
  *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *      @return            FALSE - PSP is not present
 */
BOOLEAN
MemS3PspNotDetected (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  return FALSE;
}

