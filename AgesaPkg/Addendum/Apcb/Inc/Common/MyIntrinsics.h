/* $NoKeywords:$ */
/**
 * @file
 *
 * MyIntrinsics.h
 *
 * Contains definition needed for PSP support
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  ApcbGenerator
 * @e \$Revision: 83676 $   @e \$Date: 2012-12-07 15:57:01 -0600 (Fri, 07 Dec 2012) $
 *
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
 */

 #ifndef _MYINTRINSICS_H_
 #define _MYINTRINSICS_H_

//HDTOUT debug controls
//#define IDSOPT_IDS_ENABLED TRUE
//#define IDSOPT_TRACING_ENABLED TRUE
//#define IDSOPT_TRACING_CONSOLE_HDTOUT TRUE
//#define IDSOPT_TRACING_CONSOLE_SERIALPORT TRUE
//#define IDSOPT_TRACING_CONSOLE_REDIRECT_IO TRUE
//#define IDSOPT_DEBUG_PRINT_IO_PORT (default 0x80)

  #define CODE_GROUP(arg)
  #define RDATA_GROUP(arg)
  #define IN
  #define OUT
  #define STATIC static
  #define VOLATILE volatile
      #ifndef TRUE
        #define TRUE  1
      #endif
      #ifndef FALSE
        #define FALSE 0
      #endif
  //#define CONST const - avoid const until the large job of making agesa use it consistently is complete
  #ifndef CONST
  #define CONST
  #endif
  #define ROMDATA
  #define CALLCONV
  #define _8BYTE_ALIGN __attribute__ ((aligned (8)))
  #define _4BYTE_ALIGN __attribute__ ((aligned (4)))
  #define _2BYTE_ALIGN __attribute__ ((aligned (2)))
  #define _1BYTE_ALIGN __attribute__ ((aligned (1)))
  #define NON_BIT_REGISTER_TYPE
//#include <commontypes.h>

// #define IDSOPT_PSP_IDS_ENABLED TRUE
#endif


