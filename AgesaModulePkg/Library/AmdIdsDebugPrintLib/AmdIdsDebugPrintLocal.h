/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD Integrated Debug Print Routines
 *
 * Contains all functions related to IDS Debug Print
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  IDS
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-10 02:28:05 +0800 (Wed, 10 Dec 2014) $
 */
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
 **/

#ifndef _AMD_IDS_DEBUG_PRINT_LOCAL_H_
#define _AMD_IDS_DEBUG_PRINT_LOCAL_H_

/// return status for debug print
typedef enum {
  IDS_DEBUG_PRINT_SUCCESS = 0,      ///< success
  IDS_DEBUG_PRINT_BUFFER_OVERFLOW,      ///< Bufer overflow
} IDS_DEBUG_PRINT_STATUS;

typedef BOOLEAN (*PF_AMD_IDS_DEBUG_PRINT_SUPPORT) (VOID);
typedef BOOLEAN (*PF_AMD_IDS_DEBUG_PRINT_FILTER) (UINT64 *Filter);
typedef VOID (*PF_AMD_IDS_DEBUG_PRINT_PRINT) (CHAR8 *Buffer, UINTN BufferSize);
typedef VOID (*PF_AMD_IDS_DEBUG_CONSTRUCTOR) (VOID);

/// Debug print Hw layer service class
typedef struct _AMD_IDS_DEBUG_PRINT_INSTANCE {
  PF_AMD_IDS_DEBUG_PRINT_SUPPORT  support;    ///Check if support
  PF_AMD_IDS_DEBUG_CONSTRUCTOR    constructor;  ///constructor, will be called prior to driver execution
  PF_AMD_IDS_DEBUG_PRINT_FILTER  customfilter;  ///Get if any customize filters
  PF_AMD_IDS_DEBUG_PRINT_PRINT  print;  ///Print data to Hw layer
} AMD_IDS_DEBUG_PRINT_INSTANCE;

#endif //_AMD_IDS_DEBUG_PRINT_LOCAL_H_


