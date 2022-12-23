/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD Memory API, and related functions.
 *
 * Contains code that initializes memory
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Mem
 * @e \$Revision:  $   @e \$Date:  $
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
 */
#ifndef _AMD_MEM_PPR_PROTOCOL_H_
#define _AMD_MEM_PPR_PROTOCOL_H_

#include <PiDxe.h>
#include <Library/HobLib.h>
#include <Library/UefiLib.h>
#include <Guid/HobList.h>

#define AMD_MEM_MAX_SOCKETS_SUPPORTED   2  ///< Max number of sockets in system
#define AMD_MEM_MAX_DIES_PER_SOCKET     4   ///< Max dies per socket
#define AMD_MEM_MAX_CHANNELS_PER_SOCKET 8   ///< Max Channels per sockets
#define AMD_MEM_MAX_CHANNELS_PER_DIE    2   ///< Max channels per die
#define AMD_MEM_MAX_DIMMS_PER_CHANNEL   2   ///< Max dimms per die

typedef struct _AMD_DIMM_INFO {
    UINT8  SocketId;
    UINT8  DieId;
    UINT8  ChannelId;
    UINT8  Chipselect;
} AMD_DIMM_INFO;

typedef struct _AMD_PPR_INFO {
    BOOLEAN IsValidRecord;
    BOOLEAN DpprSupported;
    BOOLEAN SpprSupported;
    UINT8   DeviceWidth;
    UINT32  SerialNumber;
} AMD_PPR_INFO;

//
// AMD_MEM_DIMM_SPD_DATA_STRUCT
//
typedef struct _AMD_MEM_PPR_DATA_TABLE {
  AMD_PPR_INFO    DimmSpdInfo[AMD_MEM_MAX_SOCKETS_SUPPORTED * AMD_MEM_MAX_CHANNELS_PER_SOCKET * AMD_MEM_MAX_DIMMS_PER_CHANNEL];
} AMD_MEM_PPR_DATA_TABLE;

//
// Forward declaration for the AMD_ACPI_CPU_SSDT_SERVICES_PROTOCOL.
//
typedef struct _AMD_POST_PACKAGE_REPAIR_INFO_PROTOCOL AMD_POST_PACKAGE_REPAIR_INFO_PROTOCOL;


typedef
EFI_STATUS
(EFIAPI *AMD_GET_PPR_INFO) (
  IN       AMD_POST_PACKAGE_REPAIR_INFO_PROTOCOL    *This,
  IN       AMD_DIMM_INFO                            *AmdDimmInfo,
     OUT   AMD_PPR_INFO                             *PprInfo
  );

//
// AMD Post Package Repair Protocol Info
//
struct _AMD_POST_PACKAGE_REPAIR_INFO_PROTOCOL {
  AMD_MEM_PPR_DATA_TABLE          AmdPprArray;
  AMD_GET_PPR_INFO                AmdGetPprInfo;
};

extern EFI_GUID  gAmdPostPackageRepairInfoProtocolGuid;

#endif
