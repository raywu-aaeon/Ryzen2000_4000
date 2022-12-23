/*****************************************************************************
 *
 * Copyright 2012 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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
 ******************************************************************************
 */

#include <AmdCpmSmm.h>
#include <AmdCpmBaseIo.h>
#include <AmdCpmCpu.h>
#include <AmdCpmFch.h>
#include <AmdCpmTable.h>

CPM_DEFINE_gBS;
CPM_DEFINE_gSmst;

VOID
EFIAPI
AmdCpmSmmRegisterKernel (
  IN       VOID                    *This
  );


/*----------------------------------------------------------------------------------------*/
/**
 * Entry point of the AMD CPM Init SMM driver
 *
 * This function installs AmdCpmTableSmmProtocol and registers CPM common functions
 * at AmdCpmInitSmm.
 *
 * @param[in]     ImageHandle    Pointer to the firmware file system header
 * @param[in]     SystemTable    Pointer to System table
 *
 * @retval        EFI_SUCCESS    Module initialized successfully
 * @retval        EFI_ERROR      Initialization failed (see error for more details)
 */
EFI_STATUS
AmdCpmInitSmmEntryPoint (
  IN       EFI_HANDLE              ImageHandle,
  IN       EFI_SYSTEM_TABLE        *SystemTable
  )
{
  EFI_STATUS                      Status;
  EFI_HANDLE                      Handle;

  AMD_CPM_TABLE_PROTOCOL          *CpmTableProtocolPtr;
  AMD_CPM_TABLE_PROTOCOL          *CpmTableSmmProtocolPtr;

  If_CpmInSmm (ImageHandle, SystemTable, gBS, gSmst, Status) {

    DEBUG((DEBUG_INFO, "FEA-SMM-%a-Start\n", __FUNCTION__));
    //
    // Initialize global variables
    //
    DEBUG((DEBUG_INFO, "FEA-SMM-%a-SmmAllocatePool-CpmTableSmmProtocolPtr\n", __FUNCTION__));
    Status = gSmst->SmmAllocatePool (
                    EfiRuntimeServicesData,
                    sizeof (AMD_CPM_TABLE_PROTOCOL),
                    (VOID**)&CpmTableSmmProtocolPtr
                    );
    if (EFI_ERROR (Status)) {
      DEBUG((DEBUG_INFO, "FEA-SMM-%a-End-1-SmmAllocatePool-FAIL\n", __FUNCTION__));
      return Status;
    }

    DEBUG((DEBUG_INFO, "FEA-SMM-%a-LocateProtocol-gAmdCpmTableProtocolGuid\n", __FUNCTION__));
    Status = gBS->LocateProtocol (
                    &gAmdCpmTableProtocolGuid,
                    NULL,
                    (VOID**)&CpmTableProtocolPtr
                    );
    if (EFI_ERROR (Status)) {
      DEBUG((DEBUG_INFO, "FEA-SMM-%a-End-2-LocateProtocol-FAIL\n", __FUNCTION__));
      return Status;
    }

    CpmTableSmmProtocolPtr->Revision      = CpmTableProtocolPtr->Revision;
    CpmTableSmmProtocolPtr->MainTablePtr  = CpmTableProtocolPtr->MainTablePtr;

    DEBUG((DEBUG_INFO, "FEA-SMM-%a-AmdCpmSmmRegisterKernel\n", __FUNCTION__));
    AmdCpmSmmRegisterKernel (CpmTableSmmProtocolPtr);
    DEBUG((DEBUG_INFO, "FEA-SMM-%a-CpmRegisterBaseIo\n", __FUNCTION__));
    CpmRegisterBaseIo (CpmTableSmmProtocolPtr);
    DEBUG((DEBUG_INFO, "FEA-SMM-%a-CpmRegisterCpu\n", __FUNCTION__));
    CpmRegisterCpu (CpmTableSmmProtocolPtr);
    DEBUG((DEBUG_INFO, "FEA-SMM-%a-CpmRegisterFch\n", __FUNCTION__));
    CpmRegisterFch (CpmTableSmmProtocolPtr);

    Handle = NULL;
    DEBUG((DEBUG_INFO, "FEA-SMM-%a-InstallProtocolInterface-gAmdCpmTableSmmProtocolGuid\n", __FUNCTION__));
    Status = gBS->InstallProtocolInterface (
                    &Handle,
                    &gAmdCpmTableSmmProtocolGuid,
                    EFI_NATIVE_INTERFACE,
                    CpmTableSmmProtocolPtr
                    );
    DEBUG((DEBUG_INFO, "FEA-SMM-%a-End-3-Status=%r\n", __FUNCTION__, Status));
  }

  RECORD_TIME_DXE (EndAmdCpmInitSmmDriver);

  return Status;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Register Common Kenerl functions at the AmdCpmInitSmm entry point.
 *
 * This function registers CPM common kernel functions in AmdCpmTableSmmProtocol
 * at AmdCpmInitSmm.
 *
 *  @param[in]   This                Pointer to Protocol.
 *
 */
VOID
EFIAPI
AmdCpmSmmRegisterKernel (
  IN       VOID                    *This
  )
{
  AMD_CPM_TABLE_PROTOCOL  *CpmTableSmmProtocolPtr         = This;
  DEBUG((DEBUG_INFO, "KER-SMM-%a-Start\n", __FUNCTION__));
  CpmTableSmmProtocolPtr->CommonFunction.GetTablePtr      = CpmGetTablePtr;
  CpmTableSmmProtocolPtr->CommonFunction.GetTablePtr2     = CpmGetTablePtr2;
  CpmTableSmmProtocolPtr->CommonFunction.RelocateTable    = CpmRelocateTableList;
  CpmTableSmmProtocolPtr->CommonFunction.CopyMem          = CpmCopyMem;
  CpmTableSmmProtocolPtr->CommonFunction.ReadSmbus        = NULL;
  CpmTableSmmProtocolPtr->CommonFunction.WriteSmbus       = NULL;
  CpmTableSmmProtocolPtr->CommonFunction.ReadSmbusBlock   = NULL;
  CpmTableSmmProtocolPtr->CommonFunction.WriteSmbusBlock  = NULL;
  DEBUG((DEBUG_INFO, "KER-SMM-%a-End\n", __FUNCTION__));
  return;
}
