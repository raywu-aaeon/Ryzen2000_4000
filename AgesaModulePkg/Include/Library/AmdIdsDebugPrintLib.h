/**
 * @file
 *
 * AMD Integrated Debug Debug_library Routines
 *
 * Contains all functions related to HDTOUT
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  IDS
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-10 02:28:05 +0800 (Wed, 10 Dec 2014) $
 */
/*****************************************************************************
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
 */
#ifndef _AMD_IDS_DEBUGPRINT_LIB_H_
#define _AMD_IDS_DEBUGPRINT_LIB_H_
#define AMD_IDS_DP_FLAG_ALL       0xFFFFFFFFFFFFFFFFull
/// HDTOUT Header.
typedef struct _HDTOUT_HEADER {
  UINT32 Signature;               ///< 0 0xDB1099CC
  UINT16 Version;                 ///< 4 HDTOUT version.
  UINT16 BufferSize;              ///< 6 Size in bytes.
  UINT16 DataIndex;               ///< 8 Data Index.
  UINT8  PrintCtrl;               ///< 10 0 off no print  1 on print
  UINT8  NumBreakpointUnit;       ///< 11 default 0 no bp unit others number of bp unit
  UINT32 FuncListAddr;            ///< 12 32 bit address to the list of functions that script can execute
  UINT8  ConsoleType;             ///< 16 Console type - deprecated
  UINT8  Event;                   ///< 17 Event type. - deprecated
  UINT8  OutBufferMode;           ///< 18 Off:stack mode, On: heap mode - deprecated
  UINT32 EnableMask;              ///< 19 Bitmap to select which part should be streamed out
  UINT64 ConsoleFilter;           ///< 23 Filter use to select which part should be streamed out
  UINT8  BspOnlyFlag;             ///< 31 1 Only Enable Bsp output, 0 enable On All cores
  UINT8  Reserved[56 - 32];       ///< 32 Reserved for header expansion

  CHAR8  BreakpointList[300];     ///< 56 Breakpoint list
  CHAR8  StatusStr[156];          ///< 356 Shows current node, DCT, CS,...
  CHAR8  Data[2];                 ///< 512 HDTOUT content. Its size will be determined by BufferSize.
} HDTOUT_HEADER;

BOOLEAN
AmdIdsDpHdtOutSupport (
  VOID
  );

VOID
AmdIdsDpHdtOutPrint (
  IN      CHAR8   *Buffer,
  IN      UINTN BufferSize
  );

BOOLEAN
AmdIdsDpHdtOutGetHeader (
  IN OUT   HDTOUT_HEADER **pHdtoutHeaderPtr
  );

VOID
AmdIdsDpHdtOutRegisterInit (
  VOID
  );

VOID
AmdIdsDpHdtOutBufferModeInit (
  );

VOID
AmdIdsDebugPrintf (
  IN      UINT64      FilterFlag,
  IN      CONST CHAR8 *Format,
  IN      VA_LIST     Marker
  );

#endif //_AMD_IDS_DEBUGPRINT_LIB_H_
