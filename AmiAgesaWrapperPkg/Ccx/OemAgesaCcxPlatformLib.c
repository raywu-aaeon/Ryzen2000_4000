/**
 * @file
 *
 * Required OEM hooks for CCX initialization
 *
 * Contains AMD AGESA debug macros and library functions
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  IDS
 * @e \$Revision$   @e \$Date$
 */
/*****************************************************************************
 * Copyright 2008 - 2018 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
 *
 * AMD is granting you permission to use this software (the Materials)
 * pursuant to the terms and conditions of your Software License Agreement
 * with AMD.  This header does *NOT* give you permission to use the Materials
 * or any rights under AMD's intellectual property.  Your use of any portion
 * of these Materials shall constitute your acceptance of those terms and
 * conditions.  If you do not agree to the terms and conditions of the Software
 * License Agreement, please do not use any portion of these Materials.
 *
 * CONFIDENTIALITY:  The Materials and all other information, identified as
 * confidential and provided to you by AMD shall be kept confidential in
 * accordance with the terms and conditions of the Software License Agreement.
 *
 * LIMITATION OF LIABILITY: THE MATERIALS AND ANY OTHER RELATED INFORMATION
 * PROVIDED TO YOU BY AMD ARE PROVIDED "AS IS" WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTY OF ANY KIND, INCLUDING BUT NOT LIMITED TO WARRANTIES OF
 * MERCHANTABILITY, NONINFRINGEMENT, TITLE, FITNESS FOR ANY PARTICULAR PURPOSE,
 * OR WARRANTIES ARISING FROM CONDUCT, COURSE OF DEALING, OR USAGE OF TRADE.
 * IN NO EVENT SHALL AMD OR ITS LICENSORS BE LIABLE FOR ANY DAMAGES WHATSOEVER
 * (INCLUDING, WITHOUT LIMITATION, DAMAGES FOR LOSS OF PROFITS, BUSINESS
 * INTERRUPTION, OR LOSS OF INFORMATION) ARISING OUT OF AMD'S NEGLIGENCE,
 * GROSS NEGLIGENCE, THE USE OF OR INABILITY TO USE THE MATERIALS OR ANY OTHER
 * RELATED INFORMATION PROVIDED TO YOU BY AMD, EVEN IF AMD HAS BEEN ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGES.  BECAUSE SOME JURISDICTIONS PROHIBIT THE
 * EXCLUSION OR LIMITATION OF LIABILITY FOR CONSEQUENTIAL OR INCIDENTAL DAMAGES,
 * THE ABOVE LIMITATION MAY NOT APPLY TO YOU.
 *
 * AMD does not assume any responsibility for any errors which may appear in
 * the Materials or any other related information provided to you by AMD, or
 * result from use of the Materials or any related information.
 *
 * You agree that you will not reverse engineer or decompile the Materials.
 *
 * NO SUPPORT OBLIGATION: AMD is not obligated to furnish, support, or make any
 * further information, software, technical information, know-how, or show-how
 * available to you.  Additionally, AMD retains the right to modify the
 * Materials at any time, without notice, and is not obligated to provide such
 * modified Materials to you.
 *
 * U.S. GOVERNMENT RESTRICTED RIGHTS: The Materials are provided with
 * "RESTRICTED RIGHTS." Use, duplication, or disclosure by the Government is
 * subject to the restrictions as set forth in FAR 52.227-14 and
 * DFAR252.227-7013, et seq., or its successor.  Use of the Materials by the
 * Government constitutes acknowledgement of AMD's proprietary rights in them.
 *
 * EXPORT ASSURANCE:  You agree and certify that neither the Materials, nor any
 * direct product thereof will be exported directly or indirectly, into any
 * country prohibited by the United States Export Administration Act and the
 * regulations thereunder, without the required authorization from the U.S.
 * government nor will be used for any purpose prohibited by the same.
 ******************************************************************************
 */
#include <Uefi.h>
#include "Token.h"
#include "Library/IoLib.h"

// [Fam15 only]
/*--------------------------------------------------------------------------------------*/
/**
 *  Hook to store the vector that all APs should jump to out of reset to a non-volatile,
 *  shared location.
 *
 *  @param[in]     ApInitAddress     Address of the code that AP should jump to
 *  @param[in,out] ContentToRestore  The current value in the non-volatile storage
 *
 **/
/*--------------------------------------------------------------------------------------*/
VOID
SaveApInitVector (
  IN       UINT32  ApInitAddress,
  IN OUT   UINT32  *ContentToRestore
  )
{
#if AGESA_AP_INIT_BY_CMOS == 1
  UINT32                  Value32;
  UINTN                   Index;

  //
  // !!! This is one of the suggested solutions where BSP can launch AP without
  // going through intitializing of Pei Core Services. This function saves the
  // ApInit pointer. In this process, the current content of CMOS gets saved
  // and returned to caller which will be restored once APInit is done by
  // calling RestoreContentVector
  //
  for (Index = AGESA_AP_INIT_CMOS_LOCATION_OFFSET; Index <= (AGESA_AP_INIT_CMOS_LOCATION_OFFSET + 3); Index++) {
    IoWrite8 ( 0x72, Index);
    Value32 = IoRead8 ( 0x73);
    Value32 = (Value32 & 0x000000FF);
    *ContentToRestore |= (Value32 << ((Index - AGESA_AP_INIT_CMOS_LOCATION_OFFSET) * 8));
    Value32 = (UINT32) (ApInitAddress & 0xff);
    IoWrite8 ( 0x73,  Value32);
    ApInitAddress >>= 8;
  }
#endif
}

// [Fam15 only]
/*--------------------------------------------------------------------------------------*/
/**
 *  Hook to restore the initial content of the non-volatile storage location.
 *
 *  @param[in]     ContentToRestore  The value to restore
 *
 **/
/*--------------------------------------------------------------------------------------*/
VOID
RestoreContentVector (
  IN       UINT32  ContentToRestore
  )
{
#if AGESA_AP_INIT_BY_CMOS == 1
  UINT32                 Value32;
  UINTN                  Index;

  Value32 = 0;
  for (Index = AGESA_AP_INIT_CMOS_LOCATION_OFFSET; Index <= (AGESA_AP_INIT_CMOS_LOCATION_OFFSET + 3); Index++) {
      IoWrite8 (0x72, Index);
      Value32 = (UINT8) ((ContentToRestore >> (Index - AGESA_AP_INIT_CMOS_LOCATION_OFFSET) * 8));
      IoWrite8 (0x73, Value32);
  }
#endif
}

