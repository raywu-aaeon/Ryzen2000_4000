/*****************************************************************************
 *
 * Copyright 2016 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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
#ifndef _SOC_LOGICAL_ID_PROTOCOL_H_
#define _SOC_LOGICAL_ID_PROTOCOL_H_

//----------------------------------------------------
//
//  SOC Logical ID Service Functions
//
//-------------------------------------------------------

#include <SocLogicalId.h>

///
/// Forward declaration for the AMD_SOC_LOGICAL_ID_PROTOCOL.
///
typedef struct _AMD_SOC_LOGICAL_ID_PROTOCOL AMD_SOC_LOGICAL_ID_PROTOCOL;

/*---------------------------------------------------------------------------------------*/
/**
 * This service retrieves the logical family and revision for the executing core.
 *
 * @param[in]  This                           A pointer to the AMD_SOC_LOGICAL_ID_PROTOCOL instance.
 * @param[out] LogicalId                      Pointer to the logical ID for the executing core.
 *
 * @retval EFI_SUCCESS                        The executing core's logical ID was successfully retrieved.
 * @retval EFI_INVALID_PARAMETER              All output parameter pointers are NULL.
 * @retval EFI_DEVICE_ERROR                   Unknown processor family found.
 *
 **/
typedef
EFI_STATUS
(EFIAPI *AMD_SOC_LOGICAL_ID_GET_LOGICAL_ID_ON_CURRENT_CORE) (
     IN    AMD_SOC_LOGICAL_ID_PROTOCOL                     *This,
     OUT   SOC_LOGICAL_ID                                  *LogicalId
  );

/*---------------------------------------------------------------------------------------*/
/**
 * This service retrieves the logical family and revision for a particular processor.
 *
 * If no processor is installed in Socket, then EFI_INVALID_PARAMETER is returned.
 *
 * @param[in]  This                           A pointer to the AMD_SOC_LOGICAL_ID_PROTOCOL instance.
 * @param[in]  Socket                         Zero-based socket number to check.
 * @param[out] LogicalId                      Pointer to the logical ID for the given socket.
 *
 * @retval EFI_SUCCESS                        The given socket's logical ID was retrieved successfully.
 * @retval EFI_INVALID_PARAMETER              Socket is non-existent.
 * @retval EFI_INVALID_PARAMETER              All output parameter pointers are NULL.
 * @retval EFI_DEVICE_ERROR                   Unknown processor family found.
 *
 **/
typedef
EFI_STATUS
(EFIAPI *AMD_SOC_LOGICAL_ID_GET_LOGICAL_ID_ON_GIVEN_SOCKET) (
     IN    AMD_SOC_LOGICAL_ID_PROTOCOL                     *This,
     IN    UINTN                                           Socket,
     OUT   SOC_LOGICAL_ID                                  *LogicalId
  );

///
/// When installed, the SoC Logical ID protocol produces a collection
/// of services that provide the logical ID translation for installed
/// processors.
///
typedef struct _AMD_SOC_LOGICAL_ID_PROTOCOL {
  UINTN                                               Revision;                   ///< Revision Number
  AMD_SOC_LOGICAL_ID_GET_LOGICAL_ID_ON_CURRENT_CORE   GetLogicalIdOnCurrentCore;  ///< Get logical revision of the executing core
  AMD_SOC_LOGICAL_ID_GET_LOGICAL_ID_ON_GIVEN_SOCKET   GetLogicalIdOnGivenSocket;  ///< Get logical revision of the given socket
} AMD_SOC_LOGICAL_ID_PROTOCOL;

extern EFI_GUID gAmdSocLogicalIdProtocolGuid;

// Current protocol revision
#define SOC_LOGICAL_ID_PROTOCOL_REVISION   0x00

#endif

