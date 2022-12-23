/* $NoKeywords:$ */
/**
 * @file
 *
 * Fabric MMIO map manager Protocol prototype definition
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Fabric
 * @e \$Revision$   @e \$Date$
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
 **/

#ifndef _FABRIC_RESOURCE_MANAGER_SERVICES_PROTOCOL_H_
#define _FABRIC_RESOURCE_MANAGER_SERVICES_PROTOCOL_H_
#include <FabricResourceManagerCmn.h>

#pragma pack (push, 1)

/*---------------------------------------------------------------------------------------
 *                 D E F I N I T I O N S     A N D     M A C R O S
 *---------------------------------------------------------------------------------------
 */

/*---------------------------------------------------------------------------------------
 *               T Y P E D E F S,   S T R U C T U R E S,    E N U M S
 *---------------------------------------------------------------------------------------
 */

/*---------------------------------------------------------------------------------------
 *                        F U N C T I O N    P R O T O T Y P E
 *---------------------------------------------------------------------------------------
 */
typedef struct _FABRIC_RESOURCE_MANAGER_PROTOCOL FABRIC_RESOURCE_MANAGER_PROTOCOL;

/// Function prototype
typedef EFI_STATUS (EFIAPI *FABRIC_DXE_ALLOCATE_MMIO) (
  IN       FABRIC_RESOURCE_MANAGER_PROTOCOL *This,         ///< Protocol Instance
  IN OUT   UINT64                           *BaseAddress,  ///< Starting address of the requested MMIO range.
  IN OUT   UINT64                           *Length,       ///< Length of the requested MMIO range.
  IN       UINT64                            Alignment,    ///< Alignment bit map. 0xFFFFF means 1MB align
  IN       FABRIC_TARGET                     Target,       ///< Indicator target type
                                                           ///< 0 - TARGET_PCI_BUS - allocate an MMIO region for the device on a certain PCI bus
                                                           ///< 1 - TARGET_RB      - allocate an MMIO region for the device on a certain Socket, RootBridge
  IN OUT   FABRIC_MMIO_ATTRIBUTE            *Attributes    ///< We have 6 pools per RootBridge. 0) MMIO_BELOW_4G 1) MMIO_ABOVE_4G 2) P_MMIO_BELOW_4G 3) P_MMIO_ABOVE_4G 4) NON_PCI_DEVICE_BELOW_4G 5) NON_PCI_DEVICE_ABOVE_4G
                                                           ///< This function is restricted to support NON_PCI_DEVICE_BELOW_4G & NON_PCI_DEVICE_ABOVE_4G only
                                                           ///< Other 4 pools are supported by FabricGetAvailableResource
);

/// Function prototype
typedef EFI_STATUS (EFIAPI *FABRIC_DXE_ALLOCATE_IO) (
  IN       FABRIC_RESOURCE_MANAGER_PROTOCOL *This,         ///< Protocol Instance
  IN OUT   UINT32                           *BaseAddress,  ///< Starting address of the requested IO range.
  IN OUT   UINT32                           *Length,       ///< Length of the requested IO range.
  IN       FABRIC_TARGET                     Target        ///< Indicator target type
                                                           ///< 0 - TARGET_PCI_BUS - allocate an IO region for the device on a certain PCI bus
                                                           ///< 1 - TARGET_RB     - allocate an IO region for the device on a certain Socket, RootBridge
);

/// Function prototype
typedef EFI_STATUS (EFIAPI *FABRIC_DXE_GET_AVAILABLE_RESOURCE) (
  IN       FABRIC_RESOURCE_MANAGER_PROTOCOL  *This,                             ///< Protocol Instance
  IN       FABRIC_RESOURCE_FOR_EACH_RB       *ResourceForEachRb                 ///< Get available DF resource size for each RootBridge
);

/// Function prototype
typedef EFI_STATUS (EFIAPI *FABRIC_DXE_REALLOCATE_RESOURCE_FOR_EACH_RB) (
  IN       FABRIC_RESOURCE_MANAGER_PROTOCOL  *This,                             ///< Protocol Instance
  IN       FABRIC_RESOURCE_FOR_EACH_RB       *ResourceSizeForEachRb,            ///< Re-allocate DF resource size for each RootBridge
  IN       FABRIC_ADDR_SPACE_SIZE            *SpaceStatus                       ///< Report current status
);

/// Function prototype
typedef EFI_STATUS (EFIAPI *FABRIC_DXE_RESOURCE_RESTORE_DEFAULT) (
  IN       FABRIC_RESOURCE_MANAGER_PROTOCOL  *This                              ///< Protocol Instance
);

/// Function prototype
typedef EFI_STATUS (EFIAPI *FABRIC_DXE_ENABLE_VGA_MMIO) (
  IN       FABRIC_RESOURCE_MANAGER_PROTOCOL  *This,                             ///< Protocol Instance
  IN       FABRIC_TARGET                     Target                             ///< Indicator target type
                                                                                ///< 0 - TARGET_PCI_BUS
                                                                                ///< 1 - TARGET_RB
);

/// Fabric resource manager Protocol Structure
struct _FABRIC_RESOURCE_MANAGER_PROTOCOL {                                      //See the Forward Declaration above
  UINTN                                      Revision;                          ///< Revision
  FABRIC_DXE_ALLOCATE_MMIO                   FabricAllocateMmio;                ///< Pointer to function
  FABRIC_DXE_ALLOCATE_IO                     FabricAllocateIo;                  ///< Pointer to function
  FABRIC_DXE_GET_AVAILABLE_RESOURCE          FabricGetAvailableResource;        ///< Pointer to function
  FABRIC_DXE_REALLOCATE_RESOURCE_FOR_EACH_RB FabricReallocateResourceForEachRb; ///< Pointer to function
  FABRIC_DXE_RESOURCE_RESTORE_DEFAULT        FabricResourceRestoreDefault;      ///< Pointer to function
  FABRIC_DXE_ENABLE_VGA_MMIO                 FabricEnableVgaMmio;               ///< Pointer to function
};

extern EFI_GUID gAmdFabricResourceManagerServicesProtocolGuid;
extern EFI_GUID gAmdResourceSizeForEachRbGuid;
extern EFI_GUID gAmdResourceDistributionGuid;

#pragma pack (pop)
#endif // _FABRIC_RESOURCE_MANAGER_SERVICES_PROTOCOL_H_

