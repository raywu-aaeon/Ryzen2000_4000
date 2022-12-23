/* $NoKeywords:$ */
/**
 * @file
 *
 * Fabric NUMA Services Protocol prototype definition
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Library
 * @e \$Revision$   @e \$Date$
 */
/*****************************************************************************
 *
 * Copyright 2017 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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
#ifndef _FABRIC_NUMA_SERVICES_PROTOCOL_H_
#define _FABRIC_NUMA_SERVICES_PROTOCOL_H_

#pragma pack (push, 1)

/*----------------------------------------------------------------------------------------
 *                    T Y P E D E F S     A N D     S T R U C T U R E S
 *----------------------------------------------------------------------------------------
 */
 /// Domain type
typedef enum {
  SocketIntlv,
  DieIntlv,
  NoIntlv,
  MaxDomainType
} DOMAIN_TYPE;

/// Socket interleave domain
typedef struct {
  UINT32   SocketCount;   ///< Socket Count
  UINT32   SocketMap;     ///< Socket Map
} SOCKET_INTLV_DOMAIN;

/// Die interleave domain
typedef struct {
  UINT32   DieCount;      ///< Die Count
  UINT32   DieMap;        ///< Die Map
} DIE_INTLV_DOMAIN;

/// No interleave domain
typedef struct {
  UINT32   Socket;        ///< Socket
  UINT32   Die;           ///< Die
} NO_INTLV_DOMAIN;

/// Domain Info
typedef struct {
  DOMAIN_TYPE  Type;              ///< Type
  union {                         ///< Interleave
    SOCKET_INTLV_DOMAIN  Socket;  ///< Socket
    DIE_INTLV_DOMAIN     Die;     ///< Die
    NO_INTLV_DOMAIN      None;    ///< None
  } Intlv;
} DOMAIN_INFO;

/*----------------------------------------------------------------------------------------
 *                 D E F I N I T I O N S     A N D     M A C R O S
 *----------------------------------------------------------------------------------------
 */

///
/// Forward declaration for the FABRIC_NUMA_SERVICES_PROTOCOL
///
typedef struct _FABRIC_NUMA_SERVICES_PROTOCOL FABRIC_NUMA_SERVICES_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI *FABRIC_NUMA_SERVICES_GET_DOMAIN_INFO) (
  IN       FABRIC_NUMA_SERVICES_PROTOCOL  *This,
     OUT   UINT32                         *NumberOfDomainsInSystem,
     OUT   DOMAIN_INFO                   **DomainInfo
  );

typedef
EFI_STATUS
(EFIAPI *FABRIC_NUMA_SERVICES_DOMAIN_XLAT) (
  IN       FABRIC_NUMA_SERVICES_PROTOCOL  *This,
  IN       UINTN                           Socket,
  IN       UINTN                           Die,
     OUT   UINT32                         *Domain
  );

typedef
UINT8
(EFIAPI *FABRIC_NUMA_SERVICES_GET_MAX_DOMAINS) (
  IN       FABRIC_NUMA_SERVICES_PROTOCOL  *This
  );

///
/// When installed, the Fabric NUMA Services Protocol produces a collection of
/// services that return various information associated with non-uniform memory
/// architecture.
///
struct _FABRIC_NUMA_SERVICES_PROTOCOL {
  UINTN                                     Revision;       ///< Revision Number
  FABRIC_NUMA_SERVICES_GET_DOMAIN_INFO      GetDomainInfo;  ///< Get Domain Info
  FABRIC_NUMA_SERVICES_DOMAIN_XLAT          DomainXlat;     ///< Domain Translation
  FABRIC_NUMA_SERVICES_GET_MAX_DOMAINS      GetMaxDomains;  ///< Get maximum proximity domain
};

extern EFI_GUID gAmdFabricNumaServicesProtocolGuid;

#pragma pack (pop)
#endif // _FABRIC_NUMA_SERVICES_PROTOCOL_H_

