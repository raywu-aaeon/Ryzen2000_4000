/* $NoKeywords:$ */
/**
 * @file
 *
 * PSP related functions in SMM
 *
 * Contains PSP SMM Resume functions prototype
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  PSP
 * @e \$Revision$   @e \$Date$
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

#ifndef _PSP_SMM_RESUME_SERVIES_H_
#define _PSP_SMM_RESUME_SERVIES_H_

#include "PiSmm.h"
#include <Protocol/AmdPspResumeServiceProtocol.h>



/// Define the structure for Smmsave override during resume @todo move into seperate OEM header
typedef struct {
  UINT16   CodeSegOverrideValue;  ///< CodeSegOverrideValue
  UINT16   CodeSegAttrib;         ///< CodeSegAttrib
  UINT16   DateSegOverrideValue;  ///< DateSegOverrideValue
  UINT16   DataSegAttrib;         ///< DataSegAttrib
  UINT64   RipBspOverrideValue;   ///< RipBspOverrideValue
  UINT64   RipApOverrideValue;    ///< RipApOverrideValue
  UINT64   RaxOverrideValue;      ///< RaxOverrideValue
  UINT64   RbxOverrideValue;      ///< RbxOverrideValue
  UINT64   RdxOverrideValue;      ///< RdxOverrideValue
  UINT64   StackBase;             ///< RspOverrideValue
  UINT64   BspStackSize;          ///< RspOverrideValue
  UINT64   ApStackSize;           ///< RspOverrideValue
  UINT64   GdtOverrideValue;      ///< GdtOverrideValue
  UINT64   GdtOverrideLimit;      ///< GdtOverrideLimit
  UINT64   Cr0;                   ///< Cr0
  UINT64   Cr3;                   ///< Cr3
  UINT64   Cr4;                   ///< Cr4
} REGISTER_OVERRIDE;


EFI_STATUS
EFIAPI
InstallPspResumeCallbackProtocolV2 ();

EFI_STATUS
EFIAPI
PspRegisterV2 (
  IN       PSP_RESUME_SERVICE_PROTOCOL        *This,
  IN       PSP_RESUME_CALLBACK                CallBackFunction,
  IN OUT   VOID                               *Context,
  IN       UINTN                              CallbackPriority,
  IN       PSP_RESUME_CALLBACK_FLAG           Flag,
     OUT   EFI_HANDLE                         *DispatchHandle
);


EFI_STATUS
EFIAPI
PspUnregisterV2 (
  IN       PSP_RESUME_SERVICE_PROTOCOL        *This,
  IN       EFI_HANDLE                         DispatchHandle
  );

EFI_STATUS
EFIAPI
PspResumeServiceCallBackV2 (
  IN       UINT8 ResumeType
   );

VOID S3ExitToBiosV2 ();

VOID UpdateS3SaveAreaMapV2 ();

/// Define layout of SMM save area
typedef struct {
  UINT16 ES_Selector;                ///< 0xFE00, sizeof (UINT16)
  UINT16 ES_Attributes;              ///< 0xFE02, sizeof (UINT16)
  UINT32 ES_Limit;                   ///< 0xFE04, sizeof (UINT32)
  UINT64 ES_Base;                    ///< 0xFE08, sizeof (UINT64)
  UINT16 CS_Selector;                ///< 0xFE10, sizeof (UINT16)
  UINT16 CS_Attributes;              ///< 0xFE12, sizeof (UINT16)
  UINT32 CS_Limit;                   ///< 0xFE14, sizeof (UINT32)
  UINT64 CS_Base;                    ///< 0xFE18, sizeof (UINT64)
  UINT16 SS_Selector;                ///< 0xFE20, sizeof (UINT16)
  UINT16 SS_Attributes;              ///< 0xFE22, sizeof (UINT16)
  UINT32 SS_Limit;                   ///< 0xFE24, sizeof (UINT32)
  UINT64 SS_Base;                    ///< 0xFE28, sizeof (UINT64)
  UINT16 DS_Selector;                ///< 0xFE30, sizeof (UINT16)
  UINT16 DS_Attributes;              ///< 0xFE32, sizeof (UINT16)
  UINT32 DS_Limit;                   ///< 0xFE34, sizeof (UINT32)
  UINT64 DS_Base;                    ///< 0xFE38, sizeof (UINT64)
  UINT16 FS_Selector;                ///< 0xFE40, sizeof (UINT16)
  UINT16 FS_Attributes;              ///< 0xFE42, sizeof (UINT16)
  UINT32 FS_Limit;                   ///< 0xFE44, sizeof (UINT32)
  UINT64 FS_Base;                    ///< 0xFE48, sizeof (UINT64)
  UINT16 GS_Selector;                ///< 0xFE50, sizeof (UINT16)
  UINT16 GS_Attributes;              ///< 0xFE52, sizeof (UINT16)
  UINT32 GS_Limit;                   ///< 0xFE54, sizeof (UINT32)
  UINT64 GS_Base;                    ///< 0xFE58, sizeof (UINT64)
  UINT8  Rsvd_FE60_63[4];            ///< 0xFE60, sizeof (UINT32)
  UINT16 GDTR_Limit;                 ///< 0xFE64, sizeof (UINT16)
  UINT8  Rsvd_FE66_FE67[2];          ///< 0xFE66, sizeof (UINT16)
  UINT64 GDTR_Base;                  ///< 0xFE68, sizeof (UINT64)
  UINT16 LDTR_Selector;              ///< 0xFE70, sizeof (UINT16)
  UINT16 LDTR_Attributes;            ///< 0xFE72, sizeof (UINT16)
  UINT32 LDTR_Limit;                 ///< 0xFE74, sizeof (UINT32)
  UINT64 LDTR_Base;                  ///< 0xFE78, sizeof (UINT64)
  UINT8  Rsvd_FE80_FE83[4];          ///< 0xFE80, sizeof (UINT32)
  UINT16 IDTR_Limit;                 ///< 0xFE84, sizeof (UINT16)
  UINT8  Rsvd_FE86_FE87[2];          ///< 0xFE86, sizeof (UINT16)
  UINT64 IDTR_Base;                  ///< 0xFE88, sizeof (UINT64)
  UINT16 TR_Selector;                ///< 0xFE90, sizeof (UINT16)
  UINT16 TR_Attributes;              ///< 0xFE92, sizeof (UINT16)
  UINT32 TR_Limit;                   ///< 0xFE94, sizeof (UINT32)
  UINT64 TR_Base;                    ///< 0xFE98, sizeof (UINT64

  UINT64 IO_RIP;                     ///< 0xFEA0, sizeof (UINT64)
  UINT64 IO_RCX;                     ///< 0xFEA8, sizeof (UINT64)
  UINT64 IO_RSI;                     ///< 0xFEB0, sizeof (UINT64)
  UINT64 IO_RDI;                     ///< 0xFEB8, sizeof (UINT64)
  UINT32 IO_Restart_Dword;           ///< 0xFEC0, sizeof (UINT32)
  UINT8  Rsvd_FEC4_FEC7[4];          ///< 0xFEC4, sizeof (UINT32)
  UINT8 IO_Restart;                  ///< 0xFEC8, sizeof (UINT8)
  UINT8 Auto_Halt_Restart;           ///< 0xFEC9, sizeof (UINT8)
  UINT8  Rsvd_FECA_FECF[6];          ///< 0xFECA, 6 byte

  UINT64 EFER;                       ///< 0xFED0, sizeof (UINT64)
  UINT64 SVM_Guest;                  ///< 0xFED8, sizeof (UINT64)
  UINT64 SVM_Guest_VMCB_Address;     ///< 0xFEE0, sizeof (UINT64)
  UINT64 SVM_Guest_Virtual_Interrupt;///< 0xFEE8, sizeof (UINT64)
  UINT8  Rsvd_FFF0_FFFB[12];         ///< 0xFEF0, 12 byte
  UINT32 SMM_Revision_Identifier1;   ///< 0xFEFC, sizeof (UINT32)
  UINT32 SMBASE;                     ///< 0xFF00, sizeof (UINT32)
  UINT8  Rsvd_FF04_FF1F[28];         ///< 0xFF04, 28 byte
  UINT64 SVM_Guest_PAT;              ///< 0xFF20, sizeof (UINT64)
  UINT64 SVM_Host_EFER;              ///< 0xFF28, sizeof (UINT64)
  UINT64 SVM_Host_CR4;               ///< 0xFF30, sizeof (UINT64)
  UINT64 SVM_Host_CR3;               ///< 0xFF38, sizeof (UINT64)
  UINT64 SVM_Host_CR0;               ///< 0xFF40, sizeof (UINT64)

  UINT64 CR4;                        ///< 0xFF48, sizeof (UINT64)
  UINT64 CR3;                        ///< 0xFF50, sizeof (UINT64)
  UINT64 CR0;                        ///< 0xFF58, sizeof (UINT64)
  UINT64 DR7;                        ///< 0xFF60, sizeof (UINT64)
  UINT64 DR6;                        ///< 0xFF68, sizeof (UINT64)
  UINT64 RFLAGS;                     ///< 0xFF70, sizeof (UINT64)
  UINT64 RIP;                        ///< 0xFF78, sizeof (UINT64)

  UINT64 R15;                        ///< 0xFF80, sizeof (UINT64)
  UINT64 R14;                        ///< 0xFF88, sizeof (UINT64)
  UINT64 R13;                        ///< 0xFF90, sizeof (UINT64)
  UINT64 R12;                        ///< 0xFF98, sizeof (UINT64)
  UINT64 R11;                        ///< 0xFFA0, sizeof (UINT64)
  UINT64 R10;                        ///< 0xFFA8, sizeof (UINT64)
  UINT64 R9;                         ///< 0xFFB0, sizeof (UINT64)
  UINT64 R8;                         ///< 0xFFB8, sizeof (UINT64)
  UINT64 RDI;                        ///< 0xFFC0, sizeof (UINT64)
  UINT64 RSI;                        ///< 0xFFC8, sizeof (UINT64)
  UINT64 RBP;                        ///< 0xFFD0, sizeof (UINT64)
  UINT64 RSP;                        ///< 0xFFD8, sizeof (UINT64)
  UINT64 RBX;                        ///< 0xFFE0, sizeof (UINT64)
  UINT64 RDX;                        ///< 0xFFE8, sizeof (UINT64)
  UINT64 RCX;                        ///< 0xFFF0, sizeof (UINT64)
  UINT64 RAX;                        ///< 0xFFF8, sizeof (UINT64)
} SMM_SAVE_MAP;


/// Define structure for Smm callback on resume from sleep
typedef struct {
  LIST_ENTRY                ListEntry;          ///< Linked list
  PSP_RESUME_CALLBACK       CallBackFunction;   ///< Callback fn.
  UINTN                     CallbackPriority;   ///< Priority/Order of callback
  VOID                      *Context;           ///< Context
  PSP_RESUME_CALLBACK_FLAG  Flag;               ///< Flag
} PSP_SMM_CALLBACK_NODE;

#endif //_PSP_SMM_RESUME_SERVIES_H_

