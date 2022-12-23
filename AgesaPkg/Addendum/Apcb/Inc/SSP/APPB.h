/* $NoKeywords:$ */
/**
 * @file
 *
 * APCB.h
 *
 * AGESA PSP PMU Block
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem)
 * @e \$Revision: 192403 $ @e \$Date: 2012-12-12 15:46:25 -0600 (Wed, 12 Dec 2012) $
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

#ifndef _APPB_H_
#define _APPB_H_
//#include "psp_fw_image.h"

/*----------------------------------------------------------------------------
 *   Mixed (DEFINITIONS AND MACROS / TYPEDEFS, STRUCTURES, ENUMS)
 *
 *----------------------------------------------------------------------------
 */

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
///===============================================================================
/// _PSP_PMU_STRUCT
/// This data structure is used to pass wrapper parameters to the memory configuration code
///
typedef struct _PSP_PMU_STRUCT {
  PMU_FIRMWARE PmuFirmwareImage;              ///< PMU Firmware Image
} PSP_PMU_STRUCT;

// AGESA PSP PMU Signature.
#define APPB_SIGNATURE           {'!', '!', 'B', 'P', 'P', 'A'}   ///< APPB Signature with 6 characters limited.
#define APPB_VERSION     0x0001  // APPB Version
/// AMD APCB_HEADER Header
typedef struct {
  CHAR8   Signature[6];                       ///< APPB signature
  CHAR8   TerminatorNull;                     ///< null terminated string
  CHAR8   TerminatorNull1;                    ///< null terminated string
  UINT32   Version;                           ///< Version
  UINT32   Family;                            ///< Family
  UINT32   DddrType;                          ///< DDR Type
} APPB_HEADER;

///===============================================================================
/// AGESA PSP PMU BLOCK
/// This data structure is used to pass PMU information to the PSP
///
typedef struct _AGESA_PSP_PMU_BLOCK_STRUCT {
  PSP_FW_IMAGE_HEADER     PspFwImageHeader;       ///< PSP FW Image Header
  IN APPB_HEADER          Header;                 ///< APPB Header
  IN PSP_PMU_STRUCT       memPspPmu;              ///< PMU Image Buffer
} AGESA_PSP_PMU_BLOCK_STRUCT;

/*----------------------------------------------------------------------------
 *                           FUNCTIONS PROTOTYPE
 *
 *----------------------------------------------------------------------------
 */

AGESA_STATUS
VerifyAppb (
  IN OUT   UINT32 AgesaAppbVersion,
  IN OUT   UINT32 BiosAppbVersion,
  IN       UINT32 Family,
  IN       UINT32 DDRType,
  IN       AMD_CONFIG_PARAMS *StdHeader
  );

#endif  /* _APPB_H_ */


