/* $NoKeywords:$ */
/**
 * @file
 *
 * Base Fabric MMIO map manager Lib implementation for UNB
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Fabric
 * @e \$Revision$   @e \$Date$
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
#ifndef _FABRIC_RESOURCE_MANAGER_UNB_LIB_H_
#define _FABRIC_RESOURCE_MANAGER_UNB_LIB_H_

#include "Porting.h"
#include <Protocol/FabricResourceManagerServicesProtocol.h>

#pragma pack (push, 1)

/*---------------------------------------------------------------------------------------
 *                 D E F I N I T I O N S     A N D     M A C R O S
 *---------------------------------------------------------------------------------------
 */
#define MMIO_REG_PAIR_NUM     12

#define CONF_MAP_RANGE_0      0xE0
#define CONF_MAP_RANGE_1      0xE4
#define CONF_MAP_RANGE_2      0xE8
#define CONF_MAP_RANGE_3      0xEC
#define CONF_MAP_NUM          4

#define MMIO_ALIGN            0x10000l

/*---------------------------------------------------------------------------------------
 *               T Y P E D E F S,   S T R U C T U R E S,    E N U M S
 *---------------------------------------------------------------------------------------
 */

/// MMIO destination
typedef struct _FABRIC_MMIO_DST {
  UINT32   DstNode:3;           ///< Destination node ID bits
  UINT32   DstLink:2;           ///< Destination link ID
  UINT32   DstSubLink:1;        ///< Destination sublink
} MMIO_DST;

/// MMIO range
typedef struct _FABRIC_MMIO_RANGE {
  UINT64  Base;                 ///< Base
  UINT64  Limit;                ///< Limit
  FABRIC_MMIO_ATTRIBUTE Attribute; ///< Attribute
  MMIO_DST Destination;     ///< Destination
  UINT8   RangeNum;             ///< Range No.
  BOOLEAN Modified;             ///< if this MMIO base/limit registers need to be updated
} MMIO_RANGE;

/// MMIO base low
typedef struct {
  UINT32 RE:1;          ///< Read enable
  UINT32 WE:1;          ///< Write enable
  UINT32 CpuDis:1;      ///< CPU Disable
  UINT32 Lock:1;        ///< Lock
  UINT32 :4;            ///< Reserved
  UINT32 MmioBase:24;   ///< MMIO base address register bits[39:16]
} MMIO_BASE_LOW;

/// MMIO limit low
typedef struct {
  UINT32 DstNode:3;     ///< Destination node ID bits
  UINT32 :1;            ///< Reserved
  UINT32 DstLink:2;     ///< Destination link ID
  UINT32 DstSubLink:1;  ///< Destination sublink
  UINT32 NP:1;          ///< Non-posted
  UINT32 MmioLimit:24;  ///< MMIO limit address register bits[39:16]
} MMIO_LIMIT_LOW;

/// MMIO base/limit high
typedef struct {
  UINT32 MmioBase:8;    ///< MMIO base address register bits[47:40]
  UINT32 :8;            ///< Reserved
  UINT32 MmioLimit:8;   ///< MMIO limit address register bits[47:40]
  UINT32 :8;            ///< Reserved
} MMIO_BASE_LIMIT_HI;

/// Configuration map
typedef struct {
  UINT32 RE:1;          ///< Read enable
  UINT32 WE:1;          ///< Write enable
  UINT32 DevCmpEn:1;    ///< Device number compare mode enable
  UINT32 :1;            ///< Reserved
  UINT32 DstNode:3;     ///< Destination node ID bits
  UINT32 :1;            ///< Reserved
  UINT32 DstLink:2;     ///< Destination link ID
  UINT32 DstSubLink:1;  ///< Destination sublink
  UINT32 :5;            ///< Reserved
  UINT32 BusNumBase:8;  ///< Bus number base bits
  UINT32 BusNumLimit:8; ///< Bus number limit bits
} CONFIGURATION_MAP;

#pragma pack (pop)
#endif // _FABRIC_RESOURCE_MANAGER_UNB_LIB_H_
