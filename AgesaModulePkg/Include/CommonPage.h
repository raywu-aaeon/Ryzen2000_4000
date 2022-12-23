/* $NoKeywords:$ */
/**
 * @file
 *
 * Create outline and references for Processor Common Component mainpage documentation.
 *
 * Design guides, maintenance guides, and general documentation, are
 * collected using this file onto the documentation mainpage.
 * This file contains doxygen comment blocks, only.
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Documentation
 * @e \$Revision: 334519 $   @e \$Date: 2016-01-15 15:48:51 +0800 (Fri, 15 Jan 2016) $
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

/**
 * @page commonmain Processor Common Component Documentation
 *
 * Additional documentation for the Common component consists of
 *
 * - Maintenance Guides:
 *   - @subpage amdconfigparamname "Naming Guidelines for type AMD_CONFIG_PARAMS"
 * - Design Guides:
 *   - add here >>>
 *
 */

/**
 * @page amdconfigparamname Naming Guidelines for type AMD_CONFIG_PARAMS
 * @par
 * These are the guidelines for naming objects of type AMD_CONFIG_PARAMS and AMD_CONFIG_PARAMS * in AGESA code.
 * <ul>
 *
 * <li>
 * Formal parameter names of type AMD_CONFIG_PARAMS and AMD_CONFIG_PARAMS * will always be named
 * StdHeader. This covers all function prototypes, function definitions, and method typedefs (a
 * typedef of a function prototype) in AGESA code. Examples:
 * @n @code
 * VOID
 *   LibAmdPciFindNextCap (
 *     IN OUT   PCI_ADDR *Address,
 *     IN       AMD_CONFIG_PARAMS *StdHeader
 *     )
 *
 * typedef VOID F_DO_TABLE_ENTRY (
 *   IN       TABLE_ENTRY_DATA       *CurrentEntry,
 *   IN       PLATFORM_CONFIGURATION *PlatformConfig,
 *   IN       AMD_CONFIG_PARAMS      *StdHeader
 *   );
 *
 * @endcode
 *
 * <li>
 * Structure members of type AMD_CONFIG_PARAMS or AMD_CONFIG_PARAMS * will always be named StdHeader. Examples:
 * @n @code
   /// Example of struct member naming.
 * typedef struct {
 *   IN OUT   AMD_CONFIG_PARAMS StdHeader;             ///< Standard Header
 *   IN       PLATFORM_CONFIGURATION PlatformConfig;   ///< platform operational characteristics.
 * } AMD_CPU_RECOVERY_PARAMS;
 *
 * @endcode
 *
 * <li>
 * Routines which define local variables of type AMD_CONFIG_PARAMS or AMD_CONFIG_PARAMS * should
 * name the local variable as closely as practical to StdHeader, but otherwise freedom is allowed. Example:
 * @n @code
 * AMD_CONFIG_PARAMS *NewStdHeader;
 * [...]
 * NewStdHeader = (AMD_CONFIG_PARAMS *)AllocHeapParams.BufferPtr;
 * @endcode
 *
 * <li>
 * Arguments to routines with AMD_CONFIG_PARAMS or AMD_CONFIG_PARAMS * formal parameters are not
 * checked.  Freedom is allowed in order to conform to these guidelines in a practical, readable
 * way.  This includes typecast arguments.  Examples:
 * @n @code
 * Status = GetEventLog (&LogEvent, (AMD_CONFIG_PARAMS *)Event);
 *
 * MemS3ExitSelfRefRegDA (NBPtr, &MemPtr->StdHeader);
 * @endcode
 *
 * </ul>
 *
 */

