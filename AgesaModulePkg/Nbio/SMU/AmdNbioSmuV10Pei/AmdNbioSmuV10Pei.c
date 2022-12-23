/* $NoKeywords:$ */
/**
 * @file
 *
 * AmdNbioSmuV10Pei Driver
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  AmdNbioSmuV10Pei
 * @e \$Revision: 312065 $   @e \$Date: 2015-01-30 04:23:05 -0600 (Fri, 30 Jan 2015) $
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
#include <PiPei.h>
#include <Filecode.h>
#include <GnbDxio.h>
#include <AmdNbioSmuV10Pei.h>
#include <GnbRegistersRV.h>
#include <Library/AmdBaseLib.h>
#include <Library/IdsLib.h>
#include <Library/PcdLib.h>
#include <Library/HobLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/NbioHandleLib.h>
//#include <PcieComplexDataZP.h>
#include <Ppi/NbioSmuServicesPpi.h>
#include <Ppi/NbioBaseServicesZPPpi.h>
#include <Ppi/NbioPcieServicesPpi.h>
#include <Ppi/AmdCoreTopologyServicesPpi.h>
#include <Guid/GnbNbioBaseZPInfoHob.h>
#include <IdsHookId.h>
#include <Library/AmdIdsHookLib.h>


/*----------------------------------------------------------------------------------------
 *                         E X T E R N   D E F I N I T I O N S
 *----------------------------------------------------------------------------------------
 */

extern
PEI_AMD_NBIO_SMU_SERVICES_PPI mNbioSmuServicePpi;

extern
AMD_CORE_TOPOLOGY_SERVICES_PPI mAmdCoreTopologyServicesPpi;
/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */

#define FILECODE        NBIO_SMU_AMDNBIOSMUV10PEI_AMDNBIOSMUV10PEI_FILECODE

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U  R E S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */
EFI_STATUS
EFIAPI
DispatchSmuV10Callback (
  IN CONST EFI_PEI_SERVICES         **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR      *NotifyDescriptor,
  IN VOID                           *Ppi
  );

EFI_STATUS
EFIAPI
InstallSmuV10Ppi (
  IN CONST EFI_PEI_SERVICES         **PeiServices
  );

/*----------------------------------------------------------------------------------------
 *                    P P I   N O T I F Y   D E S C R I P T O R S
 *----------------------------------------------------------------------------------------
 */

STATIC EFI_PEI_PPI_DESCRIPTOR mNbioSmuServicesPpiList =
{
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gAmdNbioSmuServicesPpiGuid,
  &mNbioSmuServicePpi
};

STATIC EFI_PEI_NOTIFY_DESCRIPTOR   mNotifySmuV10Ppi = {
  EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK,
  &gAmdNbioBaseServicesZpPpiGuid,
  DispatchSmuV10Callback
};


EFI_STATUS
EFIAPI
InstallSmuV10Ppi (
  IN CONST EFI_PEI_SERVICES         **PeiServices
  )
{
  EFI_STATUS       Status;

  IDS_HDT_CONSOLE (MAIN_FLOW, "InstallSmuV10Ppi\n");
  Status = (**PeiServices).InstallPpi (PeiServices, &mNbioSmuServicesPpiList);  //This driver is done.

  return Status;
}
STATIC EFI_PEI_PPI_DESCRIPTOR mAmdCoreTopologyServicesPpiList =
{
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gAmdCoreTopologyServicesPpiGuid,
  &mAmdCoreTopologyServicesPpi
};

EFI_STATUS
EFIAPI
InstallCoreToplogyServicesPpi (
  IN CONST EFI_PEI_SERVICES         **PeiServices
  )
{
  EFI_STATUS       Status;

  IDS_HDT_CONSOLE (MAIN_FLOW, "InstallCoreToplogyServicesPpi\n");
  Status = (**PeiServices).InstallPpi (PeiServices, &mAmdCoreTopologyServicesPpiList);  //This driver is done.

  return Status;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Dispatch SmuV10 Ppi callback
 * This function should use the information from memory config to initialize NBIO top of memory
 *
 *
 *
 * @param[in]  PeiServices       Pointer to EFI_PEI_SERVICES pointer
 * @param[in]  NotifyDescriptor  NotifyDescriptor pointer
 * @param[in]  Ppi               Ppi pointer
 * @retval     EFI_STATUS
 */

EFI_STATUS
EFIAPI
DispatchSmuV10Callback (
  IN CONST EFI_PEI_SERVICES     **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  IN VOID                       *Ppi
  )
{
  EFI_STATUS       Status;

  AGESA_TESTPOINT (TpDispatchSmuV10CallbackEntry, NULL);
  IDS_HDT_CONSOLE (MAIN_FLOW, "DispatchSmuV10Callback Entry\n");
  Status = InstallSmuV10Ppi (PeiServices);
  Status = InstallCoreToplogyServicesPpi (PeiServices);
  IDS_HDT_CONSOLE (MAIN_FLOW, "DispatchSmuV10Callback Exit\n");
  AGESA_TESTPOINT (TpDispatchSmuV10CallbackExit, NULL);

  return Status;
}

EFI_STATUS
EFIAPI
AmdNbioSmuV10PeiEntry (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
  EFI_STATUS                       Status;
  PEI_AMD_NBIO_BASE_SERVICES_PPI   *NbioBaseServicesPpi;
  PEI_AMD_NBIO_PCIE_SERVICES_PPI   *PcieServicesPpi;
  GNB_PCIE_INFORMATION_DATA_HOB    *PciePlatformConfigHob;
  PCIe_PLATFORM_CONFIG             *Pcie;

  AGESA_TESTPOINT (TpNbioSmuV10PeiEntry, NULL);
  IDS_HDT_CONSOLE (MAIN_FLOW, "AmdNbioSmuV10PeiEntry Entry\n");
  IDS_HOOK(IDS_HOOK_NBIO_SMUV10_INIT, NULL, NULL);
  //
  // Waiting for Nbio Base Sevice ready.
  //
  Status = PeiServicesLocatePpi (
             &gAmdNbioBaseServicesZpPpiGuid,
             0,
             NULL,
             (VOID **)&NbioBaseServicesPpi
             );
  if (Status == EFI_SUCCESS) {
    Status = InstallSmuV10Ppi (PeiServices);
    Status = InstallCoreToplogyServicesPpi (PeiServices);
  } else {
    //
    // Notify event
    //
    Status = (**PeiServices).NotifyPpi (PeiServices, &mNotifySmuV10Ppi);
  }
  Status = (*PeiServices)->LocatePpi (
                             PeiServices,
                             &gAmdNbioPcieServicesPpiGuid,
                             0,
                             NULL,
                             (VOID **)&PcieServicesPpi
                             );
  ASSERT (Status == EFI_SUCCESS);
  if (Status == EFI_SUCCESS) {
    PcieServicesPpi->PcieGetTopology (PcieServicesPpi, &PciePlatformConfigHob);
    Pcie = &(PciePlatformConfigHob->PciePlatformConfigHob);
    IDS_HDT_CONSOLE (MAIN_FLOW, "About to call  AmdNbioSmuEarlyInit\n");
    AmdNbioSmuEarlyInit (Pcie);
  }

  IDS_HDT_CONSOLE (MAIN_FLOW, "AmdNbioSmuV10PeiEntry Exit\n");
  AGESA_TESTPOINT (TpNbioSmuV10PeiExit, NULL);

  return Status;
}

