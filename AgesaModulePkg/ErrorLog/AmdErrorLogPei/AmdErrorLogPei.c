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
/*++
Module Name:

  AmdErrorLogPei.c
  Init Soc interface

Abstract:
--*/

#include <Filecode.h>
#include <PiPei.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/AmdErrorLogLib.h>
#include <Ppi/AmdErrorLogServicePpi.h>
#include <Ppi/AmdErrorLogPpi.h>
#include "AmdErrorLogPei.h"

#define FILECODE ERRORLOG_AMDERRORLOGPEI_AMDERRORLOGPEI_FILECODE

STATIC PEI_AMD_ERROR_LOG_READY_PPI mAmdErrorLogReadyPpi = {
  AMD_ERROR_LOG_PPI_REVISION,
};

STATIC EFI_PEI_PPI_DESCRIPTOR mErrorLogReadyPpiList = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gAmdErrorLogReadyPpiGuid,
  &mAmdErrorLogReadyPpi
};

STATIC PEI_AMD_ERROR_LOG_FULL_PPI mAmdErrorLogFullPpi = {
  AMD_ERROR_LOG_PPI_REVISION,
};

STATIC EFI_PEI_PPI_DESCRIPTOR mErrorLogFullPpiList = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gAmdErrorLogFullPpiGuid,
  &mAmdErrorLogFullPpi
};

STATIC PEI_AMD_ERROR_LOG_FULL_PPI mAmdErrorLogAvailablePpi = {
  AMD_ERROR_LOG_PPI_REVISION,
};

STATIC EFI_PEI_PPI_DESCRIPTOR mErrorLogAvailablePpiList = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gAmdErrorLogAvailablePpiGuid,
  &mAmdErrorLogAvailablePpi
};

/*---------------------------------------------------------------------------------------*/
/**
 *
 * This function logs AGESA Errors into the Error log.
 *
 * It will put the information in a circular buffer consisting of 16 such log
 * entries. If the buffer gets full, then the next Error log entry will be written
 * over the oldest Error log entry.
 *
 * @param[in]   PeiServices
 * @param[in]   ErrorClass   The severity of the Error, its associated AGESA_STATUS.
 * @param[in]   ErrorInfo    Uniquely identifies the Error.
 * @param[in]   DataParam1   Error specific additional data
 * @param[in]   DataParam2   Error specific additional data
 * @param[in]   DataParam3   Error specific additional data
 * @param[in]   DataParam4   Error specific additional data
 *
 */
EFI_STATUS
EFIAPI
AmdErrorLogPei (
  IN       PEI_AMD_ERROR_LOG_PPI   *This,
  IN       AMD_STATUS ErrorClass,
  IN       UINT32 ErrorInfo,
  IN       UINT32 DataParam1,
  IN       UINT32 DataParam2,
  IN       UINT32 DataParam3,
  IN       UINT32 DataParam4
  )
{
  EFI_STATUS    Status = EFI_SUCCESS;
  AMD_ERROR_ENTRY  AmdErrorEntry;
  ERROR_LOG_PPI_PRIVATE *Private;
  Private = (ERROR_LOG_PPI_PRIVATE*)This;

  AmdErrorEntry.ErrorClass = ErrorClass;
  AmdErrorEntry.ErrorInfo  = ErrorInfo;
  AmdErrorEntry.DataParam1 = DataParam1;
  AmdErrorEntry.DataParam2 = DataParam2;
  AmdErrorEntry.DataParam3 = DataParam3;
  AmdErrorEntry.DataParam4 = DataParam4;

  AddErrorLog (Private->ErrorLogBuffer, &AmdErrorEntry);
  
  if ((Private->ErrorLogBuffer)->Count == TOTAL_ERROR_LOG_BUFFERS) {
    // Publish Error Log Full Ppi
    Status = (*Private->PeiServices)->InstallPpi (
                                      Private->PeiServices,
                                      &mErrorLogFullPpiList
                                      );
    ASSERT_EFI_ERROR (Status);
  }
  return Status;
}

/*---------------------------------------------------------------------------------------*/
/**
 *
 * This function logs AGESA Errors into the Error log.
 *
 * It will put the information in a circular buffer consisting of 16 such log
 * entries. If the buffer gets full, then the next Error log entry will be written
 * over the oldest Error log entry.
 *
 * @param[in]   PeiServices
 * @param[in]   SiliconDriverId
 *
 */
EFI_STATUS
EFIAPI
AmdErrorLogIpCompletePei (
  IN       PEI_AMD_ERROR_LOG_PPI   *This,
  IN CONST EFI_GUID                *SiliconDriverId
  )
{
  EFI_STATUS    Status = EFI_SUCCESS;
  ERROR_LOG_PPI_PRIVATE *Private;
  Private = (ERROR_LOG_PPI_PRIVATE*)This;

  // check here if all IP drivers complete before publish Error Log Available Ppi

  // Publish Error Log Available Ppi
  Status = (*Private->PeiServices)->InstallPpi (
                                    Private->PeiServices,
                                    &mErrorLogAvailablePpiList
                                    );
  ASSERT_EFI_ERROR (Status);

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
AmdAquireErrorLogPei (
  IN       PEI_AMD_ERROR_LOG_SERVICE_PPI   *This,
  OUT      ERROR_LOG_DATA_STRUCT *ErrorLogDataPtr
  )
{
  EFI_STATUS    Status = EFI_SUCCESS;
  ERROR_LOG_SERVICE_PPI_PRIVATE *Private;
  Private = (ERROR_LOG_SERVICE_PPI_PRIVATE*)This;

  AquireErrorLog (Private->ErrorLogBuffer, ErrorLogDataPtr);
  //Reset Error Log buffer
  ErrorLogBufferInit (Private->ErrorLogBuffer);

  return Status;
}

/*++

Routine Description:

  Error Log Driver Entry. Initialize and publish Error Log and PPI

Arguments:

Returns:

  EFI_STATUS

--*/
EFI_STATUS
EFIAPI
PeiAmdErrorInit (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
  AMD_ERROR_LOG_INFO_HOB *ErrorLogHob;
  EFI_STATUS    Status = EFI_SUCCESS;
  ERROR_LOG_PPI_PRIVATE  *EventlogPrivate;
  ERROR_LOG_SERVICE_PPI_PRIVATE  *EventlogServicePrivate;
  AMD_ERROR_BUFFER *ErrorLogBuffer;
  EFI_PEI_PPI_DESCRIPTOR    *mErrorLogPpiList;
  EFI_PEI_PPI_DESCRIPTOR    *mErrorLogServicePpiList;

  DEBUG ((EFI_D_ERROR, "*****************************PEI Error Log Driver Entry*********************\n"));

  // Create Error Log GUID HOB to save Error Log buffer data
  Status = (*PeiServices)->CreateHob (
                             PeiServices,
                             EFI_HOB_TYPE_GUID_EXTENSION,
                             sizeof (AMD_ERROR_LOG_INFO_HOB),
                             &ErrorLogHob
                             );

  ASSERT_EFI_ERROR (Status);

  CopyMem (&ErrorLogHob->EfiHobGuidType.Name, &gErrorLogHobGuid, sizeof (EFI_GUID));
  ErrorLogBuffer = &(ErrorLogHob->AmdErrorBuffer);

  ErrorLogBufferInit (ErrorLogBuffer);


  // Publish Error Log Ppi for IP driver
  Status = (*PeiServices)->AllocatePool (
                             PeiServices,
                             sizeof (ERROR_LOG_PPI_PRIVATE),
                             &EventlogPrivate
                             );
  ASSERT_EFI_ERROR (Status);

  EventlogPrivate->AmdErrorLogPpi.AmdErrorLogPei           = AmdErrorLogPei;
  EventlogPrivate->AmdErrorLogPpi.AmdErrorLogIpCompletePei = AmdErrorLogIpCompletePei;
  EventlogPrivate->PeiServices                             = (EFI_PEI_SERVICES **)PeiServices;
  EventlogPrivate->ErrorLogBuffer                          = ErrorLogBuffer;

  // Allocate memory for the PPI descriptor
  Status = (*PeiServices)->AllocatePool (
                             PeiServices,
                             sizeof (EFI_PEI_PPI_DESCRIPTOR),
                             (VOID **)&mErrorLogPpiList
                             );
  ASSERT_EFI_ERROR ( Status);

  mErrorLogPpiList->Flags = (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST);
  mErrorLogPpiList->Guid  = &gAmdErrorLogPpiGuid;
  mErrorLogPpiList->Ppi   = &(EventlogPrivate->AmdErrorLogPpi);

  Status = (*PeiServices)->InstallPpi (
                               PeiServices,
                               mErrorLogPpiList
                               );
  ASSERT_EFI_ERROR (Status);



  // Publish Error Log Service Ppi for Platform BIOS
  Status = (*PeiServices)->AllocatePool (
                             PeiServices,
                             sizeof (ERROR_LOG_SERVICE_PPI_PRIVATE),
                             &EventlogServicePrivate
                             );
  ASSERT_EFI_ERROR (Status);

  EventlogServicePrivate->AmdErrorLogServicePpi.AmdAquireErrorLogPei = AmdAquireErrorLogPei;
  EventlogServicePrivate->PeiServices                                = (EFI_PEI_SERVICES **)PeiServices;
  EventlogServicePrivate->ErrorLogBuffer                             = ErrorLogBuffer;

  // Allocate memory for the PPI descriptor
  Status = (*PeiServices)->AllocatePool (
                             PeiServices,
                             sizeof (EFI_PEI_PPI_DESCRIPTOR),
                             (VOID **)&mErrorLogServicePpiList
                             );
  ASSERT_EFI_ERROR ( Status);

  mErrorLogServicePpiList->Flags = (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST);
  mErrorLogServicePpiList->Guid  = &gAmdErrorLogServicePpiGuid;
  mErrorLogServicePpiList->Ppi   = &(EventlogServicePrivate->AmdErrorLogServicePpi);

  Status = (*PeiServices)->InstallPpi (
                               PeiServices,
                               mErrorLogServicePpiList
                               );
  ASSERT_EFI_ERROR (Status);

  // Publish Error Log Ready Ppi
  Status = (*PeiServices)->InstallPpi (
                               PeiServices,
                               &mErrorLogReadyPpiList
                               );
  ASSERT_EFI_ERROR (Status);

  DEBUG ((EFI_D_ERROR, "*****************************PEI Error Driver Exit*********************\n"));
  return (Status);
}


