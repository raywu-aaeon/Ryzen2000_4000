/* $NoKeywords:$ */
/**
 * @file
 *
 * AmdCoreLaunchServicePpi Implementation
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  AmdCoreLaunchServicePpi
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
#include <Ppi/AmdCoreTopologyServicesPpi.h>
#include <Ppi/NbioPcieServicesPpi.h>
#include <Library/PeiServicesLib.h>
#include <Library/PeiServicesTablePointerLib.h>
#include <Library/IdsLib.h>
#include <Library/NbioHandleLib.h>
#include <Library/GnbRegisterAccZpLib.h>
#include <Library/PcieConfigLib.h>
#include <Library/NbioSmuV10Lib.h>
#include <GnbRegistersRV.h>
#include <Filecode.h>

#define FILECODE        NBIO_SMU_AMDNBIOSMUV10PEI_AMDCORELAUNCHSERVICEPPI_FILECODE

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

/**
 * This service retrieves information about the layout of the cores on the given die.
 *
 * @param[in]  This                           A pointer to the
 *                                            AMD_CORE_TOPOLOGY_SERVICES_PPI instance.
 * @param[in]  Socket                         Zero-based socket number to check.
 * @param[in]  Die                            The target die's identifier within Socket.
 * @param[out] NumberOfComplexes              Pointer to the number of enabled complexes on
 *                                            the given socket / die.
 * @param[out] NumberOfCores                  Pointer to the number of enabled cores per
 *                                            complex on the given socket / die.
 * @param[out] NumberOfThreads                Pointer to the number of enabled threads per
 *                                            core on the given socket / die.
 *
 * @retval EFI_SUCCESS                        The core topology information was successfully retrieved.
 * @retval EFI_INVALID_PARAMETER              Socket is non-existent.
 * @retval EFI_INVALID_PARAMETER              Die is non-existent.
 * @retval EFI_INVALID_PARAMETER              All output parameter pointers are NULL.
 *
 **/
EFI_STATUS
SmuV10GetCoreTopologyOnDie (
  IN       AMD_CORE_TOPOLOGY_SERVICES_PPI   *This,
  IN       UINTN                            Socket,
  IN       UINTN                            Die,
     OUT   UINTN                            *NumberOfComplexes,
     OUT   UINTN                            *NumberOfCores,
     OUT   UINTN                            *NumberOfThreads
  )
{
  EFI_PEI_SERVICES                **PeiServices;
  PEI_AMD_NBIO_PCIE_SERVICES_PPI  *PcieServicesPpi;
  PCIe_PLATFORM_CONFIG            *Pcie;
  EFI_STATUS                      Status;
  GNB_HANDLE                      *GnbHandle;
  AMD_CONFIG_PARAMS               *StdHeader;
  GNB_PCIE_INFORMATION_DATA_HOB   *PciePlatformConfigHob;
  PWR_01C_STRUCT                  ThreadConfiguration;

  IDS_HDT_CONSOLE (MAIN_FLOW, "SmuV10GetCoreTopologyOnDie Entry\n");
  GnbHandle = NULL;
  StdHeader = NULL;  ///@todo - do we need this?
  // Need topology structure
  PeiServices = (EFI_PEI_SERVICES **) GetPeiServicesTablePointer ();
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

    GnbHandle = NbioGetHandle (Pcie);
    while (GnbHandle != NULL) {
      //Find GnbHandle for this Socket/Die
      if ((Socket == GnbHandle->SocketId) && (Die == GnbHandle->DieNumber))  {
        break;
      }
      GnbHandle = GnbGetNextHandle (GnbHandle);
    }
    ASSERT (GnbHandle != NULL);
    if (GnbHandle != NULL) {
      Status = GnbRegisterReadZP (GnbHandle,
                                  THREAD_CONFIGURATION_TYPE,
                                  THREAD_CONFIGURATION_ADDRESS,
                                  &ThreadConfiguration,
                                  0,
                                  StdHeader);
      *NumberOfComplexes = ThreadConfiguration.Field.ComplexCount + 1;
      *NumberOfCores = ThreadConfiguration.Field.CoreCount + 1;
      *NumberOfThreads = (ThreadConfiguration.Field.SMTMode == 0) ? 2 : 1;
    } else {
      Status = EFI_INVALID_PARAMETER;
    }
  }

  IDS_HDT_CONSOLE (MAIN_FLOW, "SmuV10GetCoreTopologyOnDie Exit\n");
  return Status;
}

/**
 * This service will start a core to fetch its first instructions from the reset
 * vector.  This service may only be called from the BSP.
 *
 * @param[in]  This                           A pointer to the
 *                                            AMD_CORE_TOPOLOGY_SERVICES_PPI instance.
 * @param[in]  Socket                         Zero-based socket number of the target thread.
 * @param[in]  Die                            Zero-based die number within Socket of the target thread.
 * @param[in]  LogicalComplex                 Zero-based logical complex number of the target thread.
 * @param[in]  LogicalThread                  Zero-based logical thread number of the target thread.
 *
 * @retval EFI_SUCCESS                        The thread was successfully launched.
 * @retval EFI_DEVICE_ERROR                   The thread has already been launched.
 * @retval EFI_INVALID_PARAMETER              Socket is non-existent.
 * @retval EFI_INVALID_PARAMETER              Die is non-existent.
 * @retval EFI_INVALID_PARAMETER              LogicalComplex is non-existent.
 * @retval EFI_INVALID_PARAMETER              LogicalThread is non-existent.
 *
 **/
EFI_STATUS
SmuV10LaunchThread (
  IN       AMD_CORE_TOPOLOGY_SERVICES_PPI   *This,
  IN       UINTN                            Socket,
  IN       UINTN                            Die,
  IN       UINTN                            LogicalComplex,
  IN       UINTN                            LogicalThread
  )
{
  EFI_PEI_SERVICES                **PeiServices;
  PEI_AMD_NBIO_PCIE_SERVICES_PPI  *PcieServicesPpi;
  PCIe_PLATFORM_CONFIG            *Pcie;
  EFI_STATUS                      Status;
  GNB_HANDLE                      *GnbHandle;
  AMD_CONFIG_PARAMS               *StdHeader;
  GNB_PCIE_INFORMATION_DATA_HOB   *PciePlatformConfigHob;
  PWR_018_STRUCT                  ThreadEnable;
  PWR_01C_STRUCT                  ThreadConfiguration;
  UINTN                           NumberOfThreads;
  UINTN                           NumberOfCores;
  UINTN                           NumberOfLogicalThreads;
  UINT32                          SmuArg[6];

  IDS_HDT_CONSOLE (MAIN_FLOW, "SmuV10GetCoreTopologyOnDie Entry\n");
  GnbHandle = NULL;
  StdHeader = NULL;  ///@todo - do we need this?
  // Need topology structure
  PeiServices = (EFI_PEI_SERVICES **) GetPeiServicesTablePointer ();
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

    GnbHandle = NbioGetHandle (Pcie);
    while (GnbHandle != NULL) {
      //Find GnbHandle for this Socket/Die
      if ((Socket == GnbHandle->SocketId) && (Die == GnbHandle->DieNumber)) {
        break;
      }
      GnbHandle = GnbGetNextHandle (GnbHandle);
    }
    ASSERT (GnbHandle != NULL);
    if (GnbHandle != NULL) {
      Status = GnbRegisterReadZP (GnbHandle,
                                  THREAD_ENABLE_TYPE,
                                  THREAD_ENABLE_ADDRESS,
                                  &ThreadEnable,
                                  0,
                                  StdHeader);
      Status = GnbRegisterReadZP (GnbHandle,
                                  THREAD_CONFIGURATION_TYPE,
                                  THREAD_CONFIGURATION_ADDRESS,
                                  &ThreadConfiguration,
                                  0,
                                  StdHeader);
      NumberOfThreads = (ThreadConfiguration.Field.SMTMode == 0) ? 2 : 1;
      NumberOfCores = ThreadConfiguration.Field.CoreCount + 1;
      NumberOfLogicalThreads = NumberOfCores * NumberOfThreads;
      if ((LogicalComplex <= ThreadConfiguration.Field.ComplexCount) && (LogicalThread < NumberOfLogicalThreads)) {
        if ((ThreadEnable.Field.ThreadEn & (1 << (LogicalThread + (8 * LogicalComplex)))) == 0) {
          ThreadEnable.Field.ThreadEn |= 1 << (LogicalThread + (8 * LogicalComplex));
          Status = GnbRegisterWriteZP (GnbHandle,
                                       THREAD_ENABLE_TYPE,
                                       THREAD_ENABLE_ADDRESS,
                                       &ThreadEnable,
                                       0,
                                       StdHeader);
          NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
          SmuArg[0] = 0xAA55AA55;
          Status = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (GnbHandle), SMC_MSG_TestMessage, SmuArg, GNB_REG_ACC_FLAG_S3SAVE);
        } else {
          Status = EFI_DEVICE_ERROR;
        }
      } else {
        Status = EFI_INVALID_PARAMETER;
      }
    } else {
      Status = EFI_INVALID_PARAMETER;
    }
  }
  IDS_HDT_CONSOLE (MAIN_FLOW, "SmuV10GetCoreTopologyOnDie Exit\n");
  return Status;
}

/*----------------------------------------------------------------------------------------
 *                          P P I   D E S C R I P T O R
 *----------------------------------------------------------------------------------------
 */
AMD_CORE_TOPOLOGY_SERVICES_PPI mAmdCoreTopologyServicesPpi = {
  SmuV10GetCoreTopologyOnDie,
  SmuV10LaunchThread
};


