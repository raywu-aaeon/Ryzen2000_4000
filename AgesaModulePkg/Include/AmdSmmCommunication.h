/* $NoKeywords:$ */
/**
 * @file
 *
 * AmdSmmCommunication.h
 *
 * Contains definition for AmdSmmCommunication
 *
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

#ifndef _AMD_SMM_COMMUNICATION_H_
#define _AMD_SMM_COMMUNICATION_H_

extern EFI_GUID gAmdSmmCommunicationHandleGuid;

#define AMD_SMM_COMMUNICATION_ID_S3SCRIPT       0x1     ///< ID for S3 script

#define AMD_SMM_COMMUNICATION_CMN_BUFFER_SIZE (OFFSET_OF (EFI_SMM_COMMUNICATE_HEADER, Data)  + sizeof (AMD_SMM_COMMUNICATION_CMN))
/// SMM communication common buffer
typedef struct _AMD_SMM_COMMUNICATION_CMN {
  UINT32                       id;         ///< ID of smm communication buffer
} AMD_SMM_COMMUNICATION_CMN;

#define AMD_SMM_COMMUNICATION_S3SCRIPT_BUFFER_SIZE (OFFSET_OF (EFI_SMM_COMMUNICATE_HEADER, Data)  + sizeof (AMD_SMM_COMMUNICATION_S3SCRIPT))

typedef struct _AMD_SMM_COMMUNICATION_S3SCRIPT {
  UINT32                       id;         ///< ID of smm communication buffer
  VOID                         *PrivateDataAddress;  ///< Point to AmdS3LibPrivateData
} AMD_SMM_COMMUNICATION_S3SCRIPT;

//Sample for new added command
// #define AMD_SMM_COMMUNICATION_ID_XX       0x2     ///< ID for XX
// #define AMD_SMM_COMMUNICATION_XX_BUFFER_SIZE (OFFSET_OF (EFI_SMM_COMMUNICATE_HEADER, Data)  + sizeof (_AMD_SMM_COMMUNICATION_XX))
// typedef struct _AMD_SMM_COMMUNICATION_XX {
//   UINT32                       id;         ///< ID of smm communication buffer
//   XX_STRUCT                    xx;         ///< Structure for XX
// } _AMD_SMM_COMMUNICATION_XX;

#endif // _AMD_SMM_COMMUNICATION_H_

