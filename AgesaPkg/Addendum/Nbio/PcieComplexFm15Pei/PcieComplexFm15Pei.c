/* $NoKeywords:$ */
/**
 * @file
 *
 * Platform PCIe Complex Driver
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  AmdNbioSmuV9Pei
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
#include <AmdPcieComplexFm15.h>
#include <Ppi/NbioPcieComplexFm15Ppi.h>

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

  PCIe_PORT_DESCRIPTOR  PortList[] = {
    // GFX - x8 slot
    {
      0,
      PCIE_ENGINE_DATA_INITIALIZER (PciePortEngine, 8, 15),
      PCIE_PORT_DATA_INITIALIZER_V2 (
        PortEnabled,
        ChannelTypeExt6db,
        3,
        1,
        HotplugDisabled,
        PcieGenMaxSupported,
        PcieGenMaxSupported,
        AspmL0sL1,
        1,  // Bristol only uses x8
        0
      )
    },
    // GPP[1:0] - M2 x2
    {
      0,
      PCIE_ENGINE_DATA_INITIALIZER (PciePortEngine, 4, 5),
      PCIE_PORT_DATA_INITIALIZER_V2 (
        PortEnabled,
        ChannelTypeExt6db,
        2,
        5,
        HotplugDisabled,
        PcieGenMaxSupported,
        PcieGenMaxSupported,
        AspmL0sL1,
        2,
        0
      )
    },

    // UMI - Promontroy x4
    {
      0,
      PCIE_ENGINE_DATA_INITIALIZER (PcieUnusedEngine, 0, 3),
      PCIE_PORT_DATA_INITIALIZER_V2 (
        PortDisabled,
        ChannelTypeExt6db,
        2,
        4,
        HotplugDisabled,
        PcieGenMaxSupported,
        PcieGenMaxSupported,
        AspmL0sL1,
        3,
        0
      )
    },
    // UMI - PCIe x4 slot
    {
      DESCRIPTOR_TERMINATE_LIST,
      PCIE_ENGINE_DATA_INITIALIZER (PciePortEngine, 0, 3),
      PCIE_PORT_DATA_INITIALIZER_V2 (
        PortEnabled,
        ChannelTypeExt6db,
        2,
        3,
        HotplugDisabled,
        PcieGenMaxSupported,
        PcieGenMaxSupported,
        AspmL0sL1,
        4,
        0
      )
    },
  };

  PCIe_DDI_DESCRIPTOR DdiList[] = {
    // DDI0 - DP
    {
      0,
      PCIE_ENGINE_DATA_INITIALIZER (PcieDdiEngine, 16, 19),
      PCIE_DDI_DATA_INITIALIZER (ConnectorTypeDP, Aux1, Hdp1)
    },
    // DDI1 - HDMI
    {
      0,
      PCIE_ENGINE_DATA_INITIALIZER (PcieDdiEngine, 20, 23),
      PCIE_DDI_DATA_INITIALIZER (ConnectorTypeHDMI, Aux2, Hdp2)
    },
    // DDI2 - HDMI
    {
      DESCRIPTOR_TERMINATE_LIST,
      PCIE_ENGINE_DATA_INITIALIZER (PcieDdiEngine, 24, 27),
      PCIE_DDI_DATA_INITIALIZER (ConnectorTypeHDMI, Aux3, Hdp3)
    }
  };

  PCIe_COMPLEX_DESCRIPTOR PcieComplex = {
    DESCRIPTOR_TERMINATE_LIST,
    0,
    &PortList[0],
    &DdiList[0],
    NULL
  };

/**
  This service will start a core to fetch its first instructions from the reset
  vector.  This service may only be called from the BSP.

  @param[in]  This        A pointer to the PEI_AMD_NBIO_PCIE_COMPLEX_PPI instance
  @param[in]  UserConfig  Pointer PCIe_COMPLEX_DESCRIPTOR pointer

  @retval EFI_SUCCESS                        The thread was successfully launched.

**/
EFI_STATUS
PcieGetComplex (
  IN       PEI_AMD_NBIO_PCIE_COMPLEX_FM15_PPI *This,
     OUT   PCIe_COMPLEX_DESCRIPTOR            **UserConfig
  )
{
  *UserConfig = &PcieComplex;
  return EFI_SUCCESS;
}

STATIC PEI_AMD_NBIO_PCIE_COMPLEX_FM15_PPI mPcieComplexPpi = {
  AMD_NBIO_PCIE_COMPLEX_FM15_REVISION,  ///< revision
  PcieGetComplex
};

STATIC EFI_PEI_PPI_DESCRIPTOR mPcieComplexDescriptorPpiList = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gAmdNbioPcieComplexFm15PpiGuid,
  &mPcieComplexPpi
};

EFI_STATUS
EFIAPI
PcieComplexFm15PeiEntry (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
  EFI_STATUS                       Status;
  // Fixup PCIe_COMPLEX_DESCRIPTOR here
  Status = (**PeiServices).InstallPpi (PeiServices, &mPcieComplexDescriptorPpiList);
  return Status;
}

