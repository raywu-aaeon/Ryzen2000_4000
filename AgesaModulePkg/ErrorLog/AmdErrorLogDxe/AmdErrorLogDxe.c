/*
****************************************************************************
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


#include <Filecode.h>
#include <Library/HobLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/AmdErrorLogLib.h>
#include <Protocol/AmdErrorLogProtocol.h>
#include <Protocol/AmdErrorLogServiceProtocol.h>
#include "AmdErrorLogDxe.h"

#define FILECODE ERRORLOG_AMDERRORLOGDXE_AMDERRORLOGDXE_FILECODE

DXE_AMD_ERROR_LOG_SERVICES_PROTOCOL mDxeAmdErrorLogServicesProtocol = {
  AMD_ERROR_LOG_SERVICE_PROTOCOL_REVISION,
  AmdAquireErrorLogDxe,
};

DXE_AMD_ERROR_LOG_PROTOCOL mDxeAmdErrorLogProtocol = {
  AMD_ERROR_LOG_PROTOCOL_REVISION,
  AmdErrorLogDxe,
  AmdErrorLogIpCompleteDxe,
};

extern  EFI_BOOT_SERVICES       *gBS;

//
// Driver Global Data
//
STATIC AMD_ERROR_BUFFER *ErrorLogBuffer;


/*---------------------------------------------------------------------------------------*/
/**
 *
 * This function logs AGESA errors into the Error log.
 *
 * It will put the information in a circular buffer consisting of 128 such log
 * entries. If the buffer gets full, then the next Error log entry will be written
 * over the oldest Error log entry.
 *
 * @param[in]   This         Error log service instance.
 * @param[in]   ErrorClass   The severity of the Erorr, its associated AGESA_STATUS.
 * @param[in]   ErrorInfo    Uniquely identifies the error.
 * @param[in]   DataParam1   Error specific additional data
 * @param[in]   DataParam2   Error specific additional data
 * @param[in]   DataParam3   Error specific additional data
 * @param[in]   DataParam4   Error specific additional data
 *
 */
EFI_STATUS
EFIAPI
AmdErrorLogDxe (
  IN  DXE_AMD_ERROR_LOG_PROTOCOL   *This,
  IN  AMD_STATUS ErrorClass,
  IN  UINT32 ErrorInfo,
  IN  UINT32 DataParam1,
  IN  UINT32 DataParam2,
  IN  UINT32 DataParam3,
  IN  UINT32 DataParam4
  )
{
  EFI_STATUS       Status = EFI_SUCCESS;
  EFI_HANDLE       Handle;
  AMD_ERROR_ENTRY  AmdErrorEntry;

  Handle = NULL;

  AmdErrorEntry.ErrorClass = ErrorClass;
  AmdErrorEntry.ErrorInfo  = ErrorInfo;
  AmdErrorEntry.DataParam1 = DataParam1;
  AmdErrorEntry.DataParam2 = DataParam2;
  AmdErrorEntry.DataParam3 = DataParam3;
  AmdErrorEntry.DataParam4 = DataParam4;

  AddErrorLog (ErrorLogBuffer, &AmdErrorEntry);

  if (ErrorLogBuffer->Count == TOTAL_ERROR_LOG_BUFFERS) {
    // Publish Error Log Full Protocol
    Status = gBS->InstallProtocolInterface (
              &Handle,
              &gAmdErrorLogFullProtocolGuid,
              EFI_NATIVE_INTERFACE,
              NULL
              );
  }

  return Status;
}

EFI_STATUS
EFIAPI
AmdErrorLogIpCompleteDxe (
  IN       DXE_AMD_ERROR_LOG_PROTOCOL   *This,
  IN CONST EFI_GUID                     *SiliconDriverId
  )
{
  EFI_STATUS    Status = EFI_SUCCESS;
  EFI_HANDLE    Handle;

  Handle = NULL;

  // check here if all IP drivers complete before publish Error Log Available Protocol

  // Publish Error Log Available Protocol
  Status = gBS->InstallProtocolInterface (
            &Handle,
            &gAmdErrorLogAvailableProtocolGuid,
            EFI_NATIVE_INTERFACE,
            NULL
            );

  return Status;
}

/*---------------------------------------------------------------------------------------*/
/**
 *
 * This function logs AGESA Errors into the Error log.
 *
 * It will put the information in a circular buffer consisting of 128 such log
 * entries. If the buffer gets full, then the next Error log entry will be written
 * over the oldest Error log entry.
 *
 * @param[in]   PeiServices
 * @param[out]  ErrorLogDataPtr
 *
 */
EFI_STATUS
EFIAPI
AmdAquireErrorLogDxe (
  IN       DXE_AMD_ERROR_LOG_SERVICES_PROTOCOL   *This,
  OUT      ERROR_LOG_DATA_STRUCT *ErrorLogDataPtr
  )
{
  EFI_STATUS    Status = EFI_SUCCESS;

  AquireErrorLog (ErrorLogBuffer, ErrorLogDataPtr);

  return Status;
}

/*********************************************************************************
 * Name: AmdErrorLogDxeInit
 *
 * Description
 *   Entry point of the AMD Error Log DXE driver
 *   Perform the configuration init, resource reservation, early post init
 *   and install all the supported protocol
 *
 * Input
 *   ImageHandle : EFI Image Handle for the DXE driver
 *   SystemTable : pointer to the EFI system table
 *
 * Output
 *   EFI_SUCCESS : Module initialized successfully
 *   EFI_ERROR   : Initialization failed (see error for more details)
 *
 *********************************************************************************/
EFI_STATUS
EFIAPI
AmdErrorLogDxeInit (
  IN       EFI_HANDLE         ImageHandle,
  IN       EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS          Status = EFI_SUCCESS;
  EFI_HANDLE          Handle;
  AMD_ERROR_LOG_INFO_HOB *ErrorLogHob;

  DEBUG ((EFI_D_ERROR, "*****************************DXE Error Log Driver Entry*********************\n"));

  //
  // Initialize the configuration structure and private data area
  //

  //Get Error Log buffer from HOB
  ErrorLogHob = GetFirstGuidHob (&gErrorLogHobGuid);
  ErrorLogBuffer = &(ErrorLogHob->AmdErrorBuffer);

  Handle = ImageHandle;

  // Publish Error Log service Protocol For IP driver
  Status = gBS->InstallProtocolInterface (
                &Handle,
                &gAmdErrorLogProtocolGuid,
                EFI_NATIVE_INTERFACE,
                &mDxeAmdErrorLogProtocol
                );

  // Publish Error Log service Protocol for platform BIOS
  Status = gBS->InstallProtocolInterface (
                &Handle,
                &gAmdErrorLogServiceProtocolGuid,
                EFI_NATIVE_INTERFACE,
                &mDxeAmdErrorLogServicesProtocol
                );

  // Publish Error Log Ready Protocol
  Status = gBS->InstallProtocolInterface (
                  &Handle,
                  &gAmdErrorLogReadyProtocolGuid,
                  EFI_NATIVE_INTERFACE,
                  NULL
                  );

  DEBUG ((EFI_D_ERROR, "*****************************DXE Error Log Driver Exit*********************\n"));

  return (Status);
}


