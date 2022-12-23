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

#include <Uefi.h>
#include "PiDxe.h"
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include "CbsHookDxeLib.h"

typedef struct _CBS_CONFIG AMD_SYSTEM_CONFIGURATION;
extern EFI_RUNTIME_SERVICES *gRT;

CBS_CONFIG *pCbsConfig;
static CBS_DXE_PROTOCOL mCbsProtocolInstance=
{
  CbsHookFunc,
  0
};

VOID
CbsVariableLoadDefault(
  UINT8 *pVariableData
  )
{
  EFI_STATUS   Status;
  UINT32       RecordOffset;
  CBS_CONFIG   TempVariable;
  UINT8        *tempBuffer;
  UINT32       i;
  UINTN        BufferSize;

  tempBuffer = (UINT8*)&TempVariable;
  BufferSize = 0;

  Status = gRT->GetVariable (CBS_SYSTEM_CONFIGURATION_NAME,
                             &gCbsSystemConfigurationGuid,
                             NULL,
                             &BufferSize,
                             pVariableData
                             );
  if ((Status == EFI_BUFFER_TOO_SMALL) && (BufferSize == sizeof(CBS_CONFIG))) {
    Status = gRT->GetVariable (CBS_SYSTEM_CONFIGURATION_NAME,
                               &gCbsSystemConfigurationGuid,
                               NULL,
                               &BufferSize,
                               pVariableData
                               );
    if (EFI_ERROR (Status)) {
      DEBUG ((EFI_D_ERROR, "No CBS Variable, Force loading CBS variable default value.(Status=0x%x)\n", Status));
      CbsWriteDefalutValue(pVariableData);
    } else {
      CbsWriteDefalutValue(tempBuffer);
      DEBUG ((EFI_D_ERROR, "Found CBS Variable: oID=0x%08x, nID=0x%08x, Offset = 0x%08x\n", 
              (UINT32) *(UINT32 *)pVariableData, 
              (UINT32) *(UINT32 *)tempBuffer,
              (UINT32) *(UINT32*)(pVariableData + sizeof(UINT32))
              ));
      if ((UINT32) *(UINT32 *)pVariableData != (UINT32) *(UINT32 *)tempBuffer) {
        RecordOffset = (UINT32) *(UINT32*)(pVariableData + sizeof(UINT32));
        for(i = 32; i < RecordOffset; i++) {
          tempBuffer[i] = pVariableData[i];
        }
        for(i = 0; i < sizeof(CBS_CONFIG); i++) {
          pVariableData[i] = tempBuffer[i];
        }
      }
    }
  } else {
    DEBUG ((EFI_D_ERROR, "No CBS Variable, Force loading CBS variable default value.(OrgSize=0x%x, NewSize=0x%x)\n", BufferSize, sizeof(CBS_CONFIG)));
    CbsWriteDefalutValue(pVariableData);
  }
}

EFI_STATUS
CbsHookFunc (
  IN       EFI_BOOT_SERVICES    *BootServices,
  IN OUT   VOID                 *AMD_PARAMS,
  IN       UINTN                IdsHookId
  )
{
  DXE_CBS_COMPONENT_STRUCT   *pCbsFunctionTable;
  DXE_CBS_FUNCTION_STRUCT    *pCurTable;
  CPUID_DATA                 CpuId;
  UINT64                     SocFamilyID;

  AsmCpuid (
      0x80000001,
      &(CpuId.EAX_Reg),
      &(CpuId.EBX_Reg),
      &(CpuId.ECX_Reg),
      &(CpuId.EDX_Reg)
      );
  SocFamilyID = CpuId.EAX_Reg & RAW_FAMILY_ID_MASK;

  pCbsFunctionTable = &CbsCommonFuncTable[0];
  while (pCbsFunctionTable->pFuncTable != NULL) {
    if ((pCbsFunctionTable->Family == SocFamilyID) || (pCbsFunctionTable->Family == 0xFFFFFFFF)) {
      // Dispatch CBS function in DXE_CBS_FUNCTION_STRUCT.
      pCurTable = pCbsFunctionTable->pFuncTable;
      while (pCurTable->CBSFuncPtr != NULL) {
        if ((pCurTable->IdsHookId == IdsHookId) &&
          ((pCurTable->Family == SocFamilyID) || (pCurTable->Family == 0xFFFFFFFF))) {
          pCurTable->CBSFuncPtr(BootServices,AMD_PARAMS,pCbsConfig);
        }
        pCurTable++;
      }
    }
    pCbsFunctionTable++;
  }
  return EFI_SUCCESS;
}

EFI_STATUS CbsInitEntry(
  IN  EFI_BOOT_SERVICES *BootServices
  )
{
  EFI_STATUS   Status;
  EFI_HANDLE   Handle;

  pCbsConfig = AllocateZeroPool (sizeof(CBS_CONFIG));
  if (pCbsConfig == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  CbsVariableLoadDefault ((UINT8*)pCbsConfig);

  Handle = NULL;
  Status = BootServices->InstallProtocolInterface ( &Handle,
                                        &gCbsProtocolGuid,
                                        EFI_NATIVE_INTERFACE,
                                        &mCbsProtocolInstance);
  return Status;
}

EFI_STATUS
CbsInterfaceFunc (
  IN  EFI_BOOT_SERVICES      *BootServices,
  IN  OUT VOID               *AMD_PARAMS,
  IN      UINTN              IdsHookId
  )
{
  EFI_STATUS                Status;
  CBS_DXE_PROTOCOL          *pCbsProtocol;

  Status = BootServices->LocateProtocol (&gCbsProtocolGuid, NULL, &pCbsProtocol);
  if (!EFI_ERROR(Status)) {
    Status = pCbsProtocol->CbsHookInterface(BootServices, AMD_PARAMS, IdsHookId);
  }
  return Status;
}

