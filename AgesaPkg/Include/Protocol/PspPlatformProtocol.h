/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD Platform Protocol
 *
 * Contains definitions for AMD_PSP_PLATFORM_PROTOCOL_GUID
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  UEFI
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-10 02:28:05 +0800 (Wed, 10 Dec 2014) $
 *
 */
/*
 ****************************************************************************
 * AMD Generic Encapsulated Software Architecture
 *
 * Description: AmdAgesaDxeProtocol.h - DXE Protocol and GUID Declaration.
 *
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

#ifndef _PSP_PLATFORM_PROTOCOL_H_
#define _PSP_PLATFORM_PROTOCOL_H_

// !!! NOTE Please don't change the GUID defined below
// {CCF14A29-37E0-48ad-9005-1F89622FB798}
#define AMD_PSP_PLATFORM_PROTOCOL_GUID \
  { 0xccf14a29, 0x37e0, 0x48ad, { 0x90, 0x5, 0x1f, 0x89, 0x62, 0x2f, 0xb7, 0x98 } }

/// Resume Handoff Structure
typedef struct {
  UINT32  GdtOffset;                              // GDT table offset for RSM
  UINT16  CodeSelector;                           // CODE Segment Selector
  UINT16  DataSelector;                           // DATA Segment Selector
  UINT32  RsmEntryPoint;                          // IP Address after executing rsm command
  UINT32  EdxResumeSignature;                     // Value keep in EDX after executing rsm command
} RSM_HANDOFF_INFO;


/// PSP Platform Protocol, provide PSP platform customized information
typedef struct _PSP_PLATFORM_PROTOCOL {
  BOOLEAN                 CpuContextResumeEnable; // TRUE:Enable CPU Context Resume, FALSE:Disable CPU Context Resume
  UINT8                   SwSmiCmdtoBuildContext; // SW SMI number for build Cpu Context
  UINT32                  BspStackSize;           // BSP Stack Size for resume
  UINT32                  ApStackSize;            // AP Stack Size for resume
  RSM_HANDOFF_INFO        *RsmHandOffInfo;        // Resume Handoff structure include GDTTable Offset, CS&DS Selector, Entrypoint for Resume
                                                  // Also a signature kept in EDX for identification
} PSP_PLATFORM_PROTOCOL;

extern EFI_GUID gPspPlatformProtocolGuid;

#endif //_PSP_PLATFORM_PROTOCOL_H_

