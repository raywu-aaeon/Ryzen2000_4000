/* $NoKeywords:$ */
/**
 * @file
 *
 * mnD4cz.h
 *
 * Northbridge CZ
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/NB/CZ)
 * @e \$Revision: 319517 $ @e \$Date: 2015-05-28 12:14:11 +0800 (Thu, 28 May 2015) $
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

#ifndef _MND4CZ_H_
#define _MND4CZ_H_

/*----------------------------------------------------------------------------
 *   Mixed (DEFINITIONS AND MACROS / TYPEDEFS, STRUCTURES, ENUMS)
 *
 *----------------------------------------------------------------------------
 */
#define DRAM_TYPE_DDR4_CZ             2
#define MAX_D4_DCTS_PER_NODE_CZ       2
/*-----------------------------------------------------------------------------
 *                         DEFINITIONS AND MACROS
 *
 *-----------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------
 *                         TYPEDEFS, STRUCTURES, ENUMS
 *
 *----------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------
 *                           FUNCTIONS PROTOTYPE
 *
 *----------------------------------------------------------------------------
 */

VOID
MemNInitNBDataD4CZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

VOID
MemNSetDdrModeD4CZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

VOID
MemNConfigureDctForTrainingD4CZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

VOID
MemNConfigureDctNormalD4CZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

VOID
MemNProgramMemPstateRegD4CZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 MemPstate
  );

VOID
MemNProgramCycTimingsD4CZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

VOID
MemNPredriverInitD4CZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

VOID
MemNProgramCadDataBusD4CZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

VOID
MemNPhyFifoConfigD4CZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

AGESA_STATUS
MemMD4FlowCZ (
  IN OUT   MEM_MAIN_DATA_BLOCK *MemMainPtr
  );

VOID
MemNSetPmuSequenceControlD4CZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

VOID
MemNPopulatePmuSramConfigD4CZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

VOID
MemNPopulatePmuSramTimingsD4CZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

VOID
MemNModeRegisterInitializationD4CZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

VOID
MemNProgramTurnaroundTimingsD4CZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

VOID
MemNGetCSIntLvAddrD4CZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 BankAddrMap,
  OUT      UINT8 *LowBit,
  OUT      UINT8 *HiBit
  );

VOID
MemNProgramDqMappingsD4CZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

#endif  /* _MND4CZ_H_ */

