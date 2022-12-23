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
 */

#ifndef __CBS_CALLBACK_LIB_H__
#define __CBS_CALLBACK_LIB_H__

//
// This is the generated IFR binary data for each formset defined in VFR.
// This data array is ready to be used as input of HiiAddPackages() to
// create a packagelist (which contains Form packages, String packages, etc).
//
extern UINT8  AmdCbsFormBin[];

//
// This is the generated String package data for all .UNI files.
// This data array is ready to be used as input of HiiAddPackages() to
// create a packagelist (which contains Form packages, String packages, etc).
//
extern UINT8  CbsSetupLibInstanceStrings[];

extern UINTN  CbsVariableSize;

EFI_STATUS
AmdCbsSetupCallbackRoutine (
  IN  CONST EFI_HII_CONFIG_ACCESS_PROTOCOL   *This,
  IN  EFI_BROWSER_ACTION                     Action,
  IN  EFI_QUESTION_ID                        QuestionId,
  IN  UINT8                                  Type,
  IN  EFI_IFR_TYPE_VALUE                     *Value,
  OUT EFI_BROWSER_ACTION_REQUEST             *ActionRequest,
  OUT UINT8                                  *IfrData,
  IN  EFI_HII_HANDLE                         HiiHandle
  );

VOID
CbsWriteDefalutValue (
  IN UINT8   *IfrData
  );

VOID
AmdSaveCbsConfigData (
  IN UINT8   *IfrData
  );

VOID
CbsComboIdentify (
  IN UINT8   *IfrData
  );

EFI_STATUS
EFIAPI
CbsSetupLoadDefaultFunc (
  );

BOOLEAN
CbsFamilyIdentify (
  );

typedef struct {
  UINT16 RawFamily;                ///< CPUID Fn0000_0001_EAX[BaseFamily] + [ExtFamily]
  UINT8  RawExtModel;              ///< CPUID Fn0000_0001_EAX[ExtModel]
  UINT8  RawBaseModel;             ///< CPUID Fn0000_0001_EAX[BaseModel]
  UINT8  RawStepping;              ///< CPUID Fn0000_0001_EAX[Stepping]
  UINT8  RawPkgType;               ///< CPUID Fn0000_0001_EBX[PkgType]
  UINT8  ComboFlag;
} COMBO_FLAG_XLAT;

#define COMBO_FLAG_UNKNOWN  254
#define COMBO_FLAG_RESERVED 255
#define COMBO_FLAG_XLAT_TERMINATOR   {'x', 'x', 'x', 'x', 'x', COMBO_FLAG_UNKNOWN}

#endif //__CBS_CALLBACK_LIB_H__

