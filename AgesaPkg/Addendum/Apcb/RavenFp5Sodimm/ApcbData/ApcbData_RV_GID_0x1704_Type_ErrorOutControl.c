
/* $NoKeywords:$ */
/**
 * @file
 *
 * @e \$Revision:$   @e \$Date:$
 */
/*****************************************************************************
 *
 * Copyright 2015 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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

#include "MyPorting.h"
#include <RV/APCB.h>
#include <ApcbCustomizedDefinitions.h>
#include <ApcbDefaults.h>

CHAR8 mDummyBuf;

APCB_TYPE_DATA_START_SIGNATURE();
APCB_TYPE_HEADER       ApcbTypeHeader = { APCB_GROUP_MEMORY, APCB_MEM_TYPE_ERROR_OUT_EVENT_CONTROL, (sizeof(APCB_TYPE_HEADER) + sizeof (PSP_ERROR_OUT_CONTROL_STRUCT)), 0, 0, 0 };  // SizeOfType will be fixed up by tool

///< Platform Specific Overrides
PSP_ERROR_OUT_CONTROL_STRUCT PspEventOutControl = {
  FALSE,
  FALSE,
  FALSE,
  FALSE,
  0x84,
  15000,
  0x80,
  TRUE,
  4,
  4,
  6,
  6,
  FALSE,
  {
    85,
    0x01,
    0xC0
  },
  {
    {BEEP_ERROR_TYPE_GENERAL|BEEP_ERROR_OPERATION_MASK,     0x5555,   0x00000063},
    {BEEP_ERROR_TYPE_MEMORY|BEEP_ERROR_OPERATION_MASK,      0x5555,   0x00000065},
    {BEEP_ERROR_TYPE_DF|BEEP_ERROR_OPERATION_MASK,          0x5555,   0x00000067},
    {BEEP_ERROR_TYPE_CCX|BEEP_ERROR_OPERATION_MASK,         0x5555,   0x00000069},
    {BEEP_ERROR_TYPE_GNB|BEEP_ERROR_OPERATION_MASK,         0x5555,   0x0000006B},
    {BEEP_ERROR_TYPE_PSP|BEEP_ERROR_OPERATION_MASK,         0x5555,   0x0000006D},
    {BEEP_ERROR_TYPE_SMU|BEEP_ERROR_OPERATION_MASK,         0x5555,   0x0000006F},
    {BEEP_ERROR_TYPE_UNKNOW|BEEP_ERROR_OPERATION_MASK,      0x5555,   0x00000063}
  },
  FALSE
};  

APCB_TYPE_DATA_END_SIGNATURE();


int main (IN int argc, IN char * argv [ ])
{
  return 0;
}





