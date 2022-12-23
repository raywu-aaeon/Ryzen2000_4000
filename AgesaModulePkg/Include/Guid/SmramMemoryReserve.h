
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

/** @file
  Definition of GUIDed HOB for reserving SMRAM regions.

  This file defines:
  * the GUID used to identify the GUID HOB for reserving SMRAM regions.
  * the data structure of SMRAM descriptor to describe SMRAM candidate regions
  * values of state of SMRAM candidate regions
  * the GUID specific data structure of HOB for reserving SMRAM regions.
  This GUIDed HOB can be used to convey the existence of the T-SEG reservation and H-SEG usage

Copyright (c) 2007 - 2010, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials are licensed and made available under
the terms and conditions of the BSD License that accompanies this distribution.
The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php.

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

  @par Revision Reference:
  GUIDs defined in SmmCis spec version 0.9.

**/

#ifndef _EFI_SMM_PEI_SMRAM_MEMORY_RESERVE_H_
#define _EFI_SMM_PEI_SMRAM_MEMORY_RESERVE_H_

#define EFI_SMM_PEI_SMRAM_MEMORY_RESERVE \
  { \
    0x6dadf1d1, 0xd4cc, 0x4910, {0xbb, 0x6e, 0x82, 0xb1, 0xfd, 0x80, 0xff, 0x3d } \
  }

/**
* GUID specific data structure of HOB for reserving SMRAM regions.
*
* Inconsistent with specification here:
* EFI_HOB_SMRAM_DESCRIPTOR_BLOCK has been changed to EFI_SMRAM_HOB_DESCRIPTOR_BLOCK.
* This inconsistency is kept in code in order for backward compatibility.
**/
typedef struct {
  ///
  /// Designates the number of possible regions in the system
  /// that can be usable for SMRAM.
  ///
  /// Inconsistent with specification here:
  /// In Framework SMM CIS 0.91 specification, it defines the field type as UINTN.
  /// However, HOBs are supposed to be CPU neutral, so UINT32 should be used instead.
  ///
  UINT32                NumberOfSmmReservedRegions;
  ///
  /// Used throughout this protocol to describe the candidate
  /// regions for SMRAM that are supported by this platform.
  ///
  EFI_SMRAM_DESCRIPTOR  Descriptor[1];
} EFI_SMRAM_HOB_DESCRIPTOR_BLOCK;

extern EFI_GUID gEfiSmmPeiSmramMemoryReserveGuid;

#endif

