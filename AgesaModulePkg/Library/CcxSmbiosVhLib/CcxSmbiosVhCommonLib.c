/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD Ccx SMBIOS common code
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Lib
 * @e \$Revision$   @e \$Date$
 *
 */
/*
 ******************************************************************************
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
 */


/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */
#include <Library/BaseLib.h>
#include "Filecode.h"
#include "cpuRegisters.h"
#include "Library/CcxBaseX86Lib.h"

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */
#define FILECODE LIBRARY_CCXSMBIOSVHLIB_CCXSMBIOSVHCOMMONLIB_FILECODE

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U R E S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *                          E X P O R T E D    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */


/*---------------------------------------------------------------------------------------
 *                           L O C A L    F U N C T I O N S
 *---------------------------------------------------------------------------------------
 */
/* -----------------------------------------------------------------------------*/
/**
 *
 *  GetNameString
 *
 *  Description:
 *    Get name string from MSR_C001_00[35:30]
 *
 *  Parameters:
 *    @param[in, out]    *String       Pointer to name string
 *    @param[in]         *StdHeader
 *
 */
VOID
GetNameString (
  IN OUT   CHAR8 *String,
  IN       AMD_CONFIG_PARAMS *StdHeader
  )
{
  UINT8  i;
  UINT8  StringIndex;
  UINT8  MsrIndex;
  UINT64 MsrData;

  StringIndex = 0;
  for (MsrIndex = 0; MsrIndex <= 5; MsrIndex++) {
    MsrData = AsmReadMsr64 ((MSR_CPUID_NAME_STRING0 + MsrIndex));
    for (i = 0; i < 8; i++) {
      String[StringIndex] = (CHAR8) RShiftU64 (MsrData, (8 * i));
      StringIndex++;
    }
  }
  String[StringIndex] = '\0';
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *  IsSourceStrContainTargetStr
 *
 *  Description:
 *    check if source string contains target string.
 *
 *  Parameters:
 *    @param[in, out]    *SourceStr      Pointer to source CHAR array
 *    @param[in, out]    *TargetStr      Pointer to target CHAR array
 *    @param[in]         *StdHeader
 *
 *    @retval            TRUE             Target string is contained in the source string
 *    @retval            FALSE            Target string is not contained in the source string
 */
BOOLEAN
IsSourceStrContainTargetStr (
  IN OUT   CHAR8 *SourceStr,
  IN OUT   CONST CHAR8 *TargetStr,
  IN       AMD_CONFIG_PARAMS *StdHeader
  )
{
  BOOLEAN IsContained;
  UINT32  SourceStrIndex;
  UINT32  TargetStrIndex;
  CHAR8 TargetChar;

  IsContained = FALSE;
  if ((TargetStr != NULL) && (SourceStr != NULL)) {
    for (SourceStrIndex = 0; SourceStr[SourceStrIndex] != '\0'; SourceStrIndex++) {
      // Compare TrgString with SrcString from frist charactor to the '\0'
      for (TargetStrIndex = 0; TargetStr[TargetStrIndex] != '\0'; TargetStrIndex++) {
        if (TargetStr[TargetStrIndex] != SourceStr[SourceStrIndex + TargetStrIndex]) {
          // if it's not match, try to check the upcase/lowcase
          TargetChar = 0;
          if (TargetStr[TargetStrIndex] >= 'a' && TargetStr[TargetStrIndex] <= 'z') {
            TargetChar = TargetStr[TargetStrIndex] - ('a' - 'A');
          } else if (TargetStr[TargetStrIndex] >= 'A' && TargetStr[TargetStrIndex] <= 'Z') {
            TargetChar = TargetStr[TargetStrIndex] + ('a' - 'A');
          }
          // compare again
          if (TargetChar != SourceStr[SourceStrIndex + TargetStrIndex]) {
            break;
          }
        }
      }

      if ((TargetStr[TargetStrIndex] == '\0') && (TargetStrIndex != 0)) {
        IsContained = TRUE;
        break;
      }
    }
  }
  return IsContained;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *  AdjustGranularity
 *
 *  Description:
 *    If cache size is greater than or equal to 32M, then set granularity
 *    to 64K. otherwise, set granularity to 1K
 *
 *  Parameters:
 *    @param[in]    *CacheSizePtr
 *
 *    @retval       CacheSize
 *
 *  Processing:
 *
 */
UINT32
AdjustGranularity (
  IN UINT32 *CacheSizePtr
  )
{
  UINT32 CacheSize;

  if (*CacheSizePtr >= 2047 * 1024) {
    CacheSize = (*CacheSizePtr / 64);
    CacheSize |= 0x80000000;
  } else if (*CacheSizePtr >= 0x8000) {
    CacheSize = (UINT16) (*CacheSizePtr / 64);
    CacheSize |= 0x8000;
  } else {
    CacheSize = (UINT16) *CacheSizePtr;
  }

  return (CacheSize);
}


