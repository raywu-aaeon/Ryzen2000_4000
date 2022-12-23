/* $NoKeywords:$ */
/**
 * @file
 *
 * mnS3cz.h
 *
 * S3 resume memory related function for CZ.
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/NB/CZ)
 * @e \$Revision: 327442 $ @e \$Date: 2015-09-22 00:15:18 +0800 (Tue, 22 Sep 2015) $
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

#ifndef _MNS3CZ_H_
#define _MNS3CZ_H_

/*----------------------------------------------------------------------------
 *   Mixed (DEFINITIONS AND MACROS / TYPEDEFS, STRUCTURES, ENUMS)
 *
 *----------------------------------------------------------------------------
 */
/// ID for register list of CZ
typedef enum {
  PCI_LST_ESR_CZ,  ///< Assign 0x0000 for PCI register list for pre exit self refresh.
  PCI_LST_CZ,      ///< Assign 0x0001 for PCI register list for post exist self refresh.
  CPCI_LST_ESR_CZ, ///< Assign 0x0002 for conditional PCI register list for pre exit self refresh.
  CPCI_LST_CZ,     ///< Assign 0x0003 for conditional PCI register list for post exit self refresh.
  MSR_LST_ESR_CZ,  ///< Assign 0x0004 for MSR register list for pre exit self refresh.
  MSR_LST_CZ,      ///< Assign 0x0005 for MSR register list for post exit self refresh.
  CMSR_LST_ESR_CZ, ///< Assign 0x0006 for conditional MSR register list for pre exit self refresh.
  CMSR_LST_CZ      ///< Assign 0x0007 for conditional MSR register list for post exit self refresh.
} RegisterListIDCZ;

/*-----------------------------------------------------------------------------
 *                         DEFINITIONS AND MACROS
 *
 *-----------------------------------------------------------------------------
 */
#define SET_S3_NB_PSTATE_OFFSET(Offset, NBPstate) ((NBPstate << 10) | Offset)
#define SET_S3_MEM_PSTATE_OFFSET(Offset, MemPstate) ((MemPstate << 11) | Offset)

#define S3_DATABLOB_REV_CZ 0xA

#define GNB_D0F0x60_ADDRESS   0x60          ///<  Gnb Offset index for SMU mbox
#define GNB_D0F0x64_DATA 0x64
#define GNB_IOC_WRITE_ENABLE 0x80


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
MemNS3ConfigureDisDllShutdownSrCZ (
  IN       ACCESS_WIDTH AccessWidth,
  IN       PCI_ADDR Address,
  IN OUT   VOID *Value,
  IN OUT   VOID *ConfigPtr
  );
#endif //_MNS3CZ_H_

