/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD Fabric ACPI Domain infor for SRAT & CDIT.
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Fabric
 * @e \$Revision$   @e \$Date$
 *
 */
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

/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */
#include "Porting.h"
#include "AMD.h"
#include "FabricAcpiDomainInfo.h"
#include "FabricAcpiTable.h"
#include <Library/BaseLib.h>
#include "Library/AmdBaseLib.h"
#include <Library/BaseFabricTopologyLib.h>
#include <FabricRegistersRV.h>
#include <Library/FabricRegisterAccLib.h>
#include <Library/AmdIdsHookLib.h>
#include "Library/UefiBootServicesTableLib.h"
#include <Protocol/FabricNumaServicesProtocol.h>
#include "Filecode.h"


#define FILECODE FABRIC_RV_FABRICRVDXE_FABRICACPIDOMAININFO_FILECODE

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */
VOID
BuildDomainInfo (
  VOID
  );

/*----------------------------------------------------------------------------------------
 *                           G L O B A L   V A R I A B L E S
 *----------------------------------------------------------------------------------------
 */

BOOLEAN      mDomainInfoValid = FALSE;
UINT32       mNumberOfDomains = 0;
DOMAIN_INFO  mDomainInfo[MAX_SOCKETS_RV * MAX_DIES_PER_SOCKET_RV];
DIE_INFO     mDieInfo[MAX_SOCKETS_RV][MAX_DIES_PER_SOCKET_RV];

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U R E S
 *----------------------------------------------------------------------------------------
 */
EFI_STATUS
EFIAPI
FabricRvGetDomainInfo (
  IN       FABRIC_NUMA_SERVICES_PROTOCOL  *This,
     OUT   UINT32                         *NumberOfDomainsInSystem,
     OUT   DOMAIN_INFO                   **DomainInfo
  );

EFI_STATUS
EFIAPI
FabricRvDomainXlat (
  IN       FABRIC_NUMA_SERVICES_PROTOCOL  *This,
  IN       UINTN                           Socket,
  IN       UINTN                           Die,
     OUT   UINT32                         *Domain
  );

/*----------------------------------------------------------------------------------------
 *                           G L O B A L   V A R I A B L E S
 *----------------------------------------------------------------------------------------
 */
STATIC FABRIC_NUMA_SERVICES_PROTOCOL  mFabricNumaServicesProtocol = {
  0x1,
  FabricRvGetDomainInfo,
  FabricRvDomainXlat
};

/*----------------------------------------------------------------------------------------
 *                          E X P O R T E D    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */
EFI_STATUS
EFIAPI
FabricRvNumaServicesProtocolInstall (
  IN       EFI_HANDLE        ImageHandle,
  IN       EFI_SYSTEM_TABLE  *SystemTable
  )
{
  BuildDomainInfo ();
  return (gBS->InstallProtocolInterface (
                &ImageHandle,
                &gAmdFabricNumaServicesProtocolGuid,
                EFI_NATIVE_INTERFACE,
                &mFabricNumaServicesProtocol
                ));
}

EFI_STATUS
EFIAPI
FabricRvGetDomainInfo (
  IN       FABRIC_NUMA_SERVICES_PROTOCOL  *This,
     OUT   UINT32                         *NumberOfDomainsInSystem,
     OUT   DOMAIN_INFO                   **DomainInfo
  )
{
  ASSERT (mDomainInfoValid);

  if ((NumberOfDomainsInSystem == NULL) && (DomainInfo == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  if (NumberOfDomainsInSystem != NULL) {
    *NumberOfDomainsInSystem = mNumberOfDomains;
  }

  if (DomainInfo != NULL) {
    *DomainInfo = &mDomainInfo[0];
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
FabricRvDomainXlat (
  IN       FABRIC_NUMA_SERVICES_PROTOCOL  *This,
  IN       UINTN                           Socket,
  IN       UINTN                           Die,
     OUT   UINT32                         *Domain
  )
{
  ASSERT (mDomainInfoValid);

  if (Socket >= FabricTopologyGetNumberOfProcessorsPresent ()) {
    return EFI_INVALID_PARAMETER;
  }

  if (Die >= FabricTopologyGetNumberOfDiesOnSocket (Socket)) {
    return EFI_INVALID_PARAMETER;
  }

  if (Domain == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  *Domain = mDieInfo[Socket][Die].Domain;
  return EFI_SUCCESS;
}

VOID
BuildDomainInfo (
  VOID
  )
{
  UINTN                        NumberOfSockets;
  UINTN                        NumberOfDiesOnSocket;
  UINT32                       i;
  UINT32                       j;
  UINT32                       k;
  UINT32                       MapPairIndex;
  UINT32                       DiesAccountedForInDomain[(MAX_SOCKETS_RV * MAX_DIES_PER_SOCKET_RV)];
  UINT32                       TotalEntities[(MAX_SOCKETS_RV * MAX_DIES_PER_SOCKET_RV)];
  DRAM_INFO                    DramInfo[NUMBER_OF_DRAM_REGIONS];
  DRAM_BASE_ADDRESS_REGISTER   DramBaseAddr;
  DRAM_LIMIT_ADDRESS_REGISTER  DramLimitAddr;

  ASSERT (!mDomainInfoValid);
  ASSERT (mNumberOfDomains == 0);

  // Collect raw data
  for (i = 0; i < NUMBER_OF_DRAM_REGIONS; i++) {
    DramBaseAddr.Value = FabricRegisterAccRead (0, 0, DRAMBASEADDR0_FUNC, (DRAMBASEADDR0_REG + (i * DRAM_REGION_REGISTER_OFFSET)), RV_IOMS0_INSTANCE_ID);
    if (DramBaseAddr.Field.AddrRngVal == 1) {
      DramLimitAddr.Value = FabricRegisterAccRead (0, 0, DRAMLIMITADDR0_FUNC, (DRAMLIMITADDR0_REG + (i * DRAM_REGION_REGISTER_OFFSET)), RV_IOMS0_INSTANCE_ID);
      DramInfo[i].Socket = ((DramLimitAddr.Field.DstFabricID >> FABRIC_ID_SOCKET_SHIFT) & FABRIC_ID_SOCKET_SIZE_MASK);
      DramInfo[i].Die = ((DramLimitAddr.Field.DstFabricID >> FABRIC_ID_DIE_SHIFT) & FABRIC_ID_DIE_SIZE_MASK);
      DramInfo[i].SocketMask = 0xFFFFFFFF << DramLimitAddr.Field.IntLvNumSockets;
      DramInfo[i].DieMask = 0xFFFFFFFF << DramLimitAddr.Field.IntLvNumDies;
      DramInfo[i].SocketCount = 1 << DramLimitAddr.Field.IntLvNumSockets;
      DramInfo[i].DieCount = 1 << DramLimitAddr.Field.IntLvNumDies;
    } else {
      DramInfo[i].SocketCount = 0;
      DramInfo[i].DieCount = 0;
      DramInfo[i].Socket = 0xFF;
      DramInfo[i].Die = 0xFF;
      DramInfo[i].SocketMask = 0;
      DramInfo[i].DieMask = 0;
    }
  }

  // Initialize domain info to none
  for (i = 0; i < (MAX_SOCKETS_RV * MAX_DIES_PER_SOCKET_RV); i++) {
    DiesAccountedForInDomain[i] = 0;
    TotalEntities[i] = 0;
    mDomainInfo[i].Type = MaxDomainType;
  }

  // Initialize die info to none
  for (i = 0; i < MAX_SOCKETS_RV; i++) {
    for (j = 0; j < MAX_DIES_PER_SOCKET_RV; j++) {
      mDieInfo[i][j].Domain = 0xFF;
      for (k = 0; k < MAX_CHANNELS_PER_DIE; k++) {
        mDieInfo[i][j].DramMapPair[k] = 0xFF;
      }
    }
  }

  // Build die and domain info
  NumberOfSockets = FabricTopologyGetNumberOfProcessorsPresent ();
  ASSERT (NumberOfSockets <= MAX_SOCKETS_RV);
  for (i = 0; i < NumberOfSockets; i++) {
    NumberOfDiesOnSocket = FabricTopologyGetNumberOfDiesOnSocket (i);
    ASSERT (NumberOfDiesOnSocket <= MAX_DIES_PER_SOCKET_RV);
    for (j = 0; j < NumberOfDiesOnSocket; j++) {
      mDieInfo[i][j].Domain = mNumberOfDomains;
      DiesAccountedForInDomain[mNumberOfDomains]++;
      MapPairIndex = 0;
      for (k = 0; k < NUMBER_OF_DRAM_REGIONS; k++) {
        if ((DramInfo[k].Socket == (i & DramInfo[k].SocketMask)) && (DramInfo[k].Die == (j & DramInfo[k].DieMask))) {
          ASSERT (MapPairIndex < MAX_CHANNELS_PER_DIE);
          mDieInfo[i][j].DramMapPair[MapPairIndex++] = k;
        }
      }
      if (MapPairIndex != 1)  {
        mDomainInfo[mNumberOfDomains].Type = NoIntlv;
        mDomainInfo[mNumberOfDomains].Intlv.None.Socket = i;
        mDomainInfo[mNumberOfDomains].Intlv.None.Die = j;
        TotalEntities[mNumberOfDomains] = 1;
      } else if (DiesAccountedForInDomain[mNumberOfDomains] == 1) {
        if (DramInfo[mDieInfo[i][j].DramMapPair[0]].SocketCount > 1) {
          mDomainInfo[mNumberOfDomains].Type = SocketIntlv;
          mDomainInfo[mNumberOfDomains].Intlv.Socket.SocketCount = DramInfo[mDieInfo[i][j].DramMapPair[0]].SocketCount;
          TotalEntities[mNumberOfDomains] = mDomainInfo[mNumberOfDomains].Intlv.Socket.SocketCount * DramInfo[mDieInfo[i][j].DramMapPair[0]].DieCount;
          mDomainInfo[mNumberOfDomains].Intlv.Socket.SocketMap |= (1 << i);
        } else if (DramInfo[mDieInfo[i][j].DramMapPair[0]].DieCount > 1) {
          mDomainInfo[mNumberOfDomains].Type = DieIntlv;
          mDomainInfo[mNumberOfDomains].Intlv.Die.DieCount = DramInfo[mDieInfo[i][j].DramMapPair[0]].DieCount;
          TotalEntities[mNumberOfDomains] = mDomainInfo[mNumberOfDomains].Intlv.Die.DieCount;
          mDomainInfo[mNumberOfDomains].Intlv.Die.DieMap |= (1 << j);
        } else {
          mDomainInfo[mNumberOfDomains].Type = NoIntlv;
          TotalEntities[mNumberOfDomains] = 1;
          mDomainInfo[mNumberOfDomains].Intlv.None.Socket = i;
          mDomainInfo[mNumberOfDomains].Intlv.None.Die = j;
        }
      }
      if (DiesAccountedForInDomain[mNumberOfDomains] == TotalEntities[mNumberOfDomains]) {
        mNumberOfDomains++;
      }
    }
  }

  mDomainInfoValid = TRUE;
}


