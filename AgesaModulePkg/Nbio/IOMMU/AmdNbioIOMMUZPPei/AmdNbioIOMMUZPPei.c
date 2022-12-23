/* $NoKeywords:$ */
/**
 * @file
 *
 * AmdNbioIOMMUZPPei Driver
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  AmdNbioIOMMUZPPei
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
#include <AMD.h>
#include <Filecode.h>
#include <PiPei.h>
#include <GnbDxio.h>
#include <Library/PeiServicesLib.h>
#include <Library/AmdBaseLib.h>
#include <Library/PcdLib.h>
#include <Library/HobLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/NbioRegisterAccLib.h>
#include <Library/IdsLib.h>
#include <Library/GnbHeapLib.h>
#include <Library/NbioHandleLib.h>
#include <Library/PcieConfigLib.h>
#include <Library/FabricResourceManagerLib.h>
#include <Library/GnbPciLib.h>
#include <Library/GnbLib.h>
#include <Library/GnbPciAccLib.h>
#include <Guid/GnbPcieInfoHob.h>
#include <Guid/GnbNbioBaseZPInfoHob.h>
#include <Ppi/NbioPcieServicesPpi.h>

#define FILECODE   NBIO_IOMMU_AMDNBIOIOMMUZPPEI_AMDNBIOIOMMUZPPEI_FILECODE

/*----------------------------------------------------------------------------------------
 *                         E X T E R N   D E F I N I T I O N S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U  R E S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */



/*----------------------------------------------------------------------------------------
 *                    P P I   N O T I F Y   D E S C R I P T O R S
 *----------------------------------------------------------------------------------------
 */



/*----------------------------------------------------------------------------------------*/
/**
 * AmdNbio IOMMU ZP PEI driver entry point
 *
 *
 *
 * @param[in]  FileHandle  Standard configuration header
 * @param[in]  PeiServices Pointer to EFI_PEI_SERVICES pointer
 * @retval     EFI_STATUS
 */

EFI_STATUS
EFIAPI
AmdNbioIOMMUZPPeiEntry (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{

  PEI_AMD_NBIO_PCIE_SERVICES_PPI     *PcieServicesPpi;
  GNB_PCIE_INFORMATION_DATA_HOB      *PciePlatformConfigHob;
  FABRIC_TARGET                      MmioTarget;
  FABRIC_MMIO_ATTRIBUTE              MmioAttr;
  UINT64                             IommMmioSize;
  UINT64                             IommMmioBase;
  GNB_HANDLE                         *GnbHandle;
  EFI_STATUS                         Status;
  PCIe_PLATFORM_CONFIG               *Pcie;
  PCI_ADDR                           IommuPciAddress;
  UINT32                             Value;

  if (PcdGetBool (PcdCfgIommuMMIOAddressReservedEnable) == 0x00) {
    IDS_HDT_CONSOLE (MAIN_FLOW, "We don't need reserved IOMMU MMIO space from GNB PEIM \n");
    return EFI_SUCCESS;
  }

  AGESA_TESTPOINT (TpNbioIommuPEIEntry, NULL);
  IDS_HDT_CONSOLE (MAIN_FLOW, "AmdNbioIOMMUZPPEIEntry Entry\n");

  // Need topology structure
  Status = (*PeiServices)->LocatePpi (
                             PeiServices,
                             &gAmdNbioPcieServicesPpiGuid,
                             0,
                             NULL,
                             (VOID **)&PcieServicesPpi
                             );

  if (Status == EFI_SUCCESS) {
    PcieServicesPpi->PcieGetTopology (PcieServicesPpi, &PciePlatformConfigHob);
    Pcie = &(PciePlatformConfigHob->PciePlatformConfigHob);
    GnbHandle = NbioGetHandle (Pcie);
    while (GnbHandle != NULL) {

      MmioTarget.TgtType = TARGET_RB;
      MmioTarget.SocketNum = GnbHandle->SocketId;
      MmioTarget.RbNum = GnbHandle->DieNumber;
      IommMmioSize = SIZE_512KB;
      MmioAttr.MmioType = NON_PCI_DEVICE_BELOW_4G;
      FabricAllocateMmio (&IommMmioBase, &IommMmioSize, ALIGN_512K, MmioTarget, &MmioAttr);
      IDS_HDT_CONSOLE (MAIN_FLOW, "IOMMU MMIO at address 0x%x for Socket 0x%x Silicon 0x%x\n", IommMmioBase, GnbHandle->SocketId, GnbHandle->DieNumber);

      Value = (UINT32)IommMmioBase;
      IommuPciAddress = NbioGetHostPciAddress (GnbHandle);
      IommuPciAddress.Address.Function = 0x2;
      GnbLibPciWrite (IommuPciAddress.AddressValue | 0x44, AccessS3SaveWidth32, &Value, NULL);

      GnbHandle = GnbGetNextHandle (GnbHandle);
    }
  }

  IDS_HDT_CONSOLE (MAIN_FLOW, "AmdNbioIOMMUZPPEIEntry Exit\n");

  AGESA_TESTPOINT (TpNbioIommuPEIExit, NULL);
  return EFI_SUCCESS;
}

