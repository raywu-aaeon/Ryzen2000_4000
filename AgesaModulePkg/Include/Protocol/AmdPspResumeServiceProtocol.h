/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD AGESA PSP Resume Service Protocol Initialization
 *
 * Contains code to initialize GUID for AMD_PSP_RESUME_SERVICE_PROTOCOL_GUID
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  PSP
 * @e \$Revision$   @e \$Date$
 *
 */
/****************************************************************************
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

#ifndef _AMD_PSP_RESUME_SERVICE_PROTOCOL_H_
#define _AMD_PSP_RESUME_SERVICE_PROTOCOL_H_

/// PSP resume callback priority level
#define PSP_RESUME_CALLBACK_LOWEST_LEVEL  0x1
#define PSP_RESUME_CALLBACK_LOW_LEVEL     0x40
#define PSP_RESUME_CALLBACK_MEDIUM_LEVEL  0x80
#define PSP_RESUME_CALLBACK_HIGH_LEVEL    0xC0
#define PSP_RESUME_CALLBACK_HIGHEST_LEVEL 0xFF

/// Define enum PSP_RESUME_CALLBACK_FLAG
typedef enum {
  PspResumeCallBackFlagBspOnly           = 0x01, ///< Call Back function will only be executed on BSP
  PspResumeCallBackFlagCorePrimaryOnly   = 0x02, ///< Call Back function will only be executed on CorePrimary
  PspResumeCallBackFlagCcxPrimaryOnly    = 0x03, ///< Call Back function will only be executed on CcxPrimary
  PspResumeCallBackFlagDiePrimaryOnly    = 0x04, ///< Call Back function will only be executed on DiePrimary
  PspResumeCallBackFlagSocketPrimaryOnly = 0x05, ///< Call Back function will only be executed on SocketPrimary
  PspResumeCallBackFlagAllCores          = 0x06, ///< Call Back function will be executed on AllCores
} PSP_RESUME_CALLBACK_FLAG;

/// Define enum RESUME_TYPE
typedef enum {
  ResumeFromConnectedStandby  = 0x01, ///< When resume from CS
  ResumeFromS3                = 0x02, ///< When resuming from S3
  InvalidResumeValue          = 0xFF  ///< Invalid Resume Value
} RESUME_TYPE;

typedef struct _PSP_RESUME_SERVICE_PROTOCOL PSP_RESUME_SERVICE_PROTOCOL;

typedef EFI_STATUS (EFIAPI *PSP_RESUME_CALLBACK) (
  IN  RESUME_TYPE   ResumeType,
  IN  VOID          *Context
  );

typedef EFI_STATUS (EFIAPI *PSP_RESUME_REGISTER) (
  IN       PSP_RESUME_SERVICE_PROTOCOL        *This,
  IN       PSP_RESUME_CALLBACK                CallBackFunction,
  IN OUT   VOID                               *Context,
  IN       UINTN                              CallbackPriority,
  IN       PSP_RESUME_CALLBACK_FLAG           Flag,
  OUT      EFI_HANDLE                         *DispatchHandle
);

typedef EFI_STATUS (EFIAPI *PSP_RESUME_UNREGISTER) (
  IN       PSP_RESUME_SERVICE_PROTOCOL        *This,
  IN       EFI_HANDLE                         DispatchHandle
);

/// Structure for PSP_RESUME_SERVICE_PROTOCOL protocol
typedef struct  _PSP_RESUME_SERVICE_PROTOCOL {
  PSP_RESUME_REGISTER    Register;        ///< Register fn
  PSP_RESUME_UNREGISTER  UnRegister;      ///< Unregister fn
} PSP_RESUME_SERVICE_PROTOCOL ;

extern EFI_GUID gAmdPspResumeServiceProtocolGuid;
#endif //_AMD_PSP_RESUME_SERVICE_PROTOCOL_H_

