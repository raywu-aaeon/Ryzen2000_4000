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

#ifndef _AMD_ERROR_LOG_PEI_H_
#define _AMD_ERROR_LOG_PEI_H_

//Publich AGESA interface
typedef struct _ERROR_LOG_SERVICE_PPI_PRIVATE
{
    PEI_AMD_ERROR_LOG_SERVICE_PPI    AmdErrorLogServicePpi;  ///< Pointer to Error Log Service Ppi
    EFI_PEI_SERVICES                 **PeiServices;          ///< Pointer to PeiServices
    AMD_ERROR_BUFFER                 *ErrorLogBuffer;        ///< Pointer to Internal error log buffer
} ERROR_LOG_SERVICE_PPI_PRIVATE;

//AGESA private interface 
typedef struct _ERROR_LOG_PPI_PRIVATE
{
    PEI_AMD_ERROR_LOG_PPI            AmdErrorLogPpi;         ///< Pointer to Error Log Ppi
    EFI_PEI_SERVICES                 **PeiServices;          ///< Pointer to PeiServices
    AMD_ERROR_BUFFER                 *ErrorLogBuffer;        ///< Pointer to Internal error log buffer
} ERROR_LOG_PPI_PRIVATE;

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
  );

EFI_STATUS
EFIAPI
AmdErrorLogIpCompletePei (
  IN       PEI_AMD_ERROR_LOG_PPI   *This,
  IN CONST EFI_GUID            *SiliconDriverId
  );

EFI_STATUS
EFIAPI
AmdAquireErrorLogPei (
  IN       PEI_AMD_ERROR_LOG_SERVICE_PPI   *This,
  OUT      ERROR_LOG_DATA_STRUCT *ErrorLogDataPtr
  );

extern EFI_GUID gErrorLogHobGuid;

#endif // _AMD_SOC_AM4_PEI_H_


