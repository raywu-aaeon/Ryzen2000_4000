/*****************************************************************************
 *
 * Copyright 2014 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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
 * ***************************************************************************
 */

#ifndef _AMD_MEMORY_INFO_HOB_H_
#define _AMD_MEMORY_INFO_HOB_H_

// {45DC9E40-0336-4878-B5BB-AA7675C5C8EF}
#define AMD_MEMORY_INFO_HOB_GUID \
  { 0x45dc9e40, 0x336, 0x4878, 0xb5, 0xbb, 0xaa, 0x76, 0x75, 0xc5, 0xc8, 0xef }

extern EFI_GUID gAmdMemoryInfoHobGuid;

#pragma pack (push, 1)

/// Memory descriptor structure for each memory rang
typedef struct {
  UINT64  Base;                             ///< Base address of memory rang
  UINT64  Size;                             ///< Size of memory rang
  UINT32  Attribute;                        ///< Attribute of memory rang
} AMD_MEMORY_RANGE_DESCRIPTOR;

#define AMD_MEMORY_ATTRIBUTE_AVAILABLE      0x1
#define AMD_MEMORY_ATTRIBUTE_UMA            0x2
#define AMD_MEMORY_ATTRIBUTE_RESERVED       0x4

/// Memory info HOB structure
typedef struct  {
  UINT32  Version;                          ///< Version of HOB structure
  UINT32  NumberOfDescriptor;               ///< Number of memory range descriptor
  AMD_MEMORY_RANGE_DESCRIPTOR  Ranges[1];   ///< Memory ranges array
} AMD_MEMORY_INFO_HOB;

#pragma pack (pop)

#define AMD_MEMORY_INFO_HOB_VERISION        0x00000100ul  // Ver: 00.00.01.00

#endif // _AMD_MEMORY_INFO_HOB_H_

